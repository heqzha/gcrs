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

#ifndef GCRSBASECOMVEHICLEEVENTCONTROL_H_
#define GCRSBASECOMVEHICLEEVENTCONTROL_H_
#include <vector>
#include "GCRSBaseComVehicleEvent.h"

class GCRSBaseComVehicleEventControl {
public:
    GCRSBaseComVehicleEventControl();
    GCRSBaseComVehicleEventControl(unsigned int maxBufferSize);
    virtual ~GCRSBaseComVehicleEventControl();

    virtual long addEvent(int eventType, double eventOccurRatio,
            Coord eventLocation, double eventAreaRange,
            simtime_t eventStartTime);
    virtual void addEventDuration(long eventId, simtime_t duration);
    virtual long isEventOccur(GCRSBaseComVin::VinL3Type vin, Coord loc, double ratio);//If event occured, return eventId
    virtual unsigned int getCurrentEventNum();

    virtual simtime_t modifyEventDurationTime(long eventId);
    virtual int getEventType(long eventId);
    virtual GCRSBaseComVin::VinL3Type getEventVin(long eventId);
    virtual double getEventOccurRatio(long eventId);
    virtual Coord getEventLocation(long eventId);
    virtual double getEventAreaRange(long eventId);
    virtual simtime_t getEventDurationTime(long eventId);
    virtual unsigned int getNumEventDurationTime(long eventId);
    virtual void eventExpired(long eventId);

    virtual unsigned int getNumRestEvents();
    virtual unsigned int getBufferSize();
protected:
    class SearchEvent{
    public:
        SearchEvent(long eventId):m_EventId(eventId){

        }
        bool operator()(GCRSBaseComVehicleEvent* event){
            if(event == NULL)return false;
            if(this->m_EventId == event->getEventId()){
                return true;
            }
            return false;
        }
    private:
        long m_EventId;
    };
    class SearchOccurredEventByLocation{
    public:
        SearchOccurredEventByLocation(Coord loc):m_Loc(loc){};
        bool operator()(GCRSBaseComVehicleEvent* event){
            if(event == NULL)return false;
            if(this->m_Loc == event->getEventLocation()){
                if(event->getEventState() == GCRSBaseComVehicleEvent::SC_EVENT_OCCURED)
                    return true;
            }
            return false;
        }
    private:
        Coord m_Loc;
    };

    class CleanUp{
    public:
        bool operator()(GCRSBaseComVehicleEvent* event){
            if(event != NULL){
                delete event;
            }
            return true;
        }
    };
protected:
    virtual double calcEventOccurRatio(double distance, double evetAreaRange);
    virtual GCRSBaseComVehicleEvent* searchEvent(long eventId);
    virtual GCRSBaseComVehicleEvent* searchOccurredEventByLocation(Coord loc);
    virtual void cleanUp();
    virtual long getUniqueEventId();

protected:
    std::vector<GCRSBaseComVehicleEvent*> m_EventBuffer;
    unsigned int m_MaxBufferSize;
    long m_EventIdCounter;
};

#endif /* GCRSBASECOMVEHICLEEVENTCONTROL_H_ */
