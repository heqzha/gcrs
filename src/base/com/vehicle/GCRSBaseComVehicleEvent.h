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

#ifndef GCRSBASECOMVEHICLEEVENT_H_
#define GCRSBASECOMVEHICLEEVENT_H_
#include "Coord.h"
#include "GCRSBaseComVin.h"
#include <vector>

class GCRSBaseComVehicleEvent {
public:
    enum state_category{
        SC_EVENT_ASSIGNED = 0, SC_EVENT_OCCURED = 1
    };
public:
    GCRSBaseComVehicleEvent(long eventId);
    virtual ~GCRSBaseComVehicleEvent();

    void setEventState(int state){
        this->m_EventState = state;
    }
    void setEventType(int type){
        this->m_EventType = type;
    }
    void setEventVin(GCRSBaseComVin::VinL3Type vin){
        this->m_EventVin = vin;
    }
    void setEventOccurRatio(double ratio){
        this->m_EventOccurRatio = ratio;
    }
    void setEventLocation(Coord loc){
        this->m_EventLocation = loc;
    }
    void setEventAreaRange(double range){
        this->m_EventAreaRange = range;
    }
    void setEventStartTime(simtime_t time){
        this->m_EventStartTime = time;
    }
    void addEventDuration(simtime_t duration){
        this->m_ListEventDurationTime.push_back(duration);
    }

    long getEventId(){
        return this->m_EventId;
    }

    int getEventState(){
        return this->m_EventState;
    }

    int getEventType(){
        return this->m_EventType;
    }
    GCRSBaseComVin::VinL3Type getEventVin(){
        return this->m_EventVin;
    }
    double getEventOccurRatio(){
        return this->m_EventOccurRatio;
    }
    Coord getEventLocation(){
        return this->m_EventLocation;
    }
    double getEventAreaRange(){
        return this->m_EventAreaRange;
    }
    simtime_t getEventStartTime(){
        return this->m_EventStartTime;
    }
    simtime_t getEventDurationTime(){
        if(this->m_ListEventDurationTime.empty())return 0.0f;
        if(this->m_EventDurationTimeIndex >= this->m_ListEventDurationTime.size())return 0.0f;
        return this->m_ListEventDurationTime.at(this->m_EventDurationTimeIndex);
    }
    simtime_t modifyEventDurationTime(){
        simtime_t eventDuration = this->getEventDurationTime();
        if(eventDuration > 0.0f)
            this->m_EventDurationTimeIndex++;
        return eventDuration;
    }
    unsigned int getNumEventDurationTime(){
        return this->m_ListEventDurationTime.size();
    }
protected:
    long m_EventId;
    int m_EventState;
    int m_EventType;
    GCRSBaseComVin::VinL3Type m_EventVin;
    double m_EventOccurRatio;
    Coord m_EventLocation;
    double m_EventAreaRange;
    simtime_t m_EventStartTime;
    unsigned int m_EventDurationTimeIndex;
    std::vector<simtime_t> m_ListEventDurationTime;
};

#endif /* GCRSBASECOMVEHICLEEVENT_H_ */
