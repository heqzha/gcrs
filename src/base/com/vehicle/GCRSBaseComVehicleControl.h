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

#ifndef GCRSBASECOMVEHICLECONTROL_H_
#define GCRSBASECOMVEHICLECONTROL_H_
#include "GCRSBaseComVehicleState.h"
#include <map>

class GCRSBaseComVehicleControl {
public:
    GCRSBaseComVehicleControl(){
    }
    virtual ~GCRSBaseComVehicleControl();
    virtual GCRSBaseComVehicleState* addVehicle(GCRSBaseComVin::VinL3Type vin, std::string id, double eventOccurRatio = 0.0f);
    virtual GCRSBaseComVehicleState* getVehicle(GCRSBaseComVin::VinL3Type vin);
    virtual std::list<GCRSBaseComVin::VinL3Type> getAllVin();

    virtual bool updateState(GCRSBaseComVin::VinL3Type vin,GCRSBaseComVehicleState::state_category sc);
    virtual bool updateVehicleParameters(GCRSBaseComVin::VinL3Type vin, Coord loc, Coord speed, Coord direct,double speedMax = 0.0f, int laneIndex = 0.0f);
    virtual void setEvent(GCRSBaseComVin::VinL3Type vin, long eventId);
    virtual bool isEventOccurred(GCRSBaseComVin::VinL3Type vin);

    virtual GCRSBaseComVehicleState::state_category getVehicleState(GCRSBaseComVin::VinL3Type vin);
    virtual Coord getVehicleLocation(GCRSBaseComVin::VinL3Type vin);
    virtual Coord getVehicleSpeed(GCRSBaseComVin::VinL3Type vin);
    virtual double getVehicleSpeedMax(GCRSBaseComVin::VinL3Type vin);
    virtual Coord getVehicleDirection(GCRSBaseComVin::VinL3Type vin);
    virtual int getVehicleLaneIndex(GCRSBaseComVin::VinL3Type vin);
    virtual long getVehicleEventId(GCRSBaseComVin::VinL3Type vin);
    virtual double getVehicleEventOccurRatio(GCRSBaseComVin::VinL3Type vin);

    virtual int getNumAccidentVehicle();
    int getVehicleNum(){return this->mapVehicle.size();}
protected:
    virtual void cleanUp();
protected:
    std::map<GCRSBaseComVin::VinL3Type,GCRSBaseComVehicleState*> mapVehicle;
};

#endif /* GCRSBASECOMVEHICLECONTROL_H_ */
