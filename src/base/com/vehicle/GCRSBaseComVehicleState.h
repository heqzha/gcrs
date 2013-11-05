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

#ifndef GCRSBASECOMVEHICLESTATE_H_
#define GCRSBASECOMVEHICLESTATE_H_
#include "Coord.h"
#include "GCRSBaseComVin.h"

class GCRSBaseComVehicleState {
public:
    enum state_category {
        SC_NORMAL = 0, SC_EVENT_INITIAL = 1, SC_EVENT_HANDLING = 2
    };
    GCRSBaseComVehicleState() {
        this->vin = GCRSBaseComVin::VINL3NULL;
        this->id = "";
        this->state = SC_NORMAL;
        this->eventId = -1;
        this->eventOccurRatio = 0.0f;

        this->location = Coord::ZERO;
        this->speed = Coord::ZERO;
        this->speedMax = 0.0f;
        this->direction = Coord::ZERO;
        this->laneIndex = -1;
    }
    GCRSBaseComVehicleState(GCRSBaseComVin::VinL3Type v, std::string id) :
            vin(v), id(id) {
        this->state = SC_NORMAL;
        this->eventId = -1;
        this->eventOccurRatio = 0.0f;

        this->location = Coord::ZERO;
        this->speed = Coord::ZERO;
        this->speedMax = 0.0f;
        this->direction = Coord::ZERO;
        this->laneIndex = -1;
    }
    void setState(state_category s) {
        this->state = s;
    }
    void setLocation(Coord loc) {
        this->location = loc;
    }
    void setSpeed(Coord s) {
        this->speed = s;
    }
    void setSpeedMax(double sMax) {
        this->speedMax = sMax;
    }
    void setDirection(Coord direct){
        this->direction = direct;
    }
    void setLaneIndex(int index){
        this->laneIndex = index;
    }
    void setEventId(long eventId){
        this->eventId = eventId;
    }
    void setEventOccurRatio(double ratio){
        this->eventOccurRatio = ratio;
    }

    GCRSBaseComVin::VinL3Type getVin() {
        return this->vin;
    }
    std::string getId() {
        return this->id;
    }
    state_category getState() {
        return this->state;
    }
    Coord getLocation() {
        return this->location;
    }
    Coord getSpeed() {
        return this->speed;
    }
    double getSpeedMax() {
        return this->speedMax;
    }
    Coord getDirection(){
        return this->direction;
    }
    int getLaneIndex(){
        return this->laneIndex;
    }
    long getEventId(){
        return this->eventId;
    }
    double getEventOccurRatio(){
        return this->eventOccurRatio;
    }

protected:
    //Vehicle State
    state_category state;
    //Vehicle Parameters
    GCRSBaseComVin::VinL3Type vin; //Can not be updated
    std::string id; //Can not be updated
    Coord location;
    Coord speed;
    double speedMax;
    Coord direction;
    int laneIndex;
    //Event Parameters
    long eventId;
    double eventOccurRatio;
};

#endif /* GCRSBASECOMVEHICLESTATE_H_ */
