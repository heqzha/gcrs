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

#include "GCRSDTSGNetLayer.h"
#include "GCRSBaseConst.h"
#include "GCRSBaseComMath.h"

#define EV_HEAD "GCRSDTSGNetLayer: "
#define EV_ERROR_HEAD "GCRSDTSGNetLayer:<ERROR> "
#define EV_WARNING_HEAD "GCRSDTSGNetLayer:<WARNING> "

Define_Module(GCRSDTSGNetLayer)
;

void GCRSDTSGNetLayer::initialize(int stage) {
    GCRSBaseNetLayer::initialize(stage);
    if(stage == 0){
        unsigned int maxMessageBufferSize =
                hasPar("MAXMESSAGEBUFFERSIZE") ?
                        par("MAXMESSAGEBUFFERSIZE").longValue() : 0;
        this->dtsgTaskManager = new GCRSDTSGComTaskManager(maxMessageBufferSize);
        this->tManager = this->dtsgTaskManager;
    }

}

void GCRSDTSGNetLayer::handleNewTask(long taskId) {
    GCRSBaseNetPkt* pkt = this->dtsgTaskManager->getPkt(taskId);
    if (pkt == NULL)
        return;
    double txRange = this->connectionManager->getMaxIterferenceDistance();
    Coord locForward = pkt->getLocForwad();
    Coord loc = this->vManager->getLocation(this->vin);

    this->dtsgTaskManager->setNextEventTime(taskId,this->calcCompetitionBackoffTime(txRange, locForward, loc));
}

void GCRSDTSGNetLayer::handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone){
    GCRSBaseNetPkt* pkt = this->dtsgTaskManager->getPkt(taskId);
    if (pkt == NULL)
        return;
    double txRange = this->connectionManager->getMaxIterferenceDistance();
    Coord locForward = pkt->getLocForwad();
    Coord loc = this->vManager->getLocation(this->vin);

    this->dtsgTaskManager->setNextEventTime(taskId,this->calcCompetitionBackoffTime(txRange, locForward, loc));
}

bool GCRSDTSGNetLayer::handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone){
    if(GCRSBaseComCollectNode::RC_ZOR == zone)
        return true;
    return false;
}

bool GCRSDTSGNetLayer::handleIsAck(GCRSBaseNetPkt* pkt,GCRSBaseComCollectNode::range_category zone){
    long taskId = this->dtsgTaskManager->getTaskIdByPkt(pkt);
    if(taskId < 0) return false;

    GCRSBaseNetPkt* oldPkt = this->dtsgTaskManager->getPkt(taskId);
    if(oldPkt->getVersion() < pkt->getVersion()){
        this->handleUpdateTask(pkt);
        return false;
    }else if(oldPkt->getVersion() > pkt->getVersion()){
        if(this->dtsgTaskManager->isSleep(taskId)){
            this->dtsgTaskManager->toRelay(taskId);
        }
        return false;
    }else{
        if (this->collectionService->isInZofNetworkRange(pkt->getNin(),
                        pkt->getLocForwad())){
            if (this->collectionService->isInZorNetworkRange(pkt->getNin(),
                            pkt->getLocForwad())) {
                this->dtsgTaskManager->rxAckFromIntendedVehicle(taskId);
            }else{
                this->dtsgTaskManager->rxAckFromHelpVehicle(taskId);
            }
        }
        switch(zone){
        case GCRSBaseComCollectNode::RC_ZOR:{
            if(this->dtsgTaskManager->getAckFromIntendedVehicle(taskId) > 0 || this->dtsgTaskManager->getAckFromHelpVehicle(taskId) > 2){
                return true;
            }
        }
        case GCRSBaseComCollectNode::RC_ZOF:{
            if(this->dtsgTaskManager->getAckFromIntendedVehicle(taskId) > 2 || this->dtsgTaskManager->getAckFromHelpVehicle(taskId) > 0){
                return true;
            }
        }
        default:{
            return false;
        }
        }
        return false;
    }
}

void GCRSDTSGNetLayer::handleTaskAck(long taskId, GCRSBaseComCollectNode::range_category zone){
    this->dtsgTaskManager->toSleep(taskId);
}

void GCRSDTSGNetLayer::handleTaskOutZone(GCRSBaseNetPkt* pkt, GCRSBaseComNin::NinL3Type nin){
    if(this->isInExtraRegion(pkt)){
        this->setPreStableFlg(pkt, false);
        this->handleTaskInZone(pkt,nin,GCRSBaseComCollectNode::RC_NONE);
    }
}

void GCRSDTSGNetLayer::handleRunningEvent(long runningEventId) {
    long taskId = this->dtsgTaskManager->getTaskIdByRunningEventId(
            runningEventId);
    if (taskId < 0)
        return;
    GCRSBaseNetPkt* pkt = this->dtsgTaskManager->getPkt(taskId);
    if(this->isInExtraRegion(pkt)){
        this->setPreStableFlg(pkt, false);
    }
    if (this->dtsgTaskManager->isIdle(taskId)) {
        //IDLE
        this->dtsgTaskManager->toRelay(taskId);
        this->handleSendDown(runningEventId);
        this->dtsgTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
    } else if (this->dtsgTaskManager->isRelay(taskId)) {
        //RELAY
        if(this->getPreStableFlg(pkt)){
            this->handleSendDown(runningEventId);
        }else{
            this->dtsgTaskManager->toSleep(taskId);
        }
        this->dtsgTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
    } else if (this->dtsgTaskManager->isSleep(taskId)) {
        //SLEEP
        if(this->isInExtraRegion(pkt)){
            this->dtsgTaskManager->toKeepMesssageAlive(taskId);
        }
        this->dtsgTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
    } else if (this->dtsgTaskManager->isKeepMessageAlive(taskId)) {
        //KEEP MESSAGE ALIVE
        this->handleSendDown(runningEventId);
        this->dtsgTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
    }else{
        //CANCEL
        this->dtsgTaskManager->setNextEventTime(taskId, -1.0f);
    }

}

GCRSBaseNetPkt* GCRSDTSGNetLayer::packetBaseNetPkt(const char *name, int kind,
        cObject* cInfo){
    GCRSDTSGNetPkt* pkt =new GCRSDTSGNetPkt(name, kind);
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
    pkt->setPreStableFlg(true);
    return pkt;
}

bool GCRSDTSGNetLayer::isInExtraRegion(GCRSBaseNetPkt* pkt){
    GCRSBaseVehicleManager::VehicleParams vPars = this->vManager->getVehicleParams(this->vin);
    if(this->collectionService->isInZofNetworkRange(pkt->getNin(), vPars.location)) return false;

    GCRSBaseCollectionService::NetworkParams zofPars = this->collectionService->getNetworkParameters(pkt->getNin(), GCRSBaseComCollectNode::RC_ZOF);
    double numVehicle = static_cast<double>(this->collectionService->getNumVehiclePassThroughZof(pkt->getNin()));
    Coord loc = GCRSBaseComMath::tranCoordWorldtoLocal(vPars.location, zofPars.location, zofPars.direction);
    double extra = this->calcExtraRegionLength(zofPars.length, numVehicle / zofPars.length);

    if(GCRSBaseComMath::isInRectangleRange(loc, zofPars.length + 2.0f * extra, zofPars.width)){
        return true;
    }
    return false;
}

GCRSDTSGNetPkt* GCRSDTSGNetLayer::convertBasePktToDTSGPkt(GCRSBaseNetPkt* pkt){
    return dynamic_cast<GCRSDTSGNetPkt*>(pkt);
}

bool GCRSDTSGNetLayer::getPreStableFlg(GCRSBaseNetPkt* pkt){
    GCRSDTSGNetPkt* dtsgPkt = this->convertBasePktToDTSGPkt(pkt);
    return dtsgPkt->getPreStableFlg();
}

void GCRSDTSGNetLayer::setPreStableFlg(GCRSBaseNetPkt* pkt, bool flg){
    GCRSDTSGNetPkt* dtsgPkt = this->convertBasePktToDTSGPkt(pkt);
    dtsgPkt->setPreStableFlg(flg);
}

double GCRSDTSGNetLayer::calcCompetitionBackoffTime(double txRange, Coord srcLoc, Coord myLoc){
    if(GCRSBaseComMath::calcDistance(srcLoc, myLoc) > 0){
        double backoff = this->calcBackoffTime();
        double distance = GCRSBaseComMath::calcDistance(srcLoc, myLoc);
        double sleep = backoff * (txRange/distance);
        if(sleep > MAXTIME.dbl()){
            return 0.0f;
        }
        return sleep;
    }else{
        double backoff = this->calcBackoffTime();
        if(backoff > MAXTIME.dbl()){
            return 0.0f;
        }
        return backoff;
    }

}

double GCRSDTSGNetLayer::calcBackoffTime(){
    GCRSBaseVehicleManager::VehicleParams vPars = this->vManager->getVehicleParams(this->vin);
    double speed = GCRSBaseComMath::convertVectorToScalar(vPars.speed);
    double speedMax = vPars.speedMax;
    double txRange = this->connectionManager->getMaxIterferenceDistance();

    return (2.0f*txRange)/(speed + speedMax);
}

double GCRSDTSGNetLayer::calcExtraRegionLength(double zoneLength, double vehicleDensity){
    if(vehicleDensity > 0.0f){
        return zoneLength/vehicleDensity;
    }
    return 0.0f;
}
