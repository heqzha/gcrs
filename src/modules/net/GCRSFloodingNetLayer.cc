//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY{} without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "GCRSFloodingNetLayer.h"
#include "GCRSBaseComMath.h"

Define_Module(GCRSFloodingNetLayer)
;

void GCRSFloodingNetLayer::initialize(int stage) {
    GCRSBaseNetLayer::initialize(stage);
    if (stage == 0) {
        this->cwMax = hasPar("CWMAX") ? par("CWMAX").doubleValue():0.0f;
        this->st = hasPar("ST")?par("ST").doubleValue():0.0f;

        unsigned int maxMessageBufferSize =
                hasPar("MAXMESSAGEBUFFERSIZE") ?
                        par("MAXMESSAGEBUFFERSIZE").longValue():0;

        this->floodingTaskManager = new GCRSFloodingComTaskManager(
                maxMessageBufferSize);
        this->tManager = this->floodingTaskManager;
    }
}

void GCRSFloodingNetLayer::handleTaskFromUpper(long taskId){
    this->floodingTaskManager->setNextEventTime(taskId,0.1f);
}

void GCRSFloodingNetLayer::handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone){
    this->floodingTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
}

bool GCRSFloodingNetLayer::handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone){
    if(zone == GCRSBaseComCollectNode::RC_ZOR)
        return true;
    return false;
}

void GCRSFloodingNetLayer::handleTaskAck(long taskId, GCRSBaseComCollectNode::range_category zone){
    this->floodingTaskManager->rxAck(taskId);
}

void GCRSFloodingNetLayer::handleRunningEvent(long runningEventId){
    long taskId = this->floodingTaskManager->getTaskIdByRunningEventId(runningEventId);
    if(taskId<0)return;
    if(!this->floodingTaskManager->isRxAck(taskId)){
        this->handleSendDown(runningEventId);
        this->floodingTaskManager->setNextEventTime(taskId, this->calcBackoffTime());
    }
}

double GCRSFloodingNetLayer::calcBackoffTime(){
    return GCRSBaseComMath::geDoubleRandomNumber(0.0, this->cwMax)*this->st;
}
