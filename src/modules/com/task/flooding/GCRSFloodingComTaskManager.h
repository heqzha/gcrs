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

#ifndef GCRSFLOODINGCOMTASKMANAGER_H_
#define GCRSFLOODINGCOMTASKMANAGER_H_

#include "GCRSBaseComTaskManager.h"
#include "GCRSFloodingComTask.h"

#define ConvertToFooldingTask(task) dynamic_cast<GCRSFloodingComTask*>(task)
class GCRSFloodingComTaskManager: public GCRSBaseComTaskManager {
public:
    GCRSFloodingComTaskManager();
    GCRSFloodingComTaskManager(unsigned int maxSize);
    virtual ~GCRSFloodingComTaskManager();

    virtual long addTask(long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt, simtime_t expireTime);
    virtual void deleteTask(long taskId);

    virtual bool isRxAck(long taskId);
    virtual void rxAck(long taskId);
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
                GCRSFloodingComTask* floodingTask = ConvertToFooldingTask(task);
                delete floodingTask;
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
                GCRSFloodingComTask* floodingTask = ConvertToFooldingTask(task);
                delete floodingTask;
            }
            return true;
        }
    };

protected:
    virtual void cleanUp();

protected:
};

#endif /* GCRSFLOODINGCOMTASKMANAGER_H_ */
