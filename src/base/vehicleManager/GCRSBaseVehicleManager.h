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

#ifndef GCRSBASEVEHICLEMANAGER_H_
#define GCRSBASEVEHICLEMANAGER_H_

#include <csimplemodule.h>
#include "GCRSBaseComVehicleEventControl.h"
#include "GCRSBaseComVehicleControl.h"
#include "FindModule.h"
#include "GCRSBaseTraCIScenarioManagerLaunchd.h"
/*
 * @brief GCRSBaseVehicleManager provides the information of all vehicles and controls the vehicles behavior(accident).
 */
class GCRSBaseVehicleManager: public cSimpleModule {
protected:
    enum event_category{
        EC_ACCIDENT = 0, EC_EMERGENCY = 1
    };
    enum message_category {
        MC_SELFMSG_EVENT_INITIALIZE=0
    };
public:
    typedef struct tagVehicleParams{
        Coord location;
        Coord speed;
        double speedMax;
        Coord direction;
        int laneIndex;
    }VehicleParams;

public:
    virtual void initialize(int stage);
    virtual void finish();

    virtual GCRSBaseComVin::VinL3Type addVehicle(std::string id);
    virtual bool updateVehicleState(GCRSBaseComVin::VinL3Type vin, GCRSBaseComVehicleState::state_category sc);
    virtual bool updateVehicleParams(GCRSBaseComVin::VinL3Type vin, VehicleParams vParams);
    virtual VehicleParams getVehicleParams(GCRSBaseComVin::VinL3Type vin);
    virtual long isEventOccur(GCRSBaseComVin::VinL3Type vin);
    virtual simtime_t isModifyEventDuration(GCRSBaseComVin::VinL3Type vin);
    virtual unsigned int getNumEventDuration(GCRSBaseComVin::VinL3Type vin);
    virtual int getEventType(GCRSBaseComVin::VinL3Type vin);
    virtual simtime_t getEventDuration(GCRSBaseComVin::VinL3Type vin);
    virtual GCRSBaseComVehicleState::state_category getVehicleState(GCRSBaseComVin::VinL3Type vin);
    virtual std::list<GCRSBaseComVin::VinL3Type> getAllVin();
    virtual Coord getLocation(GCRSBaseComVin::VinL3Type vin);
    virtual bool isAccidentEvent(GCRSBaseComVin::VinL3Type vin);
    virtual bool isEmergencyEvent(GCRSBaseComVin::VinL3Type vin);
    virtual void vehicleOutCity(GCRSBaseComVin::VinL3Type vin);
    int getNumVehicles(){
        return this->vCtrl.getVehicleNum();
    }


protected:
    /** @brief handle self messages */
    virtual void handleMessage(cMessage* msg);

    //@brief generate a unique vehicle identify number
    virtual GCRSBaseComVin::VinL3Type geUniqueVin();

    virtual std::map<GCRSBaseComVin::VinL3Type, double> generateRandomEventTriggerRatio(long numVehicle);

protected:
    GCRSBaseTraCIScenarioManagerLaunchd* traciManager;
    cMessage* selfMsg_Event_Initialize;

    GCRSBaseComVehicleControl vCtrl;
    GCRSBaseComVehicleEventControl eCtrl;
    GCRSBaseComVin::VinL3Type vinCounter;

    int rand_seed;
    std::map<GCRSBaseComVin::VinL3Type, double> mapVEventTriggerRatio;

};

class GCRSBaseVehicleManagerAccess {
public:
    GCRSBaseVehicleManager* get(){
        return FindModule<GCRSBaseVehicleManager*>::findGlobalModule();
    }
};
#endif /* GCRSBASEVEHICLEMANAGER_H_ */
