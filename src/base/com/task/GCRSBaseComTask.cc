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

#include "GCRSBaseComTask.h"

GCRSBaseComTask::GCRSBaseComTask(){
    this->m_TaskId = -1;
    this->m_RunningEventId = -1;
    this->m_ExpireEventId = -1;
    this->m_State = -1;
    this->m_NextEventTime = 0.0f;
    this->m_ExpireTime = 0.0f;
    this->m_ScheduleTime = 0.0f;
    this->m_Pkt = NULL;
}

GCRSBaseComTask::GCRSBaseComTask(long taskId, long runningEventId, long expireEventId,
        GCRSBaseNetPkt* pkt) :
        m_TaskId(taskId), m_RunningEventId(runningEventId), m_ExpireEventId(
                expireEventId), m_Pkt(pkt){
    this->m_State = -1;
    this->m_NextEventTime = 0.0f;
    this->m_ExpireTime = 0.0f;
    this->m_ScheduleTime = 0.0f;
}

GCRSBaseComTask::~GCRSBaseComTask(){
    if(this->m_Pkt != NULL)
        delete this->m_Pkt;
    this->m_Pkt = NULL;
}
