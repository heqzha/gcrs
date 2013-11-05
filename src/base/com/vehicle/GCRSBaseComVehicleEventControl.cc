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

#include "GCRSBaseComVehicleEventControl.h"
#include <algorithm>//std::remove_if std::find_if std::sort
#include "GCRSBaseComMath.h"

GCRSBaseComVehicleEventControl::GCRSBaseComVehicleEventControl(){
    this->m_MaxBufferSize = 0;
    this->m_EventIdCounter = 0;
}
GCRSBaseComVehicleEventControl::GCRSBaseComVehicleEventControl(
        unsigned int maxBufferSize) :
        m_MaxBufferSize(maxBufferSize) {
    this->m_EventIdCounter = 0;
}

GCRSBaseComVehicleEventControl::~GCRSBaseComVehicleEventControl() {
    this->cleanUp();
}

long GCRSBaseComVehicleEventControl::addEvent(int eventType,
        double eventOccurRatio, Coord eventLocation, double eventAreaRange,
        simtime_t eventStartTime) {
    if (this->m_MaxBufferSize <= 0
            || this->m_MaxBufferSize <= this->m_EventBuffer.size())
        return -1;
    GCRSBaseComVehicleEvent* event = new GCRSBaseComVehicleEvent(
            this->getUniqueEventId());
    event->setEventType(eventType);
    event->setEventOccurRatio(eventOccurRatio);
    event->setEventLocation(eventLocation);
    event->setEventAreaRange(eventAreaRange);
    event->setEventStartTime(eventStartTime);
    this->m_EventBuffer.push_back(event);
    return event->getEventId();
}

void GCRSBaseComVehicleEventControl::addEventDuration(long eventId, simtime_t duration){
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if(event == NULL)return;
    event->addEventDuration(duration);
}

long GCRSBaseComVehicleEventControl::isEventOccur(GCRSBaseComVin::VinL3Type vin,
        Coord loc, double ratio) {
    if (this->m_EventBuffer.empty())
        return -1;
    std::vector<GCRSBaseComVehicleEvent*>::iterator iter;
    for (iter = this->m_EventBuffer.begin(); iter != this->m_EventBuffer.end();
            ++iter) {
        if ((*iter) == NULL)
            continue;
        if((*iter)->getEventState() == GCRSBaseComVehicleEvent::SC_EVENT_OCCURED)
            continue;
        Coord eventLoc = (*iter)->getEventLocation();
        double eventAreaRange = (*iter)->getEventAreaRange();
        double eventOccurRatio = (*iter)->getEventOccurRatio();
        Coord local = GCRSBaseComMath::tranCoordWorldtoLocal(loc, eventLoc,
                0.0f);
        if (GCRSBaseComMath::isInCircleRange(local, eventAreaRange)) {
            double distance = GCRSBaseComMath::calcDistance(loc, eventLoc);
            if (eventOccurRatio
                    < (this->calcEventOccurRatio(distance, eventAreaRange) + ratio)) {
                (*iter)->setEventState(GCRSBaseComVehicleEvent::SC_EVENT_OCCURED);
                return (*iter)->getEventId();
            } else {
                return -1;
            }
        }
    }
    return -1;
}

simtime_t GCRSBaseComVehicleEventControl::modifyEventDurationTime(long eventId){
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return 0.0f;
    return event->modifyEventDurationTime();
}

int GCRSBaseComVehicleEventControl::getEventType(long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return -1;
    return event->getEventType();
}

GCRSBaseComVin::VinL3Type GCRSBaseComVehicleEventControl::getEventVin(
        long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return GCRSBaseComVin::VINL3NULL;
    return event->getEventVin();
}

double GCRSBaseComVehicleEventControl::getEventOccurRatio(long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return 0.0f;
    return event->getEventOccurRatio();
}

Coord GCRSBaseComVehicleEventControl::getEventLocation(long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return Coord::ZERO;
    return event->getEventLocation();
}

double GCRSBaseComVehicleEventControl::getEventAreaRange(long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return 0.0f;
    return event->getEventAreaRange();
}

simtime_t GCRSBaseComVehicleEventControl::getEventStartTime(long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return 0.0f;
    return event->getEventStartTime();
}

simtime_t GCRSBaseComVehicleEventControl::getEventDurationTime(long eventId) {
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL)
        return 0.0f;
    return event->getEventDurationTime();
}

unsigned int GCRSBaseComVehicleEventControl::getNumEventDurationTime(long eventId){
    GCRSBaseComVehicleEvent* event = this->searchEvent(eventId);
    if (event == NULL) return 0;
    return event->getNumEventDurationTime();
}

unsigned int GCRSBaseComVehicleEventControl::getBufferSize() {
    return this->m_EventBuffer.size();
}

double GCRSBaseComVehicleEventControl::calcEventOccurRatio(double distance,
        double evetAreaRange) {
    if (evetAreaRange <= 0.0f)
        return 0.0f;
    double result = (1 - distance / evetAreaRange) * 0.5;
    return result;
}

GCRSBaseComVehicleEvent* GCRSBaseComVehicleEventControl::searchEvent(
        long eventId) {
    if (this->m_EventBuffer.empty())
        return NULL;
    std::vector<GCRSBaseComVehicleEvent*>::iterator iter;
    iter = std::find_if(this->m_EventBuffer.begin(), this->m_EventBuffer.end(),
            SearchEvent(eventId));
    if (iter == this->m_EventBuffer.end()) {
        return NULL;
    }
    return (*iter);
}

void GCRSBaseComVehicleEventControl::cleanUp() {
    this->m_EventBuffer.erase(
            std::remove_if(this->m_EventBuffer.begin(),
                    this->m_EventBuffer.end(), CleanUp()),
            this->m_EventBuffer.end());
}

long GCRSBaseComVehicleEventControl::getUniqueEventId() {
    return this->m_EventIdCounter++;
}
