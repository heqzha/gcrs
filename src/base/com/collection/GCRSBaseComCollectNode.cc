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

#include "GCRSBaseComCollectNode.h"
#include <algorithm>//std::remove_if std::find_if
GCRSBaseComCollectNode::GCRSBaseComCollectNode() {
    this->sc = SC_RELAY;
    this->vin = GCRSBaseComVin::VINL3NULL;
    this->sendTime = 0.0f;
    this->receiveTime = 0.0f;
    this->vecChildrenNodes = NULL;
}

GCRSBaseComCollectNode::GCRSBaseComCollectNode(GCRSBaseComVin::VinL3Type vin,
        simtime_t sendT, simtime_t receiveT, range_category rc) {
    this->sc = SC_RELAY;
    this->vin = vin;
    this->sendTime = sendT;
    this->receiveTime = receiveT;
    this->rangeType = rc;
    this->vecChildrenNodes = new std::vector<GCRSBaseComCollectNode*>();
}

GCRSBaseComCollectNode::GCRSBaseComCollectNode(state_category sc,
        GCRSBaseComVin::VinL3Type vin, simtime_t sendT, simtime_t receiveT, range_category rc) {
    this->sc = sc;
    this->vin = vin;
    this->sendTime = sendT;
    this->receiveTime = receiveT;
    this->rangeType = rc;
    this->vecChildrenNodes = new std::vector<GCRSBaseComCollectNode*>();
}
GCRSBaseComCollectNode::~GCRSBaseComCollectNode() {
    if (this->vecChildrenNodes == NULL)
        return;
    this->cleanUp();
    delete this->vecChildrenNodes;
}

void GCRSBaseComCollectNode::addChildNode(GCRSBaseComCollectNode* node) {
    if (node == NULL || this->vecChildrenNodes == NULL) {
        return;
    }
    if (GCRSBaseComVin::isVinL3NULL(node->vin)
            || GCRSBaseComVin::isVinL3Broadcast(node->vin)) {
        return;
    }
    this->vecChildrenNodes->push_back(node);
}

GCRSBaseComCollectNode* GCRSBaseComCollectNode::getChildNodeByVin(
        GCRSBaseComVin::VinL3Type vin) {
    if (this->vecChildrenNodes == NULL || this->vecChildrenNodes->empty()) {
        return NULL;
    }
    std::vector<GCRSBaseComCollectNode*>::iterator iter;
    iter = std::find_if(this->vecChildrenNodes->begin(),
            this->vecChildrenNodes->end(), SearchNode(vin));
    if (iter == this->vecChildrenNodes->end()) {
        return NULL;
    }
    return (*iter);
}

std::vector<GCRSBaseComCollectNode*>* GCRSBaseComCollectNode::getChildrenNodes() {
    return this->vecChildrenNodes;
}

void GCRSBaseComCollectNode::cleanUp() {
    this->vecChildrenNodes->erase(
            std::remove_if(this->vecChildrenNodes->begin(),
                    this->vecChildrenNodes->end(), ClearAll()),
            this->vecChildrenNodes->end());
}

int GCRSBaseComCollectNode::getNumChildrenNodes() {
    return this->vecChildrenNodes->size();
}

bool GCRSBaseComCollectNode::isRelayNode() {
    return this->sc == SC_RELAY ? true : false;
}

bool GCRSBaseComCollectNode::isZorNode(){
    return this->rangeType == RC_ZOR ? true:false;
}

bool GCRSBaseComCollectNode::isZofNode(){
    return this->rangeType == RC_ZOF ? true:false;
}
