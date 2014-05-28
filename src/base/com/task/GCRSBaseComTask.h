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

#ifndef GCRSBASECOMTASK_H_
#define GCRSBASECOMTASK_H_
#include "GCRSBaseNetPkt_m.h"

class GCRSBaseComTask {
public:
    GCRSBaseComTask();
    GCRSBaseComTask(long taskId, long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt);
    virtual ~GCRSBaseComTask();

    virtual void setState(int state){
        this->m_State = state;
    }

    virtual void setNextEventTime(simtime_t t){
        this->m_NextEventTime = t;
    }

    virtual void setExpireTime(simtime_t t){
        this->m_ExpireTime = t;
    }

    virtual void setScheduleTime(simtime_t t){
        this->m_ScheduleTime = t;
    }

    virtual long getTaskId(){
        return this->m_TaskId;
    }

    virtual long getRunningEventId(){
        return this->m_RunningEventId;
    }

    virtual long getExpireEventId(){
        return this->m_ExpireEventId;
    }

    virtual int getState(){
        return this->m_State;
    }

    virtual simtime_t getNextEventTime(){
        return this->m_NextEventTime;
    }

    virtual simtime_t getExpireTime(){
        return this->m_ExpireTime;
    }

    virtual GCRSBaseNetPkt* getPkt(){
        return this->m_Pkt;
    }

    virtual simtime_t getScheduleTime(){
        return this->m_ScheduleTime;
    }
protected:
    long m_TaskId;
    long m_RunningEventId;
    long m_ExpireEventId;
    int m_State;
    simtime_t m_NextEventTime;
    simtime_t m_ExpireTime;

    simtime_t m_ScheduleTime;
    GCRSBaseNetPkt* m_Pkt;
};

#endif /* GCRSBASECOMTASK_H_ */
