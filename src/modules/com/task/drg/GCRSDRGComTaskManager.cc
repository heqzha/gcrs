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

#include "GCRSDRGComTaskManager.h"
#include <algorithm>//std::remove_if std::find_if std::sort

GCRSDRGComTaskManager::GCRSDRGComTaskManager():GCRSBaseComTaskManager() {
}

GCRSDRGComTaskManager::GCRSDRGComTaskManager(unsigned int maxSize):GCRSBaseComTaskManager(maxSize) {

}

GCRSDRGComTaskManager::~GCRSDRGComTaskManager() {
    this->cleanUp();
}

long GCRSDRGComTaskManager::addTask(long runningEventId, long expireEventId,
        GCRSBaseNetPkt* pkt, simtime_t expireTime){
    if (this->m_BufferMaxSize <= 0
            || this->m_BufferMaxSize <= this->m_TaskBuffer.size()) {
        return -1;
    }
    GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
    GCRSDRGComTask *task = new GCRSDRGComTask(this->getUniqueTaskId(),
            runningEventId, expireEventId, pktCopy);
    task->setExpireTime(expireTime);
    this->m_TaskBuffer.push_back(task);
    return task->getTaskId();
}

void GCRSDRGComTaskManager::deleteTask(long taskId){
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    DeleteTask(taskId)), this->m_TaskBuffer.end());
}

void GCRSDRGComTaskManager::toRelay(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toRelay();
}

void GCRSDRGComTaskManager::toKeepMesssageAlive(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toKeepMessageAlive();
}

void GCRSDRGComTaskManager::toSleep(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toSleep();
}

bool GCRSDRGComTaskManager::isIdle(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isIdle();
}

bool GCRSDRGComTaskManager::isRelay(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isRelay();
}

bool GCRSDRGComTaskManager::isSleep(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isSleep();
}

bool GCRSDRGComTaskManager::isKeepMessageAlive(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isKeepMessageAlive();
}

void GCRSDRGComTaskManager::reTx(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->reTx();
}

long GCRSDRGComTaskManager::getReTx(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return -1;
    return task->getReTx();
}

void GCRSDRGComTaskManager::resetReTx(long taskId){
    GCRSDRGComTask* task = ConvertToDRGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->resetReTx();
}

void GCRSDRGComTaskManager::cleanUp(){
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    CleanUp()), this->m_TaskBuffer.end());
}
