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

#include "GCRSROVERNetLayer.h"
#include "GCRSBaseComMath.h"

Define_Module(GCRSROVERNetLayer)
;

void GCRSROVERNetLayer::initialize(int stage) {
    GCRSBaseNetLayer::initialize(stage);
    if (stage == 0) {
        this->cwMax = hasPar("CWMAX") ? par("CWMAX").doubleValue() : 0.0f;
        this->st = hasPar("ST") ? par("ST").doubleValue() : 0.0f;

        unsigned int maxMessageBufferSize =
                hasPar("MAXMESSAGEBUFFERSIZE") ?
                        par("MAXMESSAGEBUFFERSIZE").longValue() : 0;
        this->roverTaskManager = new GCRSROVERComTaskManager(
                maxMessageBufferSize);
        this->tManager = this->roverTaskManager;
    }
}

void GCRSROVERNetLayer::handleNewTask(long taskId) {
    GCRSBaseNetPkt* reqPkt = this->roverTaskManager->getPkt(taskId);
    this->roverTaskManager->addData(taskId, PC_DATA,reqPkt);
    this->roverTaskManager->toRequest(taskId, PC_REQUEST);
    this->roverTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
}

void GCRSROVERNetLayer::handleScheduleTask(long taskId,
        GCRSBaseComCollectNode::range_category zone) {
    if (GCRSBaseComCollectNode::RC_ZOR == zone) {
        this->roverTaskManager->toReply(taskId, PC_REPLY);
    } else if (GCRSBaseComCollectNode::RC_ZOF == zone) {
        this->roverTaskManager->toRequest(taskId, PC_REQUEST);
    }
    this->roverTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
}

bool GCRSROVERNetLayer::handleSendUp(GCRSBaseNetPkt* pkt,
        GCRSBaseComCollectNode::range_category zone) {
    if (pkt == NULL)
        return false;
    if (PC_DATA == pkt->getKind() && GCRSBaseComCollectNode::RC_ZOR == zone) {
        return true;
    }
    return false;
}

bool GCRSROVERNetLayer::handleIsAck(GCRSBaseNetPkt* pkt,
        GCRSBaseComCollectNode::range_category zone) {
    long taskId = this->roverTaskManager->getTaskIdByPkt(pkt);
    if (taskId < 0)
        return false;
    int type = pkt->getKind();
    if (type == PC_REPLY) {
        if (this->roverTaskManager->hasDataPkt(taskId)) {
            this->roverTaskManager->toData(taskId, PC_DATA, pkt);
        }else{
            this->roverTaskManager->toReply(taskId, PC_REPLY);
        }
        return true;
    } else if (type == PC_DATA) {
        if(!this->roverTaskManager->hasDataPkt(taskId)){
            this->roverTaskManager->addData(taskId, PC_DATA, pkt);
        }
        this->roverTaskManager->toRequest(taskId, PC_REQUEST);
        return true;
    }
    return false;
}

void GCRSROVERNetLayer::handleTaskAck(long taskId,
        GCRSBaseComCollectNode::range_category zone) {
    this->roverTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
}

void GCRSROVERNetLayer::handleRunningEvent(long runningEventId) {
    long taskId = this->roverTaskManager->getTaskIdByRunningEventId(
            runningEventId);
    if (taskId < 0)
        return;

    if (this->roverTaskManager->isIdle(taskId)){
        //IDLE
        return;
    }else if(this->roverTaskManager->isReply(taskId)){
        //Reply
        this->handleSendDown(runningEventId);
    }else if(this->roverTaskManager->isRequest(taskId)){
        //Request
        this->handleSendDown(runningEventId);
    }else if(this->roverTaskManager->isData(taskId)){
        this->handleSendDown(runningEventId);
        this->roverTaskManager->toRequest(taskId,PC_REQUEST);
    }
    this->roverTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
}

double GCRSROVERNetLayer::calcBackoffTime() {
    return GCRSBaseComMath::geDoubleRandomNumber(0.0, this->cwMax) * this->st;
}
