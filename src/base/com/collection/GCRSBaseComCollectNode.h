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

#ifndef GCRSBASECOMCOLLECTNODE_H_
#define GCRSBASECOMCOLLECTNODE_H_
#include <vector>
#include <omnetpp.h>
#include "GCRSBaseComVin.h"

class GCRSBaseComCollectNode {
public:
    enum state_category {
        SC_RELAY = 0, SC_CANCEL = 1
    };
    enum range_category{
        RC_ZOR = 0, RC_ZOF = 1, RC_NONE = 3
    };
public:
    GCRSBaseComCollectNode();
    GCRSBaseComCollectNode(GCRSBaseComVin::VinL3Type vin, simtime_t sendT,
            simtime_t receiveT, range_category rc);
    GCRSBaseComCollectNode(state_category sc, GCRSBaseComVin::VinL3Type vin,
            simtime_t sendT, simtime_t receiveT, range_category rc);
    virtual ~GCRSBaseComCollectNode();

    state_category getState() {
        return this->sc;
    }

    GCRSBaseComVin::VinL3Type getVin() {
        return this->vin;
    }

    simtime_t getSendTime() {
        return this->sendTime;
    }

    simtime_t getReceiveTime() {
        return this->receiveTime;
    }

    range_category getRangeType(){
        return this->rangeType;
    }

    void setState(state_category sc) {
        this->sc = sc;
    }

    void setVin(GCRSBaseComVin::VinL3Type vin) {
        this->vin = vin;
    }

    void setSendTime(simtime_t time) {
        this->sendTime = time;
    }

    void setReceiveTime(simtime_t time) {
        this->receiveTime = time;
    }

    void addChildNode(GCRSBaseComCollectNode* node);
    GCRSBaseComCollectNode* getChildNodeByVin(GCRSBaseComVin::VinL3Type vin);
    std::vector<GCRSBaseComCollectNode*>* getChildrenNodes();
    void cleanUp();
    int getNumChildrenNodes();
    bool isRelayNode();
    bool isZorNode();
    bool isZofNode();
protected:
    class SearchNode {
    public:
        SearchNode(GCRSBaseComVin::VinL3Type v) :
                vin(v) {
        }
        ;
        bool operator()(GCRSBaseComCollectNode* node) const {
            if (node == NULL) {
                return false;
            }
            if (node->vin == this->vin) {
                return true;
            }
            return false;
        }
        ;
    private:
        GCRSBaseComVin::VinL3Type vin;
    };
    class ClearAll {
    public:
        ClearAll() {
        }
        ;
        bool operator()(GCRSBaseComCollectNode* node) const {
            if (node == NULL)
                return true;
            delete node;
            return true;
        }
    };
protected:
    state_category sc;
    GCRSBaseComVin::VinL3Type vin;
    simtime_t sendTime;
    simtime_t receiveTime;
    range_category rangeType;
    std::vector<GCRSBaseComCollectNode*>* vecChildrenNodes;
};

#endif /* GCRSBASECOMCOLLECTNODE_H_ */
