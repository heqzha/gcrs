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

#include "GCRSBaseVehicleManager.h"
#include "GCRSBaseComMath.h"
#include <iterator>     // std::advance
#include "Convert.h"

Define_Module(GCRSBaseVehicleManager)
;

void GCRSBaseVehicleManager::initialize(int stage) {
    if (stage == 0) {
        this->vinCounter = 0;
        this->traciManager = GCRSBaseTraCIScenarioManagerLaunchdAccess().get();
        this->rand_seed =
                hasPar("RAND_SEED") ? par("RAND_SEED").longValue() : 0;
        this->vdState = VDSC_UNSTABLE;
        this->numVehiclesInCity = 0;
        this->numVehiclesOutCity = 0;
        /*
         *VehicleControl initialize
         */
        this->vCtrl = GCRSBaseComVehicleControl();
        /*
         * Event triggering ratio setup
         */
        this->numVehicles =
                hasPar("NUM_VEHICLES") ? par("NUM_VEHICLES").longValue() : 0;
        this->mapVEventTriggerRatio = this->generateRandomEventTriggerRatio(
                this->numVehicles);
        /*
         * Event initialize
         */
        this->selfMsg_Event_Initialize = new cMessage("Event Initial",
                MC_SELFMSG_EVENT_INITIALIZE);
        scheduleAt(simTime() + 0.1, this->selfMsg_Event_Initialize);
    }
}
void GCRSBaseVehicleManager::finish() {
    if (this->selfMsg_Event_Initialize->isScheduled()) {
        cancelAndDelete(this->selfMsg_Event_Initialize);
    } else {
        delete (this->selfMsg_Event_Initialize);
    }
}

void GCRSBaseVehicleManager::handleMessage(cMessage* msg) {
    if (msg == NULL) {
        EV<< "GCRSBaseVehicleManager:<<ERROR>>The self message is NULL!"<< endl;
        return;
    }

    switch (msg->getKind()) {
        case MC_SELFMSG_EVENT_INITIALIZE: {
            unsigned int numEvent =
            hasPar("NUM_EVENT") ? par("NUM_EVENT").longValue() : 0;
            this->eCtrl = GCRSBaseComVehicleEventControl(numEvent);
            int eventType = hasPar("EVENT_TYPE")?par("EVENT_TYPE").longValue():EC_ACCIDENT;
            double eventAreaRange = hasPar("EVENT_AREA_RANGE")?par("EVENT_AREA_RANGE").doubleValue():0.0f;
            double maxEventOccurRatio = hasPar("MAX_EVENT_OCCUR_RATIO")?par("MAX_EVENT_OCCUR_RATIO").doubleValue():0.5f;
            std::list<Coord> listCrossRoads = this->traciManager->getCrossRoads();
            for(unsigned int i=0; i < numEvent; ++i) {
                double eventOccurRatio = GCRSBaseComMath::geDoubleRandomNumber(0.5f, maxEventOccurRatio, this->rand_seed);
                double eventStart = 1.0f;
                unsigned indexCrossRoad = GCRSBaseComMath::geUnsignedRandomNumer(0,listCrossRoads.size(), this->rand_seed);
                std::list<Coord>::iterator iter = listCrossRoads.begin();
                if(indexCrossRoad < listCrossRoads.size()) {
                    std::advance(iter, indexCrossRoad);
                }
                Coord eventLocation = (*iter);
                long eventId = this->eCtrl.addEvent(eventType,eventOccurRatio,eventLocation,eventAreaRange,eventStart);
                if(eventId >= 0) {
                    int eventDurationModifyTimes = hasPar("EVENT_DURATION_MODIFY_TIMES")?par("EVENT_DURATION_MODIFY_TIMES").longValue():0;
                    double eventDurationMin = hasPar("EVENT_DURATION_MIN")?par("EVENT_DURATION_MIN").doubleValue():0.0f;
                    double eventDurationMax = hasPar("EVENT_DURATION_MAX")?par("EVENT_DURATION_MAX").doubleValue():0.0f;
                    for(int i = 0; i < eventDurationModifyTimes; ++i) {
                        double eventDuration = GCRSBaseComMath::geDoubleRandomNumber(eventDurationMin, eventDurationMax, this->rand_seed);
                        this->eCtrl.addEventDuration(eventId,eventDuration);
                    }
                }
            }
            this->selfMsg_Event_Initialize->setKind(MC_SELFMSG_VEHICLE_DENSITY_STATE);
            scheduleAt(simTime() + 0.1f, this->selfMsg_Event_Initialize);
            break;
        }
        case MC_SELFMSG_VEHICLE_DENSITY_STATE: {
            int currentNumVehiclesInCity = this->vinCounter;
            int currentNumVehiclesOutCity = this->vCtrl.getVehicleNum() - this->vCtrl.getNumInCityVehicle();
            if(currentNumVehiclesOutCity != 0) {
                double InOutRatio = (static_cast<double>(currentNumVehiclesInCity - this->numVehiclesInCity)) / (static_cast<double>(currentNumVehiclesOutCity - this->numVehiclesOutCity));
                if(InOutRatio > 0.9f && InOutRatio < 1.1f) {
                    this->vdState = VDSC_STABLE;
                    break;
                } else {
                    this->numVehiclesInCity = this->vinCounter;
                    this->numVehiclesOutCity = this->vCtrl.getVehicleNum() - this->vCtrl.getNumInCityVehicle();
                }
            }
            scheduleAt(simTime() + 60.0f, this->selfMsg_Event_Initialize);
            break;
        }
        default: {
            EV<<"GCRSBaseVehicleManager:<<ERROR>>HandleSelfMessage got unexpected message of kind " << msg->getKind() << endl;
            delete msg;
            break;
        }
    }
}

GCRSBaseComVin::VinL3Type GCRSBaseVehicleManager::geUniqueVin() {
    return this->vinCounter++;
}

std::map<GCRSBaseComVin::VinL3Type, double> GCRSBaseVehicleManager::generateRandomEventTriggerRatio(
        long numVehicle) {
    std::map<GCRSBaseComVin::VinL3Type, double> mapRatio;
    for (GCRSBaseComVin::VinL3Type i = 0; i < numVehicle; ++i) {
        double eventOccurRatio = GCRSBaseComMath::geDoubleRandomNumber(0.0f,
                0.5f, this->rand_seed);
        mapRatio.insert(
                std::map<GCRSBaseComVin::VinL3Type, double>::value_type(i,
                        eventOccurRatio));
    }
    return mapRatio;
}

GCRSBaseComVin::VinL3Type GCRSBaseVehicleManager::addVehicle(std::string id) {
    GCRSBaseComVin::VinL3Type vin = this->geUniqueVin();
    double eventOccurRatio = 0.0f;
    long key = vin % this->numVehicles;
    eventOccurRatio = this->mapVEventTriggerRatio[key];
    GCRSBaseComVehicleState* vState = this->vCtrl.addVehicle(vin, id,
            eventOccurRatio);
    return vState->getVin();
}
bool GCRSBaseVehicleManager::updateVehicleState(GCRSBaseComVin::VinL3Type vin,
        GCRSBaseComVehicleState::state_category sc) {
    return this->vCtrl.updateState(vin, sc);
}

bool GCRSBaseVehicleManager::updateVehicleParams(GCRSBaseComVin::VinL3Type vin,
        VehicleParams vParams) {
    return this->vCtrl.updateVehicleParameters(vin, vParams.location,
            vParams.speed, vParams.direction, vParams.speedMax,
            vParams.laneIndex);
}

GCRSBaseVehicleManager::VehicleParams GCRSBaseVehicleManager::getVehicleParams(
        GCRSBaseComVin::VinL3Type vin) {
    VehicleParams vParams;
    vParams.location = this->vCtrl.getVehicleLocation(vin);
    vParams.speed = this->vCtrl.getVehicleSpeed(vin);
    vParams.speedMax = this->vCtrl.getVehicleSpeedMax(vin);
    vParams.direction = this->vCtrl.getVehicleDirection(vin);
    vParams.laneIndex = this->vCtrl.getVehicleLaneIndex(vin);
    return vParams;
}

long GCRSBaseVehicleManager::isEventOccur(GCRSBaseComVin::VinL3Type vin) {
    if (this->vdState == VDSC_UNSTABLE)
        return -1;
    if (this->vCtrl.isEventOccurred(vin))
        return -1;

    Coord loc = this->vCtrl.getVehicleLocation(vin);
    double ratio = this->vCtrl.getVehicleEventOccurRatio(vin);
    long eventId = this->eCtrl.isEventOccur(vin, loc, ratio);
    if (eventId >= 0) {
        this->vCtrl.setEvent(vin, eventId);
    }
    return eventId;
}

simtime_t GCRSBaseVehicleManager::isModifyEventDuration(
        GCRSBaseComVin::VinL3Type vin) {
    if (!this->vCtrl.isEventOccurred(vin))
        return 0.0f;
    long eventId = this->vCtrl.getVehicleEventId(vin);
    return this->eCtrl.modifyEventDurationTime(eventId);
}

unsigned int GCRSBaseVehicleManager::getNumEventDuration(
        GCRSBaseComVin::VinL3Type vin) {
    long eventId = this->vCtrl.getVehicleEventId(vin);
    return this->eCtrl.getNumEventDurationTime(eventId);
}

int GCRSBaseVehicleManager::getEventType(GCRSBaseComVin::VinL3Type vin) {
    long eventId = this->vCtrl.getVehicleEventId(vin);
    return this->eCtrl.getEventType(eventId);
}

simtime_t GCRSBaseVehicleManager::getEventDuration(
        GCRSBaseComVin::VinL3Type vin) {
    long eventId = this->vCtrl.getVehicleEventId(vin);
    return this->eCtrl.getEventDurationTime(eventId);
}

GCRSBaseComVehicleState::state_category GCRSBaseVehicleManager::getVehicleState(
        GCRSBaseComVin::VinL3Type vin) {
    return this->vCtrl.getVehicleState(vin);
}

std::list<GCRSBaseComVin::VinL3Type> GCRSBaseVehicleManager::getAllVin() {
    std::list<GCRSBaseComVin::VinL3Type> listVin = this->vCtrl.getAllVin();
    return listVin;
}

Coord GCRSBaseVehicleManager::getLocation(GCRSBaseComVin::VinL3Type vin) {
    return this->vCtrl.getVehicleLocation(vin);
}

bool GCRSBaseVehicleManager::isAccidentEvent(GCRSBaseComVin::VinL3Type vin) {
    return this->getEventType(vin) == EC_ACCIDENT ? true : false;
}

bool GCRSBaseVehicleManager::isEmergencyEvent(GCRSBaseComVin::VinL3Type vin) {
    return this->getEventType(vin) == EC_EMERGENCY ? true : false;
}

void GCRSBaseVehicleManager::vehicleOutCity(GCRSBaseComVin::VinL3Type vin) {
    this->vCtrl.updateState(vin, GCRSBaseComVehicleState::SC_OUT_CITY);
    /*
     * TODO add a vehicle
     */
    this->traciManager->aVehicleWaitingToAdd();
}

unsigned int GCRSBaseVehicleManager::getNumResetEvent(){
    return this->eCtrl.getNumRestEvents();
}
