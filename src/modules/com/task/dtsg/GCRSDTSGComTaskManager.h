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

#ifndef GCRSDTSGCOMTASKMANAGER_H_
#define GCRSDTSGCOMTASKMANAGER_H_

#include "GCRSBaseComTaskManager.h"
#include "GCRSDTSGComTask.h"

#define ConvertToDTSGTask(task) dynamic_cast<GCRSDTSGComTask*>(task)

class GCRSDTSGComTaskManager: public GCRSBaseComTaskManager {
public:
    GCRSDTSGComTaskManager();
    GCRSDTSGComTaskManager(unsigned int maxSize);
    virtual ~GCRSDTSGComTaskManager();

    virtual long addTask(long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt, simtime_t expireTime);
    virtual void deleteTask(long taskId);

    virtual void toIdle(long taskId);
    virtual void toRelay(long taskId);
    virtual void toKeepMesssageAlive(long taskId);
    virtual void toSleep(long taskId);
    virtual void toCancel(long taskId);

    virtual bool isIdle(long taskId);
    virtual bool isRelay(long taskId);
    virtual bool isSleep(long taskId);
    virtual bool isKeepMessageAlive(long taskId);
    virtual bool isCancel(long taskId);

    virtual void rxAckFromHelpVehicle(long taskId);
    virtual void rxAckFromIntendedVehicle(long taskId);
    virtual void setBroadcastOnce(long taskId);
    virtual void setBroadcast(long taskId);
    virtual long getAckFromHelpVehicle(long taskId);
    virtual long getAckFromIntendedVehicle(long taskId);
    virtual bool isBroadcastOnce(long taskId);

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
                GCRSDTSGComTask* dtsgTask = ConvertToDTSGTask(task);
                delete dtsgTask;
                return true;
            }
            return false;
        }
    private:
        long m_TaskId;
    };

    class CleanUp {
    public:
        bool operator()(GCRSBaseComTask* task) {
            if (task != NULL) {
                GCRSDTSGComTask* dtsgTask = ConvertToDTSGTask(task);
                delete dtsgTask;
            }
            return true;
        }
    };
protected:
    virtual void cleanUp();
};

#endif /* GCRSDTSGCOMTASKMANAGER_H_ */
