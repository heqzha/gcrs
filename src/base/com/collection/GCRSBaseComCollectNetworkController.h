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

#ifndef GCRSBASECOMCOLLECTNETWORKCONTROLLER_H_
#define GCRSBASECOMCOLLECTNETWORKCONTROLLER_H_
#include <map>
#include "GCRSBaseComCollectNetwork.h"
#include "GCRSBaseComNin.h"

class GCRSBaseComCollectNetworkController {
public:
    GCRSBaseComCollectNetworkController();
    virtual ~GCRSBaseComCollectNetworkController();

    GCRSBaseComNin::NinL3Type createNetwork(GCRSBaseComNin::NinL3Type nin,
            simtime_t ttl);
    void setRootNode(GCRSBaseComNin::NinL3Type nin,
            GCRSBaseComVin::VinL3Type vin);
    void addRelayNode(GCRSBaseComNin::NinL3Type nin,
            GCRSBaseComVin::VinL3Type parentVin, GCRSBaseComVin::VinL3Type vin,
            GCRSBaseComCollectNode::range_category rc);
    void cancelRelayNode(GCRSBaseComNin::NinL3Type nin,
            GCRSBaseComVin::VinL3Type vin);
    void checkNetworksState();
    void updateTTL(GCRSBaseComNin::NinL3Type nin, simtime_t ttl);
    void updateVersion(GCRSBaseComNin::NinL3Type nin);

    simtime_t getCreateTime(GCRSBaseComNin::NinL3Type nin);
    simtime_t getUpdateTime(GCRSBaseComNin::NinL3Type nin);
    simtime_t getTTL(GCRSBaseComNin::NinL3Type nin);
    simtime_t getExpireTime(GCRSBaseComNin::NinL3Type nin);
    long getVersion(GCRSBaseComNin::NinL3Type nin);
    GCRSBaseComVin::VinL3Type getRootNodeVin(GCRSBaseComNin::NinL3Type nin);

    int getNumRxNodesInZor(GCRSBaseComNin::NinL3Type nin);
    int getNumRxNodesInZof(GCRSBaseComNin::NinL3Type nin);
    int getNumRelayNodes(GCRSBaseComNin::NinL3Type nin);
    int getMaxHops(GCRSBaseComNin::NinL3Type nin);
    simtime_t getMaxDelayTime(GCRSBaseComNin::NinL3Type nin);
    simtime_t getNetworkCreateTime(GCRSBaseComNin::NinL3Type nin);

protected:
    GCRSBaseComCollectNetwork* getNetworkByNin(GCRSBaseComNin::NinL3Type nin);
    void cleanUp();

protected:
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetwork*> mapNetworks;
};

#endif /* GCRSBASECOMCOLLECTNETWORKCONTROLLER_H_ */
