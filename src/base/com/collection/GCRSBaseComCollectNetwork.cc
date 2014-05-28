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

#include "GCRSBaseComCollectNetwork.h"

GCRSBaseComCollectNetwork::GCRSBaseComCollectNetwork() {
    this->sc = SC_NULL;
    this->rootNode = NULL;
    this->networkTime.setCreateTime(simTime());
    this->networkTime.setTTL(0.0f);
    this->version = 0;

    this->numRxNodesInZor = 0;
    this->numRxNodesInZof = 0;
    this->numRelayNodes = 0;
    this->maxHops = 0;
    this->maxDelayTime = 0.0f;

}

GCRSBaseComCollectNetwork::GCRSBaseComCollectNetwork(simtime_t ttl) {
    this->sc = SC_CREATED;
    this->rootNode = NULL;
    this->networkTime.setCreateTime(simTime());
    this->networkTime.setTTL(ttl);
    this->version = 0;

    this->numRxNodesInZor = 0;
    this->numRxNodesInZof = 0;
    this->numRelayNodes = 0;
    this->maxHops = 0;
    this->maxDelayTime = 0.0f;
}

GCRSBaseComCollectNetwork::~GCRSBaseComCollectNetwork() {
    this->cleanUp();
}

GCRSBaseComCollectNode* GCRSBaseComCollectNetwork::createRelayNode(
        GCRSBaseComVin::VinL3Type vin, simtime_t sendT, simtime_t receiveT, GCRSBaseComCollectNode::range_category rc) {

    if (GCRSBaseComVin::isVinL3NULL(vin) || GCRSBaseComVin::isVinL3Broadcast(vin)) {
        return NULL;
    }

    GCRSBaseComCollectNode* node = new GCRSBaseComCollectNode(
            GCRSBaseComCollectNode::SC_RELAY, vin, sendT, receiveT, rc);

    return node;
}

void GCRSBaseComCollectNetwork::setRootNode(GCRSBaseComVin::VinL3Type vin){
    this->rootNode = createRelayNode(vin, 0.0f, 0.0f, GCRSBaseComCollectNode::RC_ZOR);
}

void GCRSBaseComCollectNetwork::addRelayNode(
        GCRSBaseComVin::VinL3Type parentVin,
        GCRSBaseComVin::VinL3Type childVin, GCRSBaseComCollectNode::range_category rc, simtime_t parentSendTime) {
    GCRSBaseComCollectNode* parentNode = this->searchNodeInNetwork(parentVin);
    if(parentNode == NULL)
        return;
    GCRSBaseComCollectNode* childNode = parentNode->getChildNodeByVin(childVin);
    if(childNode != NULL)
        return;
    //Store the time of receiving message from parent node.
    childNode = createRelayNode(childVin, parentSendTime, simTime(), rc);
    if(childNode == NULL)
        return;
    parentNode->addChildNode(childNode);
}

void GCRSBaseComCollectNetwork::cancelRelayNode(GCRSBaseComVin::VinL3Type vin) {
    GCRSBaseComCollectNode* node = this->searchNodeInNetwork(vin);
    if(node == NULL){
        EV<< vin<<endl;
    }
    node->setState(GCRSBaseComCollectNode::SC_CANCEL);
}

bool GCRSBaseComCollectNetwork::isExpired(simtime_t currentT) {
    return this->networkTime.isExpires(currentT);
}

bool GCRSBaseComCollectNetwork::isInNetwork(GCRSBaseComVin::VinL3Type vin) {
    GCRSBaseComCollectNode* node = searchNodeInNetwork(vin);
    if (node != NULL) {
        return true;
    }
    return false;
}

void GCRSBaseComCollectNetwork::cleanUp() {
    if (this->rootNode != NULL) {
        delete rootNode;
    }
}

GCRSBaseComCollectNode* GCRSBaseComCollectNetwork::searchNodeInNetwork(
        GCRSBaseComVin::VinL3Type vin) {
    return searchNode(this->rootNode, vin);
}

GCRSBaseComCollectNode* GCRSBaseComCollectNetwork::searchNode(
        GCRSBaseComCollectNode* node, GCRSBaseComVin::VinL3Type vin) {
    if (node == NULL)
        return NULL;
    GCRSBaseComVin::VinL3Type nodeVin =node->getVin();
    if (nodeVin == vin) {
        return node;
    }

    std::vector<GCRSBaseComCollectNode*>::iterator iter;
    for (iter = node->getChildrenNodes()->begin();iter != node->getChildrenNodes()->end(); ++iter) {
        GCRSBaseComCollectNode* target = searchNode((*iter), vin);
        if (target != NULL) {
            return target;
        }
    }
    return NULL;
}

/*void GCRSBaseComCollectNetwork::conclusion(GCRSBaseComCollectNode* node,
        int depth) {
    if (node == NULL)
        return;
    if(node->getState() != GCRSBaseComCollectNode::SC_RELAY && node->getState() != GCRSBaseComCollectNode::SC_CANCEL)
        return;

    if (node->getChildrenNodes() == NULL || node->getChildrenNodes()->empty()) {
        if (this->maxHops <= depth) {
            this->maxHops = depth;
            if(node != this->rootNode){
                this->farthestNodes.push_back(node);
            }
        }
        return;
    }
    std::vector<GCRSBaseComCollectNode*>::iterator iter;
    for (iter = node->getChildrenNodes()->begin();
            iter != node->getChildrenNodes()->end(); ++iter) {
        conclusion((*iter), depth + 1);
        if ((*iter)->isRelayNode()) {
            this->numRelayNodes += 1;
        }
        if((*iter)->isZorNode()){
            this->numRxNodesInZor += 1;
        }
        if((*iter)->isZorNode() || (*iter)->isZofNode()){
            this->numRxNodesInZof += 1;
        }
    }
}*/

void GCRSBaseComCollectNetwork::conclusion(GCRSBaseComCollectNode* node) {
    if (node == NULL)
        return;
    if(node->getState() != GCRSBaseComCollectNode::SC_RELAY && node->getState() != GCRSBaseComCollectNode::SC_CANCEL)
        return;

    if (node->getChildrenNodes() == NULL || node->getChildrenNodes()->empty()) {
        if(this->maxHopNodeStack.size() < this->nodeStack.size()){
            this->maxHopNodeStack = this->nodeStack;
            this->maxHops = this->maxHopNodeStack.size();
        }
        return;
    }

    std::vector<GCRSBaseComCollectNode*>::iterator iter;
    for (iter = node->getChildrenNodes()->begin();
            iter != node->getChildrenNodes()->end(); ++iter) {
        this->nodeStack.push_back((*iter));
        conclusion((*iter));

        if ((*iter)->isRelayNode()) {
            this->numRelayNodes += 1;
        }
        if((*iter)->isZorNode()){
            this->numRxNodesInZor += 1;
        }
        if((*iter)->isZorNode() || (*iter)->isZofNode()){
            this->numRxNodesInZof += 1;
        }

        this->nodeStack.pop_back();
    }

}

/*simtime_t GCRSBaseComCollectNetwork::calcMaxDelayTime() {

    if(this->rootNode == NULL){
        EV<<"NULL";
    }
    simtime_t delay = 0.0f;


    if (this->farthestNodes.empty()) {
        return delay;
    }

    std::vector<GCRSBaseComCollectNode*>::iterator iter;
    for (iter = this->farthestNodes.begin();
            iter != this->farthestNodes.end(); ++iter) {
        simtime_t delayTmp = (*iter)->getReceiveTime()
                - this->rootNode->getSendTime();
        if (delayTmp > delay) {
            delay = delayTmp;
        }
    }

    return delay;

}*/

simtime_t GCRSBaseComCollectNetwork::calcMaxDelayTime() {
    if (this->rootNode == NULL) {
        EV << "NULL";
    }
    simtime_t delay = 0.0f;
    simtime_t maxDelay = 0.0f;

    if (this->maxHopNodeStack.empty()) {
        return delay;
    }
    std::vector<GCRSBaseComCollectNode*>::iterator iter;
    for (iter = this->maxHopNodeStack.begin();
            iter != this->maxHopNodeStack.end(); ++iter) {
            delay = (*iter)->getReceiveTime() - (*iter)->getSendTime();
            this->delayTimePerHop.push_back(delay);
            maxDelay += delay;
    }
    return maxDelay;
}

bool GCRSBaseComCollectNetwork::isFinished() {
    if(this->networkTime.isExpires(simTime())){
        this->sc = SC_EXPIRED;
        this->conclusion(this->rootNode);
        this->maxDelayTime = this->calcMaxDelayTime();
        return true;
    }
    return false;
}
