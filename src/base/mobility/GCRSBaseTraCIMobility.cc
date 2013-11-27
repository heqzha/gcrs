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

#include "GCRSBaseTraCIMobility.h"
#include <stdlib.h>
#include "FindModule.h"


Define_Module(GCRSBaseTraCIMobility)
;
void GCRSBaseTraCIMobility::initialize(int stage) {
    TraCIMobility::initialize(stage);
    if (stage == 0) {
        /*
         * Vehicle State initialize
         */
        this->vManager =
                FindModule<GCRSBaseVehicleManager*>::findGlobalModule();
        this->vin = this->vManager->addVehicle(this->getId());
        /*
         * Self Messages initialize
         */
        this->eventInterval =
                hasPar("EventInterval") ?
                        par("EventInterval").doubleValue() : 0.1f;

        this->selfMsg_EVENT = new cMessage("Event", MC_SELFMSG_UPDATE);

        scheduleAt(simTime() + this->eventInterval, this->selfMsg_EVENT);
    }
}

void GCRSBaseTraCIMobility::finish() {
    this->vManager->vehicleOutCity(this->vin);
    this->vManager->eventExpire(this->vin);
    TraCIMobility::finish();
    if (this->selfMsg_EVENT->isScheduled()) {
        cancelAndDelete(this->selfMsg_EVENT);
    } else {
        delete (this->selfMsg_EVENT);
    }
}

void GCRSBaseTraCIMobility::handleSelfMsg(cMessage *msg) {
    if (msg == NULL) {
        EV<<"GCRSBaseTraCIMobility:<ERROR> Self message is NULL!" << endl;
        return;
    }
    switch(msg->getKind()) {
        case MC_SELFMSG_UPDATE: {
            //Update vehicle state
            GCRSBaseVehicleManager::VehicleParams vP;
            vP.location = this->getLocation();
            vP.speed = this->getSpeedVector();
            vP.speedMax = this->getSpeedMax();
            vP.direction = this->getDirection();
            vP.laneIndex = this->getCurrentLaneIndex();
            std::string name = this->getId();
            this->vManager->updateVehicleParams(this->vin,vP);
            //Check if the event happens
            long eventId = this->vManager->isEventOccur(this->vin);
            if(eventId >= 0){
                this->vManager->updateVehicleState(this->vin,GCRSBaseComVehicleState::SC_EVENT_INITIAL);
                this->selfMsg_EVENT->setKind(MC_SELFMSG_EVENT_START);
                scheduleAt(simTime() + 0.1, this->selfMsg_EVENT);
            }else{
                scheduleAt(simTime() + this->eventInterval, this->selfMsg_EVENT);
            }
            break;
        }
        case MC_SELFMSG_EVENT_START: {
            //Event happened
            if(this->vManager->isAccidentEvent(this->vin)){
                this->commandSetSpeed(0);
            }else if(this->vManager->isEmergencyEvent(this->vin)){
                this->commandSetSpeed(this->getSpeedMax());
            }
            simtime_t eventDuration = this->vManager->isModifyEventDuration(this->vin);
            unsigned int numEventDuration = this->vManager->getNumEventDuration(this->vin);

            if(eventDuration > 0.0f){
                this->selfMsg_EVENT->setKind(MC_SELFMSG_EVENT_START);
                scheduleAt(simTime() + (eventDuration.dbl()/static_cast<double>(numEventDuration)), this->selfMsg_EVENT);
            }else{
                this->selfMsg_EVENT->setKind(MC_SELFMSG_EVENT_STOP);
                scheduleAt(simTime() + 0.1, this->selfMsg_EVENT);
            }
            break;
        }
        case MC_SELFMSG_EVENT_STOP: {
            //Event finished
            this->commandSetSpeed(-1);
            this->vManager->updateVehicleState(this->vin, GCRSBaseComVehicleState::SC_NORMAL);
            this->vManager->eventExpire(this->vin);
            this->selfMsg_EVENT->setKind(MC_SELFMSG_UPDATE);
            scheduleAt(simTime() + this->eventInterval, this->selfMsg_EVENT);
            break;
        }
        default: {
            EV<<"GCRSBaseTraCIMobility:<ERROR> HandleSelfMessage got unexpected message of kind " << msg->getKind() << endl;
            delete msg;
            break;
        }
    }
}

std::string GCRSBaseTraCIMobility::getId() {
    return this->getExternalId();
}

Coord GCRSBaseTraCIMobility::getLocation() {
    return this->move.getCurrentPosition();
}

Coord GCRSBaseTraCIMobility::getSpeedVector() {
    return this->move.getDirection() * this->getSpeedScalar();
}

double GCRSBaseTraCIMobility::getSpeedScalar() {
    return this->move.getSpeed();
}

double GCRSBaseTraCIMobility::getSpeedMax() {
    std::string laneId = this->getManager()->commandGetLaneId(this->getId());
    return this->getManager()->commandGetLaneMaxSpeed(laneId);
}

Coord GCRSBaseTraCIMobility::getDirection(){
    return this->move.getDirection();
}

int GCRSBaseTraCIMobility::getCurrentLaneIndex(){
    std::string landId = this->getManager()->commandGetLaneId(this->getId());
    unsigned found = landId.find_last_of("/_");
    std::string index = landId.substr(found + 1);
    return atoi(index.c_str());
}

GCRSBaseComVin::VinL3Type GCRSBaseTraCIMobility::getVehicleIdNum() {
    return this->vin;
}
