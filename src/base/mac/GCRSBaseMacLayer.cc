//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "GCRSBaseMacLayer.h"

#define DBG_MAC EV

Define_Module(GCRSBaseMacLayer)
;

void GCRSBaseMacLayer::initialize(int stage) {
    BaseMacLayer::initialize(stage);
    if (stage == 0) {
        phy11p = FindModule<Mac80211pToPhy11pInterface*>::findSubModule(
                getParentModule());
        assert(phy11p);
        //this is required to circumvent double precision issues with constants from CONST80211p.h
        assert(simTime().getScaleExp() == -12);

        txPower = par("txPower").doubleValue();
        bitrate = par("bitrate");
        checkBitrate(bitrate);

        //mac-addresses
        myMacAddress = intuniform(0, 0xFFFFFFFE);
        myId = getParentModule()->getParentModule()->getFullPath();
        //create frequency mappings
        frequency.insert(std::pair<int, double>(Channels::CRIT_SOL, 5.86e9));
        frequency.insert(std::pair<int, double>(Channels::SCH1, 5.87e9));
        frequency.insert(std::pair<int, double>(Channels::SCH2, 5.88e9));
        frequency.insert(std::pair<int, double>(Channels::CCH, 5.89e9));
        frequency.insert(std::pair<int, double>(Channels::SCH3, 5.90e9));
        frequency.insert(std::pair<int, double>(Channels::SCH4, 5.91e9));
        frequency.insert(std::pair<int, double>(Channels::HPPS, 5.92e9));

        //create two edca systems
        myEDCA[type_CCH] = new EDCA(type_CCH, par("queueSize").longValue());
        myEDCA[type_CCH]->myId = myId;
        myEDCA[type_CCH]->myId.append(" CCH");

        myEDCA[type_CCH]->createQueue(2, (((CWMIN_11P + 1) / 4) - 1),
                (((CWMIN_11P + 1) / 2) - 1), AC_VO);
        myEDCA[type_CCH]->createQueue(3, (((CWMIN_11P + 1) / 2) - 1), CWMIN_11P,
                AC_VI);
        myEDCA[type_CCH]->createQueue(6, CWMIN_11P, CWMAX_11P, AC_BE);
        myEDCA[type_CCH]->createQueue(9, CWMIN_11P, CWMAX_11P, AC_BK);

        myEDCA[type_SCH] = new EDCA(type_SCH, par("queueSize").longValue());
        myEDCA[type_SCH]->myId = myId;
        myEDCA[type_SCH]->myId.append(" SCH");

        myEDCA[type_SCH]->createQueue(2, (((CWMIN_11P + 1) / 4) - 1),
                (((CWMIN_11P + 1) / 2) - 1), AC_VO);
        myEDCA[type_SCH]->createQueue(3, (((CWMIN_11P + 1) / 2) - 1), CWMIN_11P,
                AC_VI);
        myEDCA[type_SCH]->createQueue(6, CWMIN_11P, CWMAX_11P, AC_BE);
        myEDCA[type_SCH]->createQueue(9, CWMIN_11P, CWMAX_11P, AC_BK);

        useSCH = par("useServiceChannel").boolValue();
        if (useSCH) {
            //set the initial service channel
            switch (par("serviceChannel").longValue()) {
            case 1:
                mySCH = Channels::SCH1;
                break;
            case 2:
                mySCH = Channels::SCH2;
                break;
            case 3:
                mySCH = Channels::SCH3;
                break;
            case 4:
                mySCH = Channels::SCH4;
                break;
            default:
                opp_error("Service Channel must be between 1 and 4");
                break;
            }
        }
        headerLength = par("headerLength");
        nextMacEvent = new cMessage("next Mac Event");

        if (useSCH) {
            // introduce a little asynchronization between radios, but no more than .3 milliseconds
            uint64_t currenTime = simTime().raw();
            uint64_t switchingTime = SWITCHING_INTERVAL_11P.raw();
            double timeToNextSwitch = (double) (switchingTime
                    - (currenTime % switchingTime)) / simTime().getScale();
            if ((currenTime / switchingTime) % 2 == 0) {
                setActiveChannel(type_CCH);
            } else {
                setActiveChannel(type_SCH);
            }

            // channel switching active
            nextChannelSwitch = new cMessage("Channel Switch");
            simtime_t offset = dblrand() * par("syncOffset").doubleValue();
            scheduleAt(simTime() + offset + timeToNextSwitch,
                    nextChannelSwitch);
        } else {
            // no channel switching
            nextChannelSwitch = 0;
            setActiveChannel(type_CCH);
        }
        //stats
        statsReceivedPackets = 0;
        statsReceivedBroadcasts = 0;
        statsSentPackets = 0;
        statsTXRXLostPackets = 0;
        statsSNIRLostPackets = 0;
        statsDroppedPackets = 0;
        statsNumTooLittleTime = 0;
        statsNumInternalContention = 0;
        statsNumBackoff = 0;
        statsSlotsBackoff = 0;
        statsTotalBusyTime = 0;

        idleChannel = true;
        lastBusy = simTime();
        channelIdle(true);
    }
}

void GCRSBaseMacLayer::finish() {
    //clean up queues.

    for (std::map<t_channel, EDCA*>::iterator iter = myEDCA.begin();
            iter != myEDCA.end(); iter++) {
        statsNumInternalContention += iter->second->statsNumInternalContention;
        statsNumBackoff += iter->second->statsNumBackoff;
        statsSlotsBackoff += iter->second->statsSlotsBackoff;
        iter->second->cleanUp();
        delete iter->second;
    }
    myEDCA.clear();

    if (nextMacEvent->isScheduled()) {
        cancelAndDelete(nextMacEvent);
    } else {
        delete nextMacEvent;
    }

    if (nextChannelSwitch && nextChannelSwitch->isScheduled())
        cancelAndDelete(nextChannelSwitch);

    //stats
    recordScalar("ReceivedUnicastPackets", statsReceivedPackets);
    recordScalar("ReceivedBroadcasts", statsReceivedBroadcasts);
    recordScalar("SentPackets", statsSentPackets);
    recordScalar("SNIRLostPackets", statsSNIRLostPackets);
    recordScalar("RXTXLostPackets", statsTXRXLostPackets);
    recordScalar("TotalLostPackets",
            statsSNIRLostPackets + statsTXRXLostPackets);
    recordScalar("DroppedPacketsInMac", statsDroppedPackets);
    recordScalar("TooLittleTime", statsNumTooLittleTime);
    recordScalar("TimesIntoBackoff", statsNumBackoff);
    recordScalar("SlotsBackoff", statsSlotsBackoff);
    recordScalar("NumInternalContention", statsNumInternalContention);
    recordScalar("totalBusyTime", statsTotalBusyTime.dbl());
}

void GCRSBaseMacLayer::handleLowerMsg(cMessage* msg) {
    Mac80211Pkt* macPkt = static_cast<Mac80211Pkt*>(msg);
    ASSERT(macPkt);
    GCRSBaseNetPkt* netwPkt =
            dynamic_cast<GCRSBaseNetPkt*>(macPkt->decapsulate());
    long dest = macPkt->getDestAddr();

    DBG_MAC<< "Received frame name= " << macPkt->getName()
    << ", myState=" << " src=" << macPkt->getSrcAddr()
    << " dst=" << dest << " myAddr="
    << myMacAddress << std::endl;

    if (dest == myMacAddress) {
        DBG_MAC<< "Received a data packet addressed to me." << std::endl;
        statsReceivedPackets++;
        sendUp(netwPkt);
    } else if (dest == LAddress::L2BROADCAST) {
        statsReceivedBroadcasts++;
        sendUp(netwPkt);
    } else {
        DBG_MAC << "Packet not for me, deleting..." << std::endl;
        delete netwPkt;
    }
    delete macPkt;
}

void GCRSBaseMacLayer::handleUpperMsg(cMessage* msg) {

    GCRSBaseNetPkt* thisMsg;

    if ((thisMsg = dynamic_cast<GCRSBaseNetPkt*>(msg)) == NULL) {
        error("GCRMAC80211p only accepts GCR Networking Packets");
    }

    t_access_category ac = mapPriority(thisMsg->getPriority());

    DBG_MAC<< "Received a message from upper layer for channel "
    << thisMsg->getChannelNumber() << " Access Category (Priority):  "
    << ac << std::endl;

    t_channel chan;

    //rewrite SCH channel to actual SCH the GCRMAC80211p is set to
    if (thisMsg->getChannelNumber() == Channels::SCH1
            || thisMsg->getChannelNumber() == Channels::SCH2
            || thisMsg->getChannelNumber() == Channels::SCH3
            || thisMsg->getChannelNumber() == Channels::SCH4) {
        ASSERT(useSCH);
        thisMsg->setChannelNumber(mySCH);
        chan = type_SCH;
    }

    /*    if (thisMsg->getChannelNumber() == Channels::SCH1) {
        ASSERT(useSCH);
        thisMsg->setChannelNumber(mySCH);
        chan = type_SCH;
    }*/

    //put this packet in its queue
    if (thisMsg->getChannelNumber() == Channels::CCH) {
        chan = type_CCH;
    }

    int num = myEDCA[chan]->queuePacket(ac, thisMsg);

    //packet was dropped in Mac
    if (num == -1) {
        statsDroppedPackets++;
        return;
    }

    //if this packet is not at the front of a new queue we dont have to reevaluate times
    DBG_MAC<< "sorted packet into queue of EDCA " << chan << " this packet is now at position: " << num << std::endl;
    if (chan == activeChannel) {
        DBG_MAC<< "this packet is for the currently active channel" << std::endl;
    } else {
        DBG_MAC << "this packet is NOT for the currently active channel" << std::endl;
    }

    if (num == 1 && idleChannel == true && chan == activeChannel) {
        simtime_t nextEvent = myEDCA[chan]->startContent(lastIdle,
                guardActive());
        if (nextEvent != -1) {
            if ((!useSCH)
                    || (nextEvent <= nextChannelSwitch->getArrivalTime())) {
                if (nextMacEvent->isScheduled()) {
                    cancelEvent(nextMacEvent);
                }
                scheduleAt(nextEvent, nextMacEvent);
                DBG_MAC<< "Updated nextMacEvent:" << nextMacEvent->getArrivalTime().raw() << std::endl;
            } else {
                DBG_MAC<< "Too little time in this interval. Will not schedule nextMacEvent" << std::endl;
                //it is possible that this queue has an txop. we have to revoke it
                myEDCA[activeChannel]->revokeTxOPs();
                statsNumTooLittleTime++;
            }
        } else {
            cancelEvent(nextMacEvent);
        }
    }
    if (num == 1 && idleChannel == false
            && myEDCA[chan]->myQueues[ac].currentBackoff == 0
            && chan == activeChannel) {
        myEDCA[chan]->backoff(ac);
    }
}

void GCRSBaseMacLayer::handleUpperControl(cMessage* msg) {
    assert(false);
}

void GCRSBaseMacLayer::handleLowerControl(cMessage* msg) {
    if (msg->getKind() == MacToPhyInterface::TX_OVER) {
        DBG_MAC<< "Successfully transmitted a packet on " << lastAC << std::endl;
        phy->setRadioState(Radio::RX);
        //message was sent
        //update EDCA queue. go into post-transmit backoff and set cwCur to cwMin
        myEDCA[activeChannel]->postTransmit(lastAC);
        //channel just turned idle.
        //don't set the chan to idle. the PHY layer decides, not us.
        if (guardActive()) {
            opp_error("We shouldnt have sent a packet in guard!");
        }
    } else if (msg->getKind() == Mac80211pToPhy11pInterface::CHANNEL_BUSY) {
        channelBusy();
    } else if (msg->getKind() == Mac80211pToPhy11pInterface::CHANNEL_IDLE) {
        channelIdle();
    } else if (msg->getKind() == Decider80211p::BITERROR) {
        statsSNIRLostPackets++;
        DBG_MAC << "A packet was not received due to biterrors" << std::endl;
    } else if (msg->getKind() == Decider80211p::RECWHILESEND) {
        statsTXRXLostPackets++;
        DBG_MAC << "A packet was not received because we were sending while receiving" << std::endl;
    } else if (msg->getKind() == MacToPhyInterface::RADIO_SWITCHING_OVER) {
        DBG_MAC << "Phylayer said radio switching is done" << std::endl;
    } else if (msg->getKind() == BaseDecider::PACKET_DROPPED) {
        phy->setRadioState(Radio::RX);
        DBG_MAC << "Phylayer said packet was dropped" << std::endl;
    } else {
        DBG_MAC << "Invalid control message type (type=NOTHING) : name=" << msg->getName() << " modulesrc=" << msg->getSenderModule()->getFullPath() << "." << std::endl;
        assert(false);
    }
    delete msg;
}

void GCRSBaseMacLayer::handleSelfMsg(cMessage* msg) {
    if (msg == nextChannelSwitch) {
        ASSERT(useSCH);

        scheduleAt(simTime() + SWITCHING_INTERVAL_11P, nextChannelSwitch);

        switch (activeChannel) {
        case type_CCH:
            DBG_MAC<< "CCH --> SCH" << std::endl;
            channelBusySelf(false);
            setActiveChannel(type_SCH);
            channelIdle(true);
            phy11p->changeListeningFrequency(frequency[mySCH]);
            break;
            case type_SCH:
            DBG_MAC << "SCH --> CCH" << std::endl;
            channelBusySelf(false);
            setActiveChannel(type_CCH);
            channelIdle(true);
            phy11p->changeListeningFrequency(frequency[Channels::CCH]);
            break;
        }
        //schedule next channel switch in 50ms
    } else if (msg == nextMacEvent) {
        //we actually came to the point where we can send a packet
        channelBusySelf(true);
        GCRSBaseNetPkt* pktToSend = myEDCA[activeChannel]->initiateTransmit(lastIdle);
        lastAC = mapPriority(pktToSend->getPriority());
        DBG_MAC << "MacEvent received. Trying to send packet with priority" << lastAC << std::endl;

        //send the packet
        Mac80211Pkt* mac = new Mac80211Pkt(pktToSend->getName(), pktToSend->getKind());

        mac->setDestAddr(LAddress::L2BROADCAST);
        mac->setSrcAddr(myMacAddress);
        mac->encapsulate(pktToSend->dup());

        simtime_t sendingDuration = RADIODELAY_11P + PHY_HDR_PREAMBLE_DURATION +
        PHY_HDR_PLCPSIGNAL_DURATION +
        ((mac->getBitLength() + PHY_HDR_PSDU_HEADER_LENGTH)/bitrate);
        DBG_MAC << "Sending duration will be" << sendingDuration << std::endl;

        if ((!useSCH) || (timeLeftInSlot() > sendingDuration)) {
            if (useSCH) DBG_MAC << " Time in this slot left: " << timeLeftInSlot() << std::endl;
            // give time for the radio to be in Tx state before transmitting
            phy->setRadioState(Radio::TX);

            double freq = (activeChannel == type_CCH) ? frequency[Channels::CCH] : frequency[mySCH];
            attachSignal(mac, simTime()+RADIODELAY_11P, freq);
            MacToPhyControlInfo* phyInfo = dynamic_cast<MacToPhyControlInfo*>(mac->getControlInfo());
            assert(phyInfo);
            DBG_MAC << "Sending a Packet. Frequency " << freq << " Priority" << lastAC << std::endl;
            sendDelayed(mac, RADIODELAY_11P, lowerLayerOut);
            statsSentPackets++;
        } else {   //not enough time left now
            DBG_MAC << "Too little Time left. This packet cannot be send in this slot." << std::endl;
            statsNumTooLittleTime++;
            //revoke TXOP
            myEDCA[activeChannel]->revokeTxOPs();
            delete mac;
            channelIdle();
            //do nothing. contention will automatically start after channel switch
        }
    }
}

void GCRSBaseMacLayer::setActiveChannel(t_channel state) {
    activeChannel = state;
    assert(state == type_CCH || (useSCH && state == type_SCH));
}

simtime_t GCRSBaseMacLayer::timeLeftInSlot() const {
    ASSERT(useSCH);
    return nextChannelSwitch->getArrivalTime() - simTime();
}

simtime_t GCRSBaseMacLayer::timeLeftTillGuardOver() const {
    ASSERT(useSCH);
    simtime_t sTime = simTime();
    if (sTime - nextChannelSwitch->getSendingTime() <= GUARD_INTERVAL_11P) {
        return GUARD_INTERVAL_11P
                - (sTime - nextChannelSwitch->getSendingTime());
    } else
        return 0;
}

/* checks if guard is active */
bool GCRSBaseMacLayer::guardActive() const {
    if (!useSCH)
        return false;
    if (simTime().dbl() - nextChannelSwitch->getSendingTime()
            <= GUARD_INTERVAL_11P)
        return true;
    return false;
}

void GCRSBaseMacLayer::attachSignal(Mac80211Pkt* mac, simtime_t startTime,
        double frequency) {
    int macPktlen = mac->getBitLength();
    simtime_t duration = PHY_HDR_PREAMBLE_DURATION + PHY_HDR_PLCPSIGNAL_DURATION
            + ((macPktlen + PHY_HDR_PSDU_HEADER_LENGTH) / bitrate);
    Signal* s = createSignal(startTime, duration, txPower, bitrate, frequency);
    MacToPhyControlInfo* cinfo = new MacToPhyControlInfo(s);
    mac->setControlInfo(cinfo);
}

Signal* GCRSBaseMacLayer::createSignal(simtime_t start, simtime_t length,
        double power, double bitrate, double frequency) {
    simtime_t end = start + length;
    //create signal with start at current simtime and passed length
    Signal* s = new Signal(start, length);

    //create and set tx power mapping
    ConstMapping* txPowerMapping = createSingleFrequencyMapping(start, end,
            frequency, 5.0e6, power);
    s->setTransmissionPower(txPowerMapping);
    Mapping* bitrateMapping = MappingUtils::createMapping(
            DimensionSet::timeDomain, Mapping::STEPS);

    Argument pos(start);
    bitrateMapping->setValue(pos, bitrate);

    pos.setTime(phyHeaderLength / bitrate);
    bitrateMapping->setValue(pos, bitrate);

    s->setBitrate(bitrateMapping);

    return s;
}

GCRSBaseMacLayer::t_access_category GCRSBaseMacLayer::mapPriority(int prio) {
    //dummy mapping function
    switch (prio) {
    case 0:
        return AC_BK;
    case 1:
        return AC_BE;
    case 2:
        return AC_VI;
    case 3:
        return AC_VO;
    default:
        opp_error("MacLayer received a packet with unknown priority");
        break;
    }
    return AC_VO;
}

void GCRSBaseMacLayer::channelBusy() {
    if (!idleChannel)
        return;

    //the channel turned busy because someone else is sending
    idleChannel = false;
    DBG_MAC<< "Channel turned busy: External sender" << std::endl;
    lastBusy = simTime();

    //channel turned busy
    if (nextMacEvent->isScheduled() == true) {
        cancelEvent(nextMacEvent);
    } else {
        //the edca subsystem was not doing anything anyway.
    }
    myEDCA[activeChannel]->stopContent(true, false);
}

void GCRSBaseMacLayer::channelBusySelf(bool generateTxOp) {

    //the channel turned busy because we're sending. we don't want our queues to go into backoff
    //internal contention is already handled in initiateTransmission

    if (!idleChannel)
        return;
    idleChannel = false;
    DBG_MAC<< "Channel turned busy: Switch or Self-Send" << std::endl;

    lastBusy = simTime();

    //channel turned busy
    if (nextMacEvent->isScheduled() == true) {
        cancelEvent(nextMacEvent);
    } else {
        //the edca subsystem was not doing anything anyway.
    }
    myEDCA[activeChannel]->stopContent(false, generateTxOp);
}

void GCRSBaseMacLayer::channelIdle(bool afterSwitch) {
    DBG_MAC<< "Channel turned idle: Switch: " << afterSwitch << std::endl;

    if (nextMacEvent->isScheduled() == true) {
        //this rare case can happen when another node's time has such a big offset
        //that the node sent a packet although we already changed the channel
        //the workaround is not trivial and requires a lot of changes to the phy and decider
        return;
        //opp_error("channel turned idle but contention timer was scheduled!");
    }

    idleChannel = true;

    simtime_t delay = 0;

    //account for 1609.4 guards
    if (afterSwitch) {
        //  delay = GUARD_INTERVAL_11P;
    }
    if (useSCH) {
        delay += timeLeftTillGuardOver();
    }

    //channel turned idle! lets start contention!
    lastIdle = delay + simTime();
    statsTotalBusyTime += simTime() - lastBusy;

    //get next Event from current EDCA subsystem
    simtime_t nextEvent = myEDCA[activeChannel]->startContent(lastIdle,guardActive());
    if (nextEvent != -1) {
        if ((!useSCH) || (nextEvent < nextChannelSwitch->getArrivalTime())) {
            scheduleAt(nextEvent,nextMacEvent);
            DBG_MAC << "next Event is at " << nextMacEvent->getArrivalTime().raw() << std::endl;
        }
        else {
            DBG_MAC << "Too little time in this interval. will not schedule macEvent" << std::endl;
            statsNumTooLittleTime++;
            myEDCA[activeChannel]->revokeTxOPs();
        }
    }
    else {
        DBG_MAC << "I don't have any new events in this EDCA sub system" << std::endl;
    }
}

void GCRSBaseMacLayer::checkBitrate(int bitrate) const {
    for (unsigned int i = 0; i < sizeof(BITRATES_80211P); i++) {
        if (bitrate == BITRATES_80211P[i])
            return;
    }
    opp_error(
            "Chosen Bitrate is not valid for 802.11p: Valid rates are: 3Mbps, 4.5Mbps, 6Mbps, 9Mbps, 12Mbps, 18Mbps, 24Mbps and 27Mbps. Please adjust your omnetpp.ini file accordingly.");
}

int GCRSBaseMacLayer::EDCA::createQueue(int aifsn, int cwMin, int cwMax,
        t_access_category ac) {
    if (myQueues.find(ac) != myQueues.end()) {
        opp_error(
                "You can only add one queue per Access Category per EDCA subsystem");
    }

    EDCAQueue newQueue(aifsn, cwMin, cwMax, ac);
    myQueues[ac] = newQueue;

    return ++numQueues;
}

int GCRSBaseMacLayer::EDCA::queuePacket(t_access_category ac,
        GCRSBaseNetPkt* msg) {

    if (maxQueueSize && myQueues[ac].queue.size() >= maxQueueSize) {
        delete msg;
        return -1;
    }
    myQueues[ac].queue.push(msg);
    return myQueues[ac].queue.size();
}

void GCRSBaseMacLayer::EDCA::backoff(t_access_category ac) {
    myQueues[ac].currentBackoff = intuniform(0, myQueues[ac].cwCur);
    statsSlotsBackoff += myQueues[ac].currentBackoff;
    statsNumBackoff++;
    DBG_MAC<< "Going into Backoff because channel was busy when new packet arrived from upperLayer" << std::endl;
}

simtime_t GCRSBaseMacLayer::EDCA::startContent(simtime_t idleSince,
        bool guardActive) {

    DBG_MAC<< "Restarting contention." << std::endl;
    simtime_t nextEvent = -1;
    simtime_t idleTime = SimTime().setRaw(std::max((int64_t)0,(simTime() - idleSince).raw()));

    lastStart = idleSince;

    DBG_MAC << "Channel is already idle for:" << idleTime << " since " << idleSince << std::endl;
    //this returns the nearest possible event in this EDCA subsystem after a busy channel
    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.queue.size() != 0) {
            /* 1609_4 says that when attempting to send (backoff == 0) when guard is active, a random backoff is invoked */
            if (guardActive == true && iter->second.currentBackoff == 0) {
                //cw is not increased
                iter->second.currentBackoff = intuniform(0,iter->second.cwCur);
                statsNumBackoff++;
            }

            simtime_t DIFS = iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P;

            //the next possible time to send can be in the past if the channel was idle for a long time, meaning we COULD have sent earlier if we had a packet
            simtime_t possibleNextEvent = DIFS + iter->second.currentBackoff * SLOTLENGTH_11P;
            DBG_MAC << "Waiting Time for Queue " << iter->first << ":" << possibleNextEvent << "=" << iter->second.aifsn << " * " << SLOTLENGTH_11P << " + " << SIFS_11P << "+" << iter->second.currentBackoff << "*" << SLOTLENGTH_11P << "; Idle time: " << idleTime << std::endl;
            if (idleTime > possibleNextEvent) {
                DBG_MAC << "Could have already send if we had it earlier" << std::endl;
                //we could have already sent. round up to next boundary
                simtime_t base = idleSince + DIFS;
                possibleNextEvent = simTime() - simtime_t().setRaw((simTime() - base).raw() % SLOTLENGTH_11P.raw()) + SLOTLENGTH_11P;
            }
            else {
                //we are gonna send in the future
                DBG_MAC << "Sending in the future" << std::endl;
                possibleNextEvent = idleSince + possibleNextEvent;
            }
            nextEvent == -1? nextEvent = possibleNextEvent : nextEvent = std::min(nextEvent,possibleNextEvent);

        }
    }
    return nextEvent;
}

void GCRSBaseMacLayer::EDCA::stopContent(bool allowBackoff, bool generateTxOp) {
    //update all Queues

    DBG_MAC<< "Stopping Contention at " << simTime().raw() << std::endl;

    simtime_t passedTime = simTime() - lastStart;
    DBG_MAC << "Channel was idle for " << passedTime << std::endl;
    lastStart = -1; //indicate that there was no last start
    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.currentBackoff != 0 || iter->second.queue.size() != 0) {
            //check how many slots we already waited until the chan became busy

            int oldBackoff = iter->second.currentBackoff;

            std::string info;
            if (passedTime < iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P) {
                //we didnt even make it one DIFS :(
                info.append(" No DIFS");
            }
            else {
                //decrease the backoff by one because we made it longer than one DIFS
                iter->second.currentBackoff--;

                //check how many slots we waited after the first DIFS
                int passedSlots = (int)((passedTime - SimTime(iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P)) / SLOTLENGTH_11P);

                DBG_MAC << "Passed slots after DIFS: " << passedSlots << std::endl;

                if (iter->second.queue.size() == 0) {
                    //this can be below 0 because of post transmit backoff -> backoff on empty queues will not generate macevents,
                    //we dont want to generate a txOP for empty queues
                    iter->second.currentBackoff -= std::min(iter->second.currentBackoff,passedSlots);
                    info.append(" PostCommit Over");
                }
                else {
                    iter->second.currentBackoff -= passedSlots;
                    if (iter->second.currentBackoff <= -1) {
                        if (generateTxOp) {
                            iter->second.txOP = true; info.append(" TXOP");
                        }
                        //else: this packet couldnt be sent because there was too little time. we could have generated a txop, but the channel switched
                        iter->second.currentBackoff = 0;
                    }
                }
            }
            DBG_MAC << "Updating backoff for Queue " << iter->first << ": " << oldBackoff << " -> " << iter->second.currentBackoff << info <<std::endl;
        }
    }
}

void GCRSBaseMacLayer::EDCA::postTransmit(t_access_category ac) {
    delete myQueues[ac].queue.front();
    myQueues[ac].queue.pop();
    myQueues[ac].cwCur = myQueues[ac].cwMin;
    //post transmit backoff
    myQueues[ac].currentBackoff = intuniform(0, myQueues[ac].cwCur);
    statsSlotsBackoff += myQueues[ac].currentBackoff;
    statsNumBackoff++;
    DBG_MAC<< "Queue " << ac << " will go into post-transmit backoff for " << myQueues[ac].currentBackoff << " slots" << std::endl;
}

void GCRSBaseMacLayer::EDCA::revokeTxOPs() {
    for (std::map<t_access_category, EDCAQueue>::iterator iter =
            myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.txOP == true) {
            iter->second.txOP = false;
            iter->second.currentBackoff = 0;
        }
    }
}

void GCRSBaseMacLayer::EDCA::cleanUp() {
    for (std::map<t_access_category, EDCAQueue>::iterator iter =
            myQueues.begin(); iter != myQueues.end(); iter++) {
        while (iter->second.queue.size() != 0) {
            delete iter->second.queue.front();
            iter->second.queue.pop();
        }
    }
    myQueues.clear();
}

GCRSBaseNetPkt* GCRSBaseMacLayer::EDCA::initiateTransmit(simtime_t lastIdle) {
    //iterate through the queues to return the packet we want to send
    GCRSBaseNetPkt* pktToSend = NULL;

    simtime_t idleTime = simTime() - lastIdle;

    DBG_MAC<< "Initiating transmit at " << simTime() << ". I've been idle since " << idleTime << std::endl;
    for (std::map<t_access_category, EDCAQueue>::iterator iter =
            myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.queue.size() != 0) {
            if (idleTime >= iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P
                    && iter->second.txOP == true) {

                DBG_MAC<< "Queue " << iter->first << " is ready to send!" << std::endl;

                iter->second.txOP = false;
                //this queue is ready to send
                if (pktToSend == NULL) {
                    pktToSend = iter->second.queue.front();
                }
                else {
                    //there was already another packet ready. we have to go increase cw and go into backoff. It's called internal contention and its wonderful

                    statsNumInternalContention++;
                    iter->second.cwCur = std::min(iter->second.cwMax,iter->second.cwCur*2);
                    iter->second.currentBackoff = intuniform(0,iter->second.cwCur);
                    DBG_MAC << "Internal contention for queue " << iter->first << " : "<< iter->second.currentBackoff << ". Increase cwCur to " << iter->second.cwCur << std::endl;
                }
            }
        }
    }

    if (pktToSend == NULL) {
        opp_error("No packet was ready");
    }
    return pktToSend;
}
