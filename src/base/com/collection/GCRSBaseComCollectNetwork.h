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

#ifndef GCRSBASECOMCOLLECTNETWORK_H_
#define GCRSBASECOMCOLLECTNETWORK_H_
#include "GCRSBaseComCollectNode.h"
#include "GCRSBaseComZone.h"
#include "Coord.h"
#include <vector>
#include "GCRSBaseComTTL.h"

class GCRSBaseComCollectNetwork {
public:
    enum state_category {
        SC_NULL = 0, SC_CREATED = 1, SC_EXPIRED = 2
    };

public:
    GCRSBaseComCollectNetwork();
    GCRSBaseComCollectNetwork(simtime_t ttl);
    virtual ~GCRSBaseComCollectNetwork();

    state_category getState() {
        return this->sc;
    }

    GCRSBaseComVin::VinL3Type getRootNodeVin(){
        if(this->rootNode == NULL)return GCRSBaseComVin::VINL3NULL;
        return this->rootNode->getVin();
    }

    GCRSBaseComCollectNode* getRootNode() {
        return this->rootNode;
    }

    simtime_t getCreateTime() {
        return this->networkTime.getCreateTime();
    }

    simtime_t getUpdateTIme(){
        return this->networkTime.getUpdateTime();
    }

    simtime_t getTTL() {
        return this->networkTime.getTTL();
    }

    simtime_t getExpireTime(){
        return this->networkTime.getExpireTime();
    }

    long getVersion(){
        return this->version;
    }

    int getNumRxNodesInZor() {
        return this->numRxNodesInZor;
    }

    int getNumRxNodesInZof(){
        return this->numRxNodesInZof;
    }

    int getNumRelayNodes() {
        return this->numRelayNodes;
    }

    int getMaxHops() {
        return this->maxHops;
    }

    simtime_t getMaxDelayTime(){
        return this->maxDelayTime;
    }

    void setState(state_category sc) {
        this->sc = sc;
    }

    void setUpdateTime(simtime_t t){
        this->networkTime.setUpdateTime(t);
    }

    void setTTL(simtime_t t) {
        this->networkTime.setTTL(t);
    }

    void updateVersion(){
        this->version++;
    }

    void setRootNode(GCRSBaseComVin::VinL3Type vin);
    void addRelayNode(GCRSBaseComVin::VinL3Type parentVin,
            GCRSBaseComVin::VinL3Type childVin, GCRSBaseComCollectNode::range_category rc);
    void cancelRelayNode(GCRSBaseComVin::VinL3Type vin);
    bool isInNetwork(GCRSBaseComVin::VinL3Type vin);

    bool isFinished();

protected:
    GCRSBaseComCollectNode* createRelayNode(GCRSBaseComVin::VinL3Type vin,
            simtime_t sendT, simtime_t receiveT, GCRSBaseComCollectNode::range_category rc);
    GCRSBaseComCollectNode* searchNodeInNetwork(GCRSBaseComVin::VinL3Type vin);
    bool isExpired(simtime_t currentT);
    GCRSBaseComCollectNode* searchNode(GCRSBaseComCollectNode* node,
            GCRSBaseComVin::VinL3Type vin);
    void conclusion(GCRSBaseComCollectNode* node, int depth);
    simtime_t calcMaxDelayTime();
    void cleanUp();

protected:
    state_category sc;
    GCRSBaseComCollectNode* rootNode;
    GCRSBaseComTTL networkTime;
    long version;
    std::vector<GCRSBaseComCollectNode*> farthestNodes;

    int numRxNodesInZor;
    int numRxNodesInZof;
    int numRelayNodes;
    int maxHops;
    simtime_t maxDelayTime;
};

#endif /* GCRSBASECOMCOLLECTNETWORK_H_ */
