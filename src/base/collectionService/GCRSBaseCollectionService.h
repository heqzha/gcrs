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

#ifndef GCRSBASECOLLECTIONSERVICE_H_
#define GCRSBASECOLLECTIONSERVICE_H_

#include <csimplemodule.h>
#include "GCRSBaseComCollectNetworkController.h"
#include "GCRSBaseComCollectNetworkRangeController.h"
#include "GCRSBaseComCollectStatistics.h"
#include "GCRSBaseComCollectPrintOut.h"
#include "GCRSBaseComZone.h"
#include "GCRSBaseTraCIScenarioManagerLaunchd.h"
#include "GCRSBaseVehicleManager.h"
#include "GCRSBaseConnectionManager.h"
#include "FindModule.h"
#include "GCRSBaseComNin.h"
#include "GCRSBaseRealWorldTimer.h"
#include "GCRSBaseComCollectPrintOut.h"

class GCRSBaseCollectionService: public cSimpleModule {
public:
    enum state_category {
        SC_USECASE_INFO = 0, SC_UPDATE = 1
    };
    typedef struct tagNetworkParams{
        Coord location;
        int shape;
        double length;
        double width;
        double direction;
    }NetworkParams;
public:
    /*
     * Get use case informations
     */
    virtual void initialize(int stage);
    /*
     * Get statistics data and print out to xml file.
     */
    virtual void finish();

    GCRSBaseComNin::NinL3Type createNetwork(GCRSBaseComVin::VinL3Type vin,
            simtime_t ttl, Coord loc, double offset, double direct, int landIndex);
    void addRelayNode(GCRSBaseComNin::NinL3Type nin,
            GCRSBaseComVin::VinL3Type parentVin, GCRSBaseComVin::VinL3Type vin,
            GCRSBaseComCollectNode::range_category rc);
    void cancelRelayNode(GCRSBaseComNin::NinL3Type nin,
            GCRSBaseComVin::VinL3Type vin);

    bool isInZorNetworkRange(GCRSBaseComNin::NinL3Type nin, Coord loc);
    bool isInZofNetworkRange(GCRSBaseComNin::NinL3Type nin, Coord loc);

    void updateNetworkTTL(GCRSBaseComNin::NinL3Type nin, simtime_t ttl);
    void updateNetworkVersion(GCRSBaseComNin::NinL3Type nin);
    simtime_t getNetworkCreateTime(GCRSBaseComNin::NinL3Type nin);
    simtime_t getNetworkUpdateTime(GCRSBaseComNin::NinL3Type nin);
    simtime_t getNetworkTTL(GCRSBaseComNin::NinL3Type nin);
    simtime_t getNetworkExipreTime(GCRSBaseComNin::NinL3Type nin);

    long getNetworkVersion(GCRSBaseComNin::NinL3Type nin);
    NetworkParams getNetworkParameters(GCRSBaseComNin::NinL3Type nin, int networkType);
    int getNumVehiclePassThroughZor(GCRSBaseComNin::NinL3Type nin);
    int getNumVehiclePassThroughZof(GCRSBaseComNin::NinL3Type nin);


protected:
    double calcRoadBuidingDensityRatio(double roadLength, double interval);
    void checkVehicleState();
    GCRSBaseComNin::NinL3Type getUniqueNin();
    void conclusion();

protected:
    /** @brief handle self messages */
    virtual void handleMessage(cMessage* msg);

protected:
    GCRSBaseComCollectNetworkController* networkCtrl;
    GCRSBaseComCollectNetworkRangeController *networkRangeCtrl;
    GCRSBaseComCollectPrintOut* printOutProtocol;
    GCRSBaseComCollectPrintOut* printOutVehicleInCity;

    GCRSBaseTraCIScenarioManagerLaunchd* traciManager;
    GCRSBaseVehicleManager* vManager;
    GCRSBaseConnectionManager* connectionManager;
    cMessage* selfMsg_CollectBasicInfo;
    cMessage* selfMsg_Update;
    double updateInterval;

    double playgroundX;
    double playgroundY;
    double roadLength;
    int numCrossRoads;
    int numVehiclesInCity;
    int numPolygon;
    double txRange;
    double roadWidth;
    int roadNum;
    double buildingInterval;

    time_t simStart;
    time_t simEnd;

    GCRSBaseComNin::NinL3Type ninCounter;

};

class GCRSBaseCollectionServiceAccess {
public:
    GCRSBaseCollectionService* get() {
        return FindModule<GCRSBaseCollectionService*>::findGlobalModule();
    }
};

#endif /* GCRSBASECOLLECTIONSERVICE_H_ */
