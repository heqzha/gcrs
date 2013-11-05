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

#include "GCRSDTSGComTaskManager.h"
#include <algorithm>//std::remove_if std::find_if std::sort

GCRSDTSGComTaskManager::GCRSDTSGComTaskManager():GCRSBaseComTaskManager(){

}
GCRSDTSGComTaskManager::GCRSDTSGComTaskManager(unsigned int maxSize):GCRSBaseComTaskManager(maxSize) {
    // TODO Auto-generated constructor stub

}

GCRSDTSGComTaskManager::~GCRSDTSGComTaskManager() {
    this->cleanUp();
}

long GCRSDTSGComTaskManager::addTask(long runningEventId, long expireEventId,
        GCRSBaseNetPkt* pkt, simtime_t expireTime){
    if (this->m_BufferMaxSize <= 0
            || this->m_BufferMaxSize <= this->m_TaskBuffer.size()) {
        return -1;
    }
    GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
    GCRSDTSGComTask *task = new GCRSDTSGComTask(this->getUniqueTaskId(),
                runningEventId, expireEventId, pktCopy);
    task->setExpireTime(expireTime);
    this->m_TaskBuffer.push_back(task);
    return task->getTaskId();
}

void GCRSDTSGComTaskManager::deleteTask(long taskId){
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    DeleteTask(taskId)), this->m_TaskBuffer.end());
}

void GCRSDTSGComTaskManager::toIdle(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toIdle();
}

void GCRSDTSGComTaskManager::toRelay(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toRelay();
}

void GCRSDTSGComTaskManager::toKeepMesssageAlive(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toKeepMessageAlive();
}

void GCRSDTSGComTaskManager::toSleep(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toSleep();
}

void GCRSDTSGComTaskManager::toCancel(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return;
    task->toCancel();
}

bool GCRSDTSGComTaskManager::isIdle(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isIdle();
}

bool GCRSDTSGComTaskManager::isRelay(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isRelay();
}

bool GCRSDTSGComTaskManager::isSleep(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return false;
     return task->isSleep();
}

bool GCRSDTSGComTaskManager::isKeepMessageAlive(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return false;
     return task->isKeepMessageAlive();
}

bool GCRSDTSGComTaskManager::isCancel(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isCancel();
}

void GCRSDTSGComTaskManager::rxAckFromHelpVehicle(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return;
     task->rxAckFromHelpVehicle();
}

void GCRSDTSGComTaskManager::rxAckFromIntendedVehicle(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return;
     task->rxAckFromIntendedVehicle();
}

void GCRSDTSGComTaskManager::setBroadcastOnce(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return;
     task->setBroadcastOnce(true);
}

void GCRSDTSGComTaskManager::setBroadcast(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return;
     task->setBroadcastOnce(false);
}

long GCRSDTSGComTaskManager::getAckFromHelpVehicle(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return -1;
     return task->getAckFromHelpVehicle();
}

long GCRSDTSGComTaskManager::getAckFromIntendedVehicle(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return -1;
     return task->getAckFromIntendedVehicle();
}

bool GCRSDTSGComTaskManager::isBroadcastOnce(long taskId){
    GCRSDTSGComTask* task = ConvertToDTSGTask(this->searchTask(taskId));
     if(task == NULL)return false;
     return task->isBroadcastOnce();
}

void GCRSDTSGComTaskManager::cleanUp(){
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    CleanUp()), this->m_TaskBuffer.end());
}
