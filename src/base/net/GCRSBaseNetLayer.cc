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

#include "GCRSBaseNetLayer.h"
#include <algorithm>//std::remove_if
#include "GCRSBaseConst.h"
#include "GCRSBaseComMath.h"
#include "GCRSBaseComNin.h"

#define EV_HEAD "GCRSBaseNetLayer: "
#define EV_ERROR_HEAD "GCRSBaseNetLayer:<ERROR> "
#define EV_WARNING_HEAD "GCRSBaseNetLayer:<WARNING> "

Define_Module(GCRSBaseNetLayer)
;

void GCRSBaseNetLayer::initialize(int stage) {
    BaseNetwLayer::initialize(stage);
    if (stage == 0) {
        /*
         * Vehicle State initialize
         */
        this->traciMobility = GCRSBaseTraCIMobilityAccess().get(
                getParentModule());
        this->vManager =
                FindModule<GCRSBaseVehicleManager*>::findGlobalModule();
        this->vin = this->traciMobility->getVehicleIdNum();
        this->collectionService = GCRSBaseCollectionServiceAccess().get();
        connectionManager = GCRSBaseConnectionManagerAccess().get();
        this->tManager = NULL;

    }
}

void GCRSBaseNetLayer::finish() {
    this->cleanUp();
    if (this->tManager != NULL)
        delete this->tManager;
}

void GCRSBaseNetLayer::handleUpperMsg(cMessage* msg) {
    if (msg == NULL)
        return;
    cObject* cInfo = msg->removeControlInfo();
    GCRSBaseNetPkt* pkt = this->packetBaseNetPkt(msg->getName(),
            PC_BASE_NETWORK_PKT, cInfo);
    if (pkt == NULL) {
        delete msg;
        return;
    }
    assert(static_cast<cPacket*>(msg));
    pkt->encapsulate(static_cast<cPacket*>(msg));
    int ctrlType = GCRSBaseComNetwControlInfo::getCtrlType(cInfo);
    if(ctrlType == GCRSBaseComNetwControlInfo::CC_CREATE){
        this->handleCreateTask(pkt);
    }else if(ctrlType == GCRSBaseComNetwControlInfo::CC_UPDATE){
        this->handleUpdateTask(pkt);
    }
    delete cInfo;
    delete pkt;

}

void GCRSBaseNetLayer::handleLowerMsg(cMessage* msg) {
    GCRSBaseNetPkt* pkt = check_and_cast<GCRSBaseNetPkt*>(msg);
    if (pkt == NULL) {
        EV<< EV_ERROR_HEAD <<"The Packet is NULL!"<<endl;
        return;
    }
    if (this->tManager == NULL) {
        EV<< EV_ERROR_HEAD << "The initialization of Task Manager is failed!" << endl;
        delete pkt;
        return;
    }
    if (!GCRSBaseComVin::isVinL3Broadcast(pkt->getVinDest())
            && this->vin != pkt->getVinDest()) {
        delete pkt;
        return;
    }
    GCRSBaseVehicleManager::VehicleParams vParams =
            this->vManager->getVehicleParams(this->vin);
    Coord location = vParams.location;
    if (location == Coord::ZERO) {
        EV<< EV_ERROR_HEAD <<"Can not get own location!"<<endl;
        delete pkt;
        return;
    }
    EV<< EV_HEAD << "The own location is ("<<location.x<<", "<<location.y <<", "<<location.z<<")"<<endl;

    GCRSBaseComCollectNode::range_category zone =
            GCRSBaseComCollectNode::RC_NONE;
    GCRSBaseComNin::NinL3Type nin = pkt->getNin();
    simtime_t expired = this->collectionService->getNetworkCreateTime(nin) + this->collectionService->getNetworkTTL(nin);
    if(simTime() >= expired){
        EV << EV_HEAD << "This packet expired."<<endl;
        delete pkt;
        return;
    }
    if (this->collectionService->isInZofNetworkRange(nin, location)) {
        if (this->collectionService->isInZorNetworkRange(nin, location)) {
            /*
             * In ZOR
             */
            zone = GCRSBaseComCollectNode::RC_ZOR;
            EV<< EV_HEAD << "The packet " << pkt->getVinOriginSrc() << " - " <<pkt->getTimestamp() << "is in ZOR "<< pkt->getNin()<<"."<<endl;
            this->handleTaskInZone(pkt, nin, zone);
        } else {
            /*
             * In ZOF
             */
            EV<< EV_HEAD << "The packet " << pkt->getVinOriginSrc() << " - " <<pkt->getTimestamp() << "is in ZOF "<< pkt->getNin()<<"."<<endl;
            zone = GCRSBaseComCollectNode::RC_ZOF;
            this->handleTaskInZone(pkt, nin,zone);
        }
    } else {
        EV << EV_HEAD << "The packet " << pkt->getVinOriginSrc() << " - " <<pkt->getTimestamp() << "is not in ZOR/ZOF "<< pkt->getNin()<<"."<<endl;
        this->handleTaskOutZone(pkt,nin);
    }

    if (this->handleSendUp(pkt, zone)) {
        //Send to Application Layer
        GCRSBaseNetPkt* cpNetPkt = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
        sendUp(this->decapsMsg(cpNetPkt));
    }

    delete pkt;
}

void GCRSBaseNetLayer::handleSelfMsg(cMessage* msg) {
    if (msg == NULL) {
        return;
    }
    switch (msg->getKind()) {
    case MC_RUNNING: {
        this->handleRunningEvent(msg->getId()); //Set task next event time
        long taskId = this->tManager->getTaskIdByRunningEventId(msg->getId());
        this->handleScheduleRunningEvent(taskId);
        break;
    }
    case MC_EXPIRE: {
        this->handleExpireEvent(msg->getId());
        break;
    }
    default: {
        break;
    }
    }
}

void GCRSBaseNetLayer::handleLowerControl(cMessage* msg) {

}

void GCRSBaseNetLayer::handleUpperControl(cMessage * msg) {

}

cMessage* GCRSBaseNetLayer::decapsMsg(GCRSBaseNetPkt* pkt) {
    cMessage *m = pkt->decapsulate();
    long version = this->collectionService->getNetworkVersion(pkt->getNin());
    GCRSBaseComNetwControlInfo::setControlInfo(m, version,pkt->getVinOriginSrc(),
            pkt->getVinDest(), pkt->getLocSrc(), pkt->getSpeedSrc(),
            pkt->getSpeedMaxSrc(), pkt->getChannelNumber(), pkt->getPriority(),
            pkt->getNin(), pkt->getTimestamp());
    delete pkt;
    return m;
}

NetwPkt* GCRSBaseNetLayer::encapsMsg(cPacket*) {
    return NULL;
}

cObject * const GCRSBaseNetLayer::setDownControlInfo(cMessage * const pMsg,
        const LAddress::L2Type& pDestAddr) {
    return NULL;
}

cObject * const GCRSBaseNetLayer::setUpControlInfo(cMessage * const pMsg,
        const LAddress::L3Type& pSrcAddr) {
    return NULL;
}

long GCRSBaseNetLayer::handleTask(GCRSBaseNetPkt* pkt) {
    if (pkt == NULL)
        return -1;
    cMessage* runningEvent = new cMessage("Running", MC_RUNNING);
    cMessage* expireEvent = new cMessage("Expire", MC_EXPIRE);
    simtime_t expireTime = this->collectionService->getNetworkExipreTime(pkt->getNin());

    long taskId = this->tManager->addTask(runningEvent->getId(),
            expireEvent->getId(), pkt, expireTime);
    if (taskId >= 0) {
        this->eventBuffer.push_back(runningEvent);
        this->eventBuffer.push_back(expireEvent);
    } else {
        delete runningEvent;
        delete expireEvent;
    }
    return taskId;
}

void GCRSBaseNetLayer::handleCreateTask(GCRSBaseNetPkt* pkt){
    long taskId = this->handleTask(pkt);
    if (taskId >= 0) {
        this->handleNewTask(taskId); //Set task next event time
        this->handleScheduleExpireEvent(taskId);
        this->handleScheduleRunningEvent(taskId);
    }
}

void GCRSBaseNetLayer::handleUpdateTask(GCRSBaseNetPkt* pkt){
    long taskId = this->tManager->getTaskIdByPkt(pkt);
    if(taskId < 0)return;
    long expireEventId = this->tManager->getExpireEventId(taskId);
    this->handleExpireEvent(expireEventId);
    this->handleCreateTask(pkt);
}

void GCRSBaseNetLayer::handleScheduleRunningEvent(long taskId) {
    long eventId = this->tManager->getRunningEventId(taskId);
    simtime_t t = this->tManager->getNextEventTime(taskId);
    if(t > 0){
        this->handleSchedule(eventId, simTime() + t);
    }
}

void GCRSBaseNetLayer::handleScheduleExpireEvent(long taskId) {
    long eventId = this->tManager->getExpireEventId(taskId);
    simtime_t t = this->tManager->getExpireEventTime(taskId);
    this->handleSchedule(eventId, t);
}

bool GCRSBaseNetLayer::handleSchedule(long eventId, simtime_t t) {
    if (eventId >= 0) {
        cMessage* event = this->seachEvent(eventId);
        scheduleAt(t, event);
        return true;
    }
    return false;
}

void GCRSBaseNetLayer::handleExpireEvent(long expireEventId) {
    long taskId = this->tManager->getTaskIdByExpireEventId(expireEventId);
    if (taskId >= 0) {
        long runningEventId = this->tManager->getRunningEventId(taskId);
        if (runningEventId > 0) {
            this->deleteEvent(runningEventId);
        }
        this->deleteEvent(expireEventId);
        this->tManager->deleteTask(taskId);
    }
}

GCRSBaseNetPkt* GCRSBaseNetLayer::packetBaseNetPkt(const char *name, int kind,
        cObject* cInfo) {
    GCRSBaseNetPkt* pkt = new GCRSBaseNetPkt(name, kind);
    pkt->setByteLength(this->headerLength);

    if (cInfo == NULL) {
        EV<< EV_ERROR_HEAD <<"Application layer did not specify geogrGCRSaphic information\n"
        << "\t drop this message\n";
        delete pkt;
        return NULL;
    }
    GCRSBaseComVin::VinL3Type destVin =
            GCRSBaseComNetwControlInfo::getDestVinFromControlInfo(cInfo);
    if (GCRSBaseComVin::isVinL3NULL(destVin)) {
        EV<< EV_WARNING_HEAD <<"Application layer did not specify a destination L3 Vin\n"
        << "\t using broadcast address instead\n";
        destVin = GCRSBaseComVin::VINL3BROADCAST;
    }
    int channelType =
            GCRSBaseComNetwControlInfo::getSrcTxChannelTypeFromControlInfo(
                    cInfo);
    int priority = GCRSBaseComNetwControlInfo::getSrcMsgPriorityFromControlInfo(
            cInfo);
    GCRSBaseComNin::NinL3Type nin =
            GCRSBaseComNetwControlInfo::getNinFromControlInfo(cInfo);
    pkt->setVinOriginSrc(this->vin);
    pkt->setVinForwardSrc(GCRSBaseComVin::VINL3NULL);
    pkt->setVinDest(destVin);
    pkt->setPriority(priority);
    switch (channelType) {
    //will be rewritten at Mac layer to actual Service Channel.
    case type_SCH:
        pkt->setChannelNumber(Channels::SCH1);
        break;
    case type_CCH:
        pkt->setChannelNumber(Channels::CCH);
        break;
    default:
        EV<< EV_ERROR_HEAD << "The channel number is incorrect!"<<endl;
        break;
    }
    GCRSBaseVehicleManager::VehicleParams vParams =
            this->vManager->getVehicleParams(this->vin);
    pkt->setLocSrc(vParams.location);
    pkt->setSpeedSrc(vParams.speed);
    pkt->setSpeedMaxSrc(vParams.speedMax);
    pkt->setVinForwardSrc(this->vin);
    pkt->setLocForwad(vParams.location);
    pkt->setSpeedForwad(vParams.speed);
    pkt->setSpeedMaxForwarding(vParams.speedMax);
    pkt->setNin(nin);
    pkt->setHops(0);
    //Forwarding timestamp will be set when send pkt
    pkt->setTimestampForwarding(0.0f);
    pkt->setTimestamp(simTime());
    long version = this->collectionService->getNetworkVersion(nin);
    pkt->setVersion(version);

    return pkt;
}

void GCRSBaseNetLayer::handleSendDown(long eventId) {
    long taskId = this->tManager->getTaskIdByRunningEventId(eventId);
    if (taskId < 0)
        return;
    GCRSBaseNetPkt* pkt = this->tManager->getPkt(taskId);
    if (pkt != NULL) {
        GCRSBaseNetPkt* cpNetPkt = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
        GCRSBaseVehicleManager::VehicleParams vParams =
                this->vManager->getVehicleParams(this->vin);
        cpNetPkt->setVinForwardSrc(this->vin);
        cpNetPkt->setLocForwad(vParams.location);
        cpNetPkt->setSpeedForwad(vParams.speed);
        cpNetPkt->setSpeedMaxForwarding(vParams.speedMax);
        cpNetPkt->setTimestampForwarding(simTime());
        cpNetPkt->setHops(pkt->getHops() + 1);
        sendDown(cpNetPkt);
    }
}

void GCRSBaseNetLayer::handleTaskInZone(GCRSBaseNetPkt* pkt,
        GCRSBaseComNin::NinL3Type nin,
        GCRSBaseComCollectNode::range_category zone) {
    GCRSBaseComVin::VinL3Type pVin = pkt->getVinForwardSrc();
    if(pVin == 5 && this->vin == 20){
        EV<<endl;
    }
    if (!this->tManager->hasSamePkt(pkt)) {
        long taskId = this->handleTask(pkt);
        if (taskId >= 0) {
            //Set Relay Node
            GCRSBaseComVin::VinL3Type parentVin = pkt->getVinForwardSrc();
            this->collectionService->addRelayNode(nin, parentVin, this->vin,
                    zone);
            EV<< EV_HEAD << "The message " << pkt->getVinOriginSrc()<< "-" << pkt->getTimestamp()<< " is added in message buffer"<<endl;
            EV<< EV_HEAD << "The size of Message Buffer is " << this->tManager->getBufferSize() <<"."<<endl;
            this->handleScheduleTask(taskId, zone); //Schedule task
            this->handleScheduleExpireEvent(taskId);
            this->handleScheduleRunningEvent(taskId);
        } else {
            EV<< EV_WARNING_HEAD << "The Message Buffer is full! The packet "<< pkt->getVinOriginSrc() << "-" << pkt->getTimestamp()<< " is abandoned."<<endl;
        }
    } else {
        if(this->handleIsAck(pkt, zone)) {
            EV << EV_HEAD << "The message " << pkt->getVinOriginSrc()<< "-" << pkt->getTimestamp()
            <<" is ACK message."<<endl;
            long taskId = this->tManager->getTaskIdByPkt(pkt);
            if(taskId >= 0) {
                //Cancel Relay Node
                this->collectionService->cancelRelayNode(nin,this->vin);
                this->handleTaskAck(taskId,zone);
            }
        }
    }
}

cMessage* GCRSBaseNetLayer::seachEvent(long eventId) {
    if (this->eventBuffer.empty())
        return NULL;
    std::vector<cMessage*>::iterator iter;
    iter = std::find_if(this->eventBuffer.begin(), this->eventBuffer.end(),
            SearchEvent(eventId));
    if (iter == this->eventBuffer.end()) {
        return NULL;
    }
    return (*iter);
}

void GCRSBaseNetLayer::deleteEvent(long eventId) {
    if (this->eventBuffer.empty())
        return;
    this->eventBuffer.erase(
            std::remove_if(this->eventBuffer.begin(), this->eventBuffer.end(),
                    DeleteEvent(eventId, this)), this->eventBuffer.end());

}

void GCRSBaseNetLayer::cleanUp() {
    if (this->eventBuffer.empty())
        return;
    this->eventBuffer.erase(
            std::remove_if(this->eventBuffer.begin(), this->eventBuffer.end(),
                    CleanUp(this)), this->eventBuffer.end());
}
