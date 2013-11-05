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

#ifndef GCRSBASECOMTASKMANAGER_H_
#define GCRSBASECOMTASKMANAGER_H_
#include <vector>
#include "GCRSBaseComTask.h"

#define ConvertToBaseTask(task) static_cast<GCRSBaseComTask*>(task)

class GCRSBaseComTaskManager {
public:
    GCRSBaseComTaskManager();
    GCRSBaseComTaskManager(unsigned int maxSize);
    virtual ~GCRSBaseComTaskManager();

    virtual long addTask(long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt, simtime_t expireTime);
    virtual void setTaskState(long taskId, int state);
    virtual void setNextEventTime(long taskId, simtime_t t);
    virtual void deleteTask(long taskId)=0;

    virtual long getTaskIdByRunningEventId(long runningEventId);
    virtual long getTaskIdByExpireEventId(long expireEventId);
    virtual long getRunningEventId(long taskId);
    virtual long getExpireEventId(long taskId);
    virtual simtime_t getNextEventTime(long taskId);
    virtual simtime_t getExpireEventTime(long taskId);
    virtual GCRSBaseNetPkt* getPkt(long taskId);

    virtual unsigned int getBufferSize();

    virtual long getTaskIdByPkt(GCRSBaseNetPkt* pkt);

    virtual bool hasSamePkt(GCRSBaseNetPkt* pkt);
protected:
    virtual void cleanUp()=0;

protected:
    class SearchTask{
    public:
        SearchTask(long taskId):m_TaskId(taskId){};
        bool operator()(GCRSBaseComTask* task){
            if(task == NULL)return false;
            if(this->m_TaskId == task->getTaskId()){
                return true;
            }
            return false;
        }
    private:
        long m_TaskId;
    };

    class SearchTaskByRunningEventId{
    public:
        SearchTaskByRunningEventId(long runningEventId):m_RunningEventId(runningEventId){};
        bool operator()(GCRSBaseComTask* task){
            if(task == NULL)return false;
            if(this->m_RunningEventId == task->getRunningEventId()){
                return true;
            }
            return false;
        }
    private:
        long m_RunningEventId;
    };

    class SearchTaskByExpireEventId{
    public:
        SearchTaskByExpireEventId(long expireEventId):m_ExpireEventId(expireEventId){};
        bool operator()(GCRSBaseComTask* task){
            if(task == NULL)return false;
            if(this->m_ExpireEventId == task->getExpireEventId()){
                return true;
            }
            return false;
        }
    private:
        long m_ExpireEventId;
    };

    class SearchPkt{
    public:
        SearchPkt(GCRSBaseNetPkt* pkt):m_Pkt(pkt){};
        bool operator()(GCRSBaseComTask* task){
            if(task == NULL)return false;
            long vinSrc = task->getPkt()->getVinOriginSrc();
            long nin= task->getPkt()->getNin();
            if (vinSrc == this->m_Pkt->getVinOriginSrc() &&
                    nin == this->m_Pkt->getNin()){
                return true;
            }
            return false;
        }
    private:
        GCRSBaseNetPkt* m_Pkt;
    };

    class CleanUp{
    public:
        bool operator()(GCRSBaseComTask* task){
            if(task != NULL){
                delete task;
            }
            return true;
        }
    };
protected:
    virtual GCRSBaseComTask* searchTask(long taskId);
    virtual GCRSBaseComTask* searchTaskByRunningEventId(long runningEventId);
    virtual GCRSBaseComTask* searchTaskByExpireEventId(long expireEventId);
    virtual long searchPkt(GCRSBaseNetPkt*);
    virtual long getUniqueTaskId();
protected:
    std::vector<GCRSBaseComTask*> m_TaskBuffer;
    unsigned int m_BufferMaxSize;

    long m_taskIdCounter;

};

#endif /* GCRSBASECOMTASKMANAGER_H_ */
