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

#include "GCRSFloodingComTaskManager.h"
#include <algorithm>//std::remove_if std::find_if std::sort

GCRSFloodingComTaskManager::GCRSFloodingComTaskManager():GCRSBaseComTaskManager() {
}

GCRSFloodingComTaskManager::GCRSFloodingComTaskManager(unsigned int maxSize):GCRSBaseComTaskManager(maxSize) {
}

GCRSFloodingComTaskManager::~GCRSFloodingComTaskManager() {
    this->cleanUp();
}

long GCRSFloodingComTaskManager::addTask(long runningEventId, long expireEventId,
        GCRSBaseNetPkt* pkt, simtime_t expireTime){
    if (this->m_BufferMaxSize <= 0
            || this->m_BufferMaxSize <= this->m_TaskBuffer.size()) {
        return -1;
    }
    GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
    GCRSFloodingComTask* task = new GCRSFloodingComTask(this->getUniqueTaskId(),
            runningEventId, expireEventId, pktCopy);
    task->setExpireTime(expireTime);
    this->m_TaskBuffer.push_back(task);
    return task->getTaskId();
}

void GCRSFloodingComTaskManager::deleteTask(long taskId){
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    DeleteTask(taskId)), this->m_TaskBuffer.end());
}

bool GCRSFloodingComTaskManager::isRxAck(long taskId){
    GCRSFloodingComTask* task = ConvertToFooldingTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isRxAck();
}

void GCRSFloodingComTaskManager::rxAck(long taskId){
    GCRSFloodingComTask* task = ConvertToFooldingTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->rxAck();
}

void GCRSFloodingComTaskManager::cleanUp(){
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    CleanUp()), this->m_TaskBuffer.end());
}
