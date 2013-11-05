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

#ifndef GCRSDRGCOMTASKMANAGER_H_
#define GCRSDRGCOMTASKMANAGER_H_

#include "GCRSBaseComTaskManager.h"
#include "GCRSDRGComTask.h"

#define ConvertToDRGTask(task) dynamic_cast<GCRSDRGComTask*>(task)

class GCRSDRGComTaskManager: public GCRSBaseComTaskManager {
public:
    GCRSDRGComTaskManager();
    GCRSDRGComTaskManager(unsigned int maxSize);
    virtual ~GCRSDRGComTaskManager();

    virtual long addTask(long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt, simtime_t expireTime);
    virtual void deleteTask(long taskId);

    virtual void toRelay(long taskId);
    virtual void toKeepMesssageAlive(long taskId);
    virtual void toSleep(long taskId);
    virtual bool isIdle(long taskId);
    virtual bool isRelay(long taskId);
    virtual bool isSleep(long taskId);
    virtual bool isKeepMessageAlive(long taskId);
    virtual void reTx(long taskId);
    virtual long getReTx(long taskId);
    virtual void resetReTx(long taskId);

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
                GCRSDRGComTask* drgTask = ConvertToDRGTask(task);
                delete drgTask;
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
                GCRSDRGComTask* drgTask = ConvertToDRGTask(task);
                delete drgTask;
            }
            return true;
        }
    };
protected:
    virtual void cleanUp();
};

#endif /* GCRSDRGCOMTASKMANAGER_H_ */
