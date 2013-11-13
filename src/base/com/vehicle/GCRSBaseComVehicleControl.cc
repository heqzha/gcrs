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

#include "GCRSBaseComVehicleControl.h"
#include <algorithm>//std::remove_if
GCRSBaseComVehicleControl::~GCRSBaseComVehicleControl() {
    this->cleanUp();
}

GCRSBaseComVehicleState* GCRSBaseComVehicleControl::addVehicle(
        GCRSBaseComVin::VinL3Type vin, std::string id, double eventOccurRatio) {
    GCRSBaseComVehicleState* vehicle = getVehicle(vin);
    if (vehicle != NULL)
        return vehicle;
    vehicle = new GCRSBaseComVehicleState(vin, id);
    vehicle->setEventOccurRatio(eventOccurRatio);
    this->mapVehicle.insert(
            std::map<GCRSBaseComVin::VinL3Type, GCRSBaseComVehicleState*>::value_type(
                    vin, vehicle));
    return vehicle;
}

GCRSBaseComVehicleState* GCRSBaseComVehicleControl::getVehicle(
        GCRSBaseComVin::VinL3Type vin) {
    if (this->mapVehicle.empty()) {
        return NULL;
    }
    std::map<GCRSBaseComVin::VinL3Type, GCRSBaseComVehicleState*>::iterator iter;
    iter = this->mapVehicle.find(vin);
    if (iter == this->mapVehicle.end()) {
        return NULL;
    }
    return (*iter).second;
}

std::list<GCRSBaseComVin::VinL3Type> GCRSBaseComVehicleControl::getAllVin(){
    std::list<GCRSBaseComVin::VinL3Type> listVin;
    std::map<GCRSBaseComVin::VinL3Type, GCRSBaseComVehicleState*>::iterator iter;
    for(iter = this->mapVehicle.begin(); iter != this->mapVehicle.end(); ++iter){
        listVin.push_back((*iter).first);
    }
    return listVin;
}

bool GCRSBaseComVehicleControl::updateState(GCRSBaseComVin::VinL3Type vin,
        GCRSBaseComVehicleState::state_category sc) {
    GCRSBaseComVehicleState* vehicle = getVehicle(vin);
    if (vehicle == NULL)
        return false;
    vehicle->setState(sc);
    return true;
}

bool GCRSBaseComVehicleControl::updateVehicleParameters(
        GCRSBaseComVin::VinL3Type vin, Coord loc, Coord speed, Coord direct,
        double speedMax, int laneIndex) {
    GCRSBaseComVehicleState* vehicle = getVehicle(vin);
    if (vehicle == NULL)
        return false;
    vehicle->setLocation(loc);
    vehicle->setSpeed(speed);
    vehicle->setDirection(direct);
    if (speedMax != 0.0f) {
        vehicle->setSpeedMax(speedMax);
    }
    if(laneIndex != -1){
        vehicle->setLaneIndex(laneIndex);
    }
    return true;
}

void GCRSBaseComVehicleControl::setEvent(GCRSBaseComVin::VinL3Type vin, long eventId){
    GCRSBaseComVehicleState* vehicle = getVehicle(vin);
    if (vehicle == NULL)
        return;
    vehicle->setEventId(eventId);
}

bool GCRSBaseComVehicleControl::isEventOccurred(GCRSBaseComVin::VinL3Type vin){
    GCRSBaseComVehicleState* vehicle = getVehicle(vin);
    if (vehicle == NULL)
        return false;
    return vehicle->getEventId() >= 0? true:false;
}

GCRSBaseComVehicleState::state_category GCRSBaseComVehicleControl::getVehicleState(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getState();
}

Coord GCRSBaseComVehicleControl::getVehicleLocation(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getLocation();
}

Coord GCRSBaseComVehicleControl::getVehicleSpeed(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getSpeed();
}

double GCRSBaseComVehicleControl::getVehicleSpeedMax(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getSpeedMax();
}

Coord GCRSBaseComVehicleControl::getVehicleDirection(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getDirection();
}

int GCRSBaseComVehicleControl::getVehicleLaneIndex(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getLaneIndex();
}

long GCRSBaseComVehicleControl::getVehicleEventId(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getEventId();
}

double GCRSBaseComVehicleControl::getVehicleEventOccurRatio(GCRSBaseComVin::VinL3Type vin){
    return this->getVehicle(vin)->getEventOccurRatio();
}

int GCRSBaseComVehicleControl::getNumEventVehicle(){
    int numEventVehicle = 0;
    std::map<GCRSBaseComVin::VinL3Type, GCRSBaseComVehicleState*>::iterator iter;
    for(iter = this->mapVehicle.begin(); iter != this->mapVehicle.end();){
        GCRSBaseComVehicleState::state_category sc = (*iter).second->getState();
        if(sc == GCRSBaseComVehicleState::SC_EVENT_INITIAL || sc == GCRSBaseComVehicleState::SC_EVENT_HANDLING){
            numEventVehicle++;
        }
        iter++;
    }
    return numEventVehicle;
}

int GCRSBaseComVehicleControl::getNumInCityVehicle(){
    int numInCityVehicle = 0;
    std::map<GCRSBaseComVin::VinL3Type, GCRSBaseComVehicleState*>::iterator iter;
    for(iter = this->mapVehicle.begin(); iter != this->mapVehicle.end();){
        GCRSBaseComVehicleState::state_category sc = (*iter).second->getState();
        if(sc != GCRSBaseComVehicleState::SC_OUT_CITY){
            numInCityVehicle++;
        }
        iter++;
    }
    return numInCityVehicle;
}

void GCRSBaseComVehicleControl::cleanUp() {
    std::map<GCRSBaseComVin::VinL3Type, GCRSBaseComVehicleState*>::iterator iter;
    for (iter = this->mapVehicle.begin(); iter != this->mapVehicle.end();) {
        if ((*iter).second != NULL) {
            delete (*iter).second;
        }
        this->mapVehicle.erase(iter++);
    }
}
