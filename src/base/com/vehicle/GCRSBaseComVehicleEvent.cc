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

#include "GCRSBaseComVehicleEvent.h"

GCRSBaseComVehicleEvent::GCRSBaseComVehicleEvent(long eventId):m_EventId(eventId) {
    this->m_EventState = SC_EVENT_ASSIGNED;
    this->m_EventType = 0;
    this->m_EventVin = GCRSBaseComVin::VINL3NULL;
    this->m_EventOccurRatio = 0.0f;
    this->m_EventLocation = Coord::ZERO;
    this->m_EventAreaRange = 0.0f;
    this->m_EventStartTime = 0.0f;
    this->m_EventDurationTimeIndex = 0;
}

GCRSBaseComVehicleEvent::~GCRSBaseComVehicleEvent() {
    // TODO Auto-generated destructor stub
}

