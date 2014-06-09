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

#include "GCRSDRGNetLayer.h"
#include "GCRSBaseComMath.h"

Define_Module(GCRSDRGNetLayer)
;

void GCRSDRGNetLayer::initialize(int stage) {
    GCRSBaseNetLayer::initialize(stage);
    if (stage == 0) {
        this->maxBOd = hasPar("MAXBOD") ? par("MAXBOD").doubleValue() : 0.01f;
        this->longBOd = hasPar("LONGBOD") ? par("LONGBOD").doubleValue() : 2.5f;
        this->maxReTx = hasPar("MAXRETX") ? par("MAXRETX").longValue() : 2;
        this->mimCW = hasPar("MINCW") ? par("MINCW").doubleValue() : 0.0f;
        this->maxCW = hasPar("MAXCW") ? par("MAXCW").doubleValue() : 0.002f;
        this->sd = hasPar("SD") ? par("SD").doubleValue() : 1.0f;
        this->epsilon = hasPar("EPSILON") ? par("EPSILON").doubleValue() : 0.5;
        double criterionAngle = hasPar("MAXCRITERIONANGLE") ?
                par("MAXCRITERIONANGLE").doubleValue() :
                135.0f; //135 degree

        this->maxCriterionAngle =GCRSBaseComMath::convertToRadian(criterionAngle);


        unsigned int maxMessageBufferSize =
                hasPar("MAXMESSAGEBUFFERSIZE") ?
                        par("MAXMESSAGEBUFFERSIZE").longValue() : 0;
        this->drgTaskManager = new GCRSDRGComTaskManager(maxMessageBufferSize);
        this->tManager = this->drgTaskManager;
    }
}

void GCRSDRGNetLayer::handleNewTask(long taskId) {
    GCRSBaseNetPkt* pkt = this->drgTaskManager->getPkt(taskId);
    if (pkt == NULL)
        return;
    Coord locForward = pkt->getLocForwad();
    Coord loc = this->vManager->getLocation(this->vin);
    double dist = GCRSBaseComMath::calcDistance(locForward, loc);
    double rtx = this->connectionManager->getMaxIterferenceDistance();
    simtime_t backoff = this->calcDistanceBOd(rtx, dist) + this->calcBackoffTime();
    this->drgTaskManager->setNextEventTime(taskId, backoff);
}

void GCRSDRGNetLayer::handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone){
    GCRSBaseNetPkt* pkt = this->drgTaskManager->getPkt(taskId);
    if (pkt == NULL)
        return;
    Coord locForward = pkt->getLocForwad();
    Coord loc = this->vManager->getLocation(this->vin);
    double dist = GCRSBaseComMath::calcDistance(locForward, loc);
    double rtx = this->connectionManager->getMaxIterferenceDistance();
    simtime_t backoff = this->calcDistanceBOd(rtx, dist) + this->calcBackoffTime();
    this->drgTaskManager->setNextEventTime(taskId, backoff);
}
bool GCRSDRGNetLayer::handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone){
    if(GCRSBaseComCollectNode::RC_ZOR == zone)
        return true;
    return false;
}

bool GCRSDRGNetLayer::handleIsAck(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone){
    long taskId = this->drgTaskManager->getTaskIdByPkt(pkt);
    if(taskId < 0)return false;
    Coord myLoc = this->vManager->getLocation(this->vin);
    GCRSBaseNetPkt* preNodePkt = this->drgTaskManager->getPkt(taskId);
    Coord preNode = preNodePkt->getLocForwad();
    Coord nextNode = pkt->getLocForwad();
    double dist = GCRSBaseComMath::calcDistance(preNode, nextNode);
    double rtx = this->connectionManager->getMaxIterferenceDistance();
    double criterionAngle = this->calcCriterionAngle(dist,rtx);
    if(criterionAngle >= this->maxCriterionAngle){
        return true;
    }
    return false;
}

void GCRSDRGNetLayer::handleTaskAck(long taskId, GCRSBaseComCollectNode::range_category zone) {
    GCRSBaseNetPkt* pkt = this->drgTaskManager->getPkt(taskId);
    double vMax = pkt->getSpeedMaxForwarding();
    double rTx = this->connectionManager->getMaxIterferenceDistance();
    simtime_t persisT = this->calcPersistenceTime(this->epsilon, rTx, vMax,
            this->mimCW.dbl(), this->maxCW.dbl());
    this->drgTaskManager->toKeepMesssageAlive(taskId);
    this->drgTaskManager->setNextEventTime(taskId, persisT);
}

void GCRSDRGNetLayer::handleRunningEvent(long runningEventId) {
    long taskId = this->drgTaskManager->getTaskIdByRunningEventId(
            runningEventId);
    if (taskId < 0)
        return;
    if (this->drgTaskManager->isIdle(taskId)) {
        //IDLE
        this->drgTaskManager->toRelay(taskId);
        this->handleSendDown(runningEventId);
        this->drgTaskManager->setNextEventTime(taskId, this->maxBOd);
    } else if (this->drgTaskManager->isRelay(taskId)) {
        //RELAY
        if (this->drgTaskManager->getReTx(taskId) >= this->maxReTx) {
            this->drgTaskManager->resetReTx(taskId);
            this->drgTaskManager->toSleep(taskId);
            this->drgTaskManager->setNextEventTime(taskId, this->longBOd);
        } else {
            this->drgTaskManager->reTx(taskId);
            this->handleSendDown(runningEventId);
            this->drgTaskManager->setNextEventTime(taskId, this->maxBOd);
        }
    } else if (this->drgTaskManager->isSleep(taskId)) {
        //SLEEP
        this->drgTaskManager->toRelay(taskId);
        this->handleSendDown(runningEventId);
        this->drgTaskManager->setNextEventTime(taskId, this->maxBOd);
    } else if (this->drgTaskManager->isKeepMessageAlive(taskId)) {
        //KEEP MESSAGE ALIVE
        this->handleSendDown(runningEventId);
    }
}

simtime_t GCRSDRGNetLayer::calcBackoffTime() {
    return GCRSBaseComMath::geDoubleRandomNumber(this->mimCW.dbl(),
            this->maxCW.dbl());
}

simtime_t GCRSDRGNetLayer::calcDistanceBOd(double Rtx, double distance) {
    if (Rtx == 0.0f)
        return 0.0f;
    return this->maxBOd * this->sd * abs((Rtx - distance) / Rtx);
}

simtime_t GCRSDRGNetLayer::calcPersistenceTime(double e, double rTx,
        double vMax, double minCW, double maxCW) {
    return e * (rTx / vMax)
            + GCRSBaseComMath::geDoubleRandomNumber(minCW, maxCW);
}

double GCRSDRGNetLayer::calcCriterionAngle(double distance, double rTx) {
    return 2 * asin(distance / (2 * rTx));
}
