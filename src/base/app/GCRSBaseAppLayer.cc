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

#include "GCRSBaseAppLayer.h"
#include "GCRSBaseComNetwControlInfo.h"
#include "GCRSBaseConst.h"
#include "GCRSBaseComMath.h"
#include "Convert.h"

#define EV_HEAD "GCRSBaseAppLayer: "
#define EV_ERROR_HEAD "GCRSBaseAppLayer: <ERROR> "
#define EV_WARNING_HEAD "GCRSBaseAppLayer: <WARNING> "

#define PRIORITY_EVENT_MESSAGE 1

Define_Module(GCRSBaseAppLayer)
;

void GCRSBaseAppLayer::initialize(int stage) {
    BaseApplLayer::initialize(stage);
    if (stage == 0) {
        unsigned int MaxGeoBufferSize =
                hasPar("MAXGEOBUFFERSIZE") ?
                        par("MAXGEOBUFFERSIZE").longValue() : 0;
        this->geoInfoBuffer = GCRSBaseComGeoInfoBuffer(MaxGeoBufferSize);
        this->selfMsgInterval =
                hasPar("SELFMSGINTERVAL") ?
                        par("SELFMSGINTERVAL").doubleValue() : 0.0f;
        this->individualOffset =
                hasPar("INDIVIDUALOFFSET") ?
                        par("INDIVIDUALOFFSET").doubleValue() : 0.0f;
        this->isOnSch = hasPar("ISONSCH") ? par("ISONSCH").boolValue() : true;
        this->priorityClass =
                hasPar("PRIORITYCLASS") ? par("PRIORITYCLASS").longValue() : 3;

        this->traciMobility = GCRSBaseTraCIMobilityAccess().get(
                getParentModule());
        this->vManager = GCRSBaseVehicleManagerAccess().get();
        this->vin = this->traciMobility->getVehicleIdNum();
        this->nin = GCRSBaseComNin::NINL3NULL;
        this->collectionService = GCRSBaseCollectionServiceAccess().get();


        this->selfMsg = new cMessage("Self_Message", MC_SELF_MESSAGE);
        scheduleAt(simTime() + this->selfMsgInterval, this->selfMsg);
    }
}

void GCRSBaseAppLayer::finish() {
    if (this->selfMsg->isScheduled()) {
        cancelAndDelete(this->selfMsg);
    } else {
        delete (this->selfMsg);
    }
}

void GCRSBaseAppLayer::handleLowerMsg(cMessage* msg) {

    GCRSBasePkt* pkt = check_and_cast<GCRSBasePkt*>(msg);
    if (pkt == NULL) {
        EV<< EV_ERROR_HEAD << "The packet is NULL!"<<endl;
        return;
    }
    cObject* cInfo = pkt->removeControlInfo();
    if (cInfo == NULL) {
        delete pkt;
        EV<< EV_ERROR_HEAD << "The control information of packet is NULL!"<<endl;
    }
    GCRSBaseComNin::NinL3Type nin =
            GCRSBaseComNetwControlInfo::getNinFromControlInfo(cInfo);
    GCRSBaseComVin::VinL3Type vinSrc =
            GCRSBaseComNetwControlInfo::getSrcVinFromControlInfo(cInfo);
    GCRSBaseComVin::VinL3Type vinDest =
            GCRSBaseComNetwControlInfo::getDestVinFromControlInfo(cInfo);
    Coord location = GCRSBaseComNetwControlInfo::getSrcLocationFromControlInfo(
            cInfo);
    Coord speed = GCRSBaseComNetwControlInfo::getSrcSpeedFromControlInfo(cInfo);
    double speedMax = GCRSBaseComNetwControlInfo::getSrcSpeedMaxFromControlInfo(
            cInfo);
    int msgPriority =
            GCRSBaseComNetwControlInfo::getSrcMsgPriorityFromControlInfo(cInfo);
    simtime_t timestamp =
            GCRSBaseComNetwControlInfo::getTimestampFromControlInfo(cInfo);
    std::string name = "Message";
    if (msgPriority == PRIORITY_EVENT_MESSAGE) {
        name = "Accident Message";
        EV<< EV_HEAD << "Warning! An accident occurred in front!" << endl;
    }

    simtime_t ttl = this->collectionService->getNetworkTTL(nin);
    this->geoInfoBuffer.addGeoInfo(name, nin, vinSrc, vinDest, location, speed,
            speedMax, ttl, timestamp);

    delete cInfo;
    delete pkt;
}

void GCRSBaseAppLayer::handleSelfMsg(cMessage* msg) {
    if (msg == NULL) {
        EV<< EV_ERROR_HEAD << "Self message is NULL!"<<endl;
        return;
    }
    switch(msg->getKind()) {
        case MC_SELF_MESSAGE: {
            unsigned int bufferSize = this->geoInfoBuffer.getBufferSize();
            EV<< EV_HEAD <<"The number of Relay Nodes in buffer is " << bufferSize <<"." <<endl;
            int priority = PRIORITY_EVENT_MESSAGE;
            switch(this->vManager->getVehicleState(this->vin)) {
                case GCRSBaseComVehicleState::SC_NORMAL: {
                    EV<< EV_HEAD <<"The Vehicle State is Normal."<<endl;
                    break;
                }
                case GCRSBaseComVehicleState::SC_EVENT_INITIAL: {
                    double offset =
                    hasPar("OFFSET") ? par("OFFSET").doubleValue() : 0.0f;
                    simtime_t ttl = this->vManager->getEventDuration(this->vin);
                    GCRSBaseVehicleManager::VehicleParams vParams = this->vManager->getVehicleParams(this->vin);
                    double angle = GCRSBaseComMath::calcAngleWithDirection(Coord(1.0f,0.0f,0.0f), vParams.direction);
                    if(this->vManager->isAccidentEvent(this->vin)) {
                        EV << EV_HEAD << "An accident event occurred!"<<endl;
                        //Create Network
                        this->nin = this->collectionService->createNetwork(this->vin,ttl,vParams.location, -offset,angle,vParams.laneIndex);
                        sendPkt(preparePkt(GCRSBaseComNetwControlInfo::CC_CREATE, this->nin, this->priorityClass, GCRSBaseComVin::VINL3BROADCAST, priority, PC_ACCIDENT_MESSAGE));
                    } else if(this->vManager->isEmergencyEvent(this->vin)) {
                        EV << EV_HEAD << "An emergency event occurred!"<<endl;
                        //Create Network
                        this->nin = this->collectionService->createNetwork(this->vin,ttl,vParams.location, offset,angle,vParams.laneIndex);
                        sendPkt(preparePkt(GCRSBaseComNetwControlInfo::CC_CREATE, this->nin, this->priorityClass, GCRSBaseComVin::VINL3BROADCAST, priority, PC_EMERGENCY_MESSAGE));
                    }
                    this->vManager->updateVehicleState(this->vin, GCRSBaseComVehicleState::SC_EVENT_HANDLING);

                    break;
                }
                case GCRSBaseComVehicleState::SC_EVENT_HANDLING: {
                    if(this->nin != GCRSBaseComNin::NINL3NULL){
                        EV << EV_HEAD << "Event handling..." << endl;
                        this->handleEvent(this->vin);
                        simtime_t oldTtl = this->collectionService->getNetworkTTL(this->nin);
                        simtime_t newTtl = this->vManager->getEventDuration(this->vin);
                        if(newTtl > 0.0f && newTtl != oldTtl){
                            this->collectionService->updateNetworkTTL(this->nin,newTtl);
                            this->collectionService->updateNetworkVersion(this->nin);
                            if(this->vManager->isAccidentEvent(this->vin)) {
                                sendPkt(preparePkt(GCRSBaseComNetwControlInfo::CC_UPDATE, this->nin, this->priorityClass, GCRSBaseComVin::VINL3BROADCAST, priority, PC_ACCIDENT_MESSAGE));
                            }else if(this->vManager->isEmergencyEvent(this->vin)) {
                                sendPkt(preparePkt(GCRSBaseComNetwControlInfo::CC_UPDATE, this->nin, this->priorityClass, GCRSBaseComVin::VINL3BROADCAST, priority, PC_EMERGENCY_MESSAGE));
                            }
                        }
                    }else{
                        EV << EV_ERROR_HEAD << "The Network Identification Number is Unknown!"<<endl;
                    }
                    break;
                }
                default: {
                    EV << EV_WARNING_HEAD << "The Vehicle State is Unknown!"<<endl;
                    break;
                }
            }
            scheduleAt(simTime() + this->selfMsgInterval, this->selfMsg);
            break;
        }
        default: {
            EV<< EV_WARNING_HEAD <<"HandleSelfMessage got unexpected message of kind " << msg->getKind() << endl;
            delete msg;
            break;
        }
    }
}

GCRSBasePkt* GCRSBaseAppLayer::preparePkt( int ctrlType, GCRSBaseComNin::NinL3Type nin,
        int priorityClass, GCRSBaseComVin::VinL3Type dest, int priority,
        int pktType) {
    GCRSBasePkt* pkt = new GCRSBasePkt("GCRSBasePkt", pktType);
    pkt->setPriorityClass(priorityClass);
    t_channel channel = this->isOnSch ? type_SCH : type_CCH;
    GCRSBaseComNetwControlInfo::setControlInfo(pkt, ctrlType,dest, channel, priority,
            nin);
    return pkt;
}

void GCRSBaseAppLayer::sendPkt(GCRSBasePkt* pkt) {
    sendDelayedDown(pkt, this->individualOffset);
    EV<< EV_HEAD <<"Send a new Message"<<endl;
}

