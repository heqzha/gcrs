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

#include "GCRSDummyNetLayer.h"

Define_Module(GCRSDummyNetLayer)
;

void GCRSDummyNetLayer::initialize(int stage){
    GCRSBaseNetLayer::initialize(stage);
    if (stage == 0) {
        this->floodingTaskManager = new GCRSFloodingComTaskManager(100);
        this->tManager = this->floodingTaskManager;
    }
}

void GCRSDummyNetLayer::handleNewTask(long taskId){
    this->handleSendDownPkt(taskId);
}

void GCRSDummyNetLayer::handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone){
    this->handleSendDownPkt(taskId);
}

bool GCRSDummyNetLayer::handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone){
    if(zone == GCRSBaseComCollectNode::RC_ZOR)
        return true;
    return false;
}

void GCRSDummyNetLayer::handleSendDownPkt(long taskId){
    if (taskId < 0)
        return;
    GCRSBaseNetPkt* pkt = this->floodingTaskManager->getPkt(taskId);
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
