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

#ifndef GCRSROVERCOMTASKMANAGER_H_
#define GCRSROVERCOMTASKMANAGER_H_

#include "GCRSBaseComTaskManager.h"
#include "GCRSROVERComTask.h"

#define ConvertToRoverTask(task) dynamic_cast<GCRSROVERComTask*>(task)

class GCRSROVERComTaskManager: public GCRSBaseComTaskManager {
public:
    GCRSROVERComTaskManager();
    GCRSROVERComTaskManager(unsigned int maxSize);
    virtual ~GCRSROVERComTaskManager();

    virtual long addTask(long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt, simtime_t expireTime);
    virtual void deleteTask(long taskId);
    virtual void addData(long taskId, int kind,GCRSBaseNetPkt* dataPkt);
    virtual bool hasDataPkt(long taskId);
    virtual void toReply(long taskId, int kind);
    virtual void toRequest(long taskId, int kind);
    virtual void toData(long taskId, int kind, GCRSBaseNetPkt* repData);
    virtual bool isIdle(long taskId);
    virtual bool isReply(long taskId);
    virtual bool isRequest(long taskId);
    virtual bool isData(long taskId);

protected:
    class DeleteTask {
    public:
        DeleteTask(long taskId) :
                m_TaskId(taskId) {
        }
        ;
        bool operator()(GCRSBaseComTask* task) const {
            if (task == NULL)
                return true;

            if (this->m_TaskId == task->getTaskId()) {
                GCRSROVERComTask* drgTask = ConvertToRoverTask(task);
                delete drgTask;
                return true;
            }
            return false;
        }
    private:
        long m_TaskId;
    };

    class SearchPkt{
    public:
        SearchPkt(GCRSBaseNetPkt* pkt):m_Pkt(pkt){};
        bool operator()(GCRSBaseComTask* task){
            if(task == NULL)return false;
            GCRSROVERComTask* drgTask = ConvertToRoverTask(task);
            long vinSrc = drgTask->getReqPkt()->getVinOriginSrc();
            simtime_t timestamp = drgTask->getReqPkt()->getTimestamp();
            if (vinSrc == this->m_Pkt->getVinOriginSrc() &&
                    timestamp == this->m_Pkt->getTimestamp()){
                return true;
            }
            return false;
        }
    private:
        GCRSBaseNetPkt* m_Pkt;
    };

    class CleanUp {
    public:
        bool operator()(GCRSBaseComTask* task) {
            if (task != NULL) {
                GCRSROVERComTask* drgTask = ConvertToRoverTask(task);
                delete drgTask;
            }
            return true;
        }
    };
protected:
    virtual long searchPkt(GCRSBaseNetPkt*);
    virtual void cleanUp();
};

#endif /* GCRSROVERCOMTASKMANAGER_H_ */
