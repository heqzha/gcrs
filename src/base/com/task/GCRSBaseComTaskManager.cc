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

#include "GCRSBaseComTaskManager.h"
#include <algorithm>//std::remove_if std::find_if std::sort

GCRSBaseComTaskManager::GCRSBaseComTaskManager() {
    this->m_BufferMaxSize = 0;
    this->m_taskIdCounter = 0;
    this->m_TaskBuffer = std::vector<GCRSBaseComTask*>();
}

GCRSBaseComTaskManager::GCRSBaseComTaskManager(unsigned int maxSize) {
    this->m_BufferMaxSize = maxSize;
    this->m_taskIdCounter = 0;
    this->m_TaskBuffer = std::vector<GCRSBaseComTask*>();
}

GCRSBaseComTaskManager::~GCRSBaseComTaskManager() {
    this->cleanUp();
}

long GCRSBaseComTaskManager::addTask(long runningEventId, long expireEventId,
        GCRSBaseNetPkt* pkt, simtime_t expireTime) {
    if (this->m_BufferMaxSize <= 0
            || this->m_BufferMaxSize <= this->m_TaskBuffer.size()) {
        return -1;
    }
    GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
    GCRSBaseComTask* task = new GCRSBaseComTask(this->getUniqueTaskId(),
            runningEventId, expireEventId, pktCopy);
    task->setExpireTime(expireTime);
    this->m_TaskBuffer.push_back(task);
    return task->getTaskId();
}

void GCRSBaseComTaskManager::setTaskState(long taskId, int state) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if (task == NULL)
        return;
    task->setState(state);
}

void GCRSBaseComTaskManager::setNextEventTime(long taskId, simtime_t t) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if (task == NULL)
        return;
    task->setNextEventTime(t);
}

void GCRSBaseComTaskManager::setScheduleTime(long taskId) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if (task == NULL)
        return;
    task->setScheduleTime(simTime());
}

long GCRSBaseComTaskManager::getTaskIdByRunningEventId(long runningEventId){
    GCRSBaseComTask* task = this->searchTaskByRunningEventId(runningEventId);
    if(task == NULL)return -1;
    return task->getTaskId();
}

long GCRSBaseComTaskManager::getTaskIdByExpireEventId(long expireEventId){
    GCRSBaseComTask* task = this->searchTaskByExpireEventId(expireEventId);
    if(task == NULL)return -1;
    return task->getTaskId();
}

long GCRSBaseComTaskManager::getRunningEventId(long taskId) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if(task == NULL)return -1;
    return task->getRunningEventId();
}

long GCRSBaseComTaskManager::getExpireEventId(long taskId) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if(task == NULL)return -1;
    return task->getExpireEventId();
}

simtime_t GCRSBaseComTaskManager::getNextEventTime(long taskId) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if(task == NULL)return 0;
    return task->getNextEventTime();
}

simtime_t GCRSBaseComTaskManager::getExpireEventTime(long taskId) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if(task == NULL)return 0;
    return task->getExpireTime();
}

simtime_t GCRSBaseComTaskManager::getScheduleTime(long taskId){
    GCRSBaseComTask* task = this->searchTask(taskId);
    if(task == NULL)return 0;
    return task->getScheduleTime();
}

GCRSBaseNetPkt* GCRSBaseComTaskManager::getPkt(long taskId) {
    GCRSBaseComTask* task = this->searchTask(taskId);
    if(task == NULL)return NULL;
    return task->getPkt();
}

unsigned int GCRSBaseComTaskManager::getBufferSize() {
    return this->m_TaskBuffer.size();
}

long GCRSBaseComTaskManager::getTaskIdByPkt(GCRSBaseNetPkt* pkt) {
    return this->searchPkt(pkt);
}

bool GCRSBaseComTaskManager::hasSamePkt(GCRSBaseNetPkt* pkt){
    return (this->getTaskIdByPkt(pkt) >= 0) ?true:false;
}

GCRSBaseComTask* GCRSBaseComTaskManager::searchTask(long taskId) {
    if(this->m_TaskBuffer.empty())return NULL;
    std::vector<GCRSBaseComTask*>::iterator iter;
    iter = std::find_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),SearchTask(taskId));
    if(iter == this->m_TaskBuffer.end()){
        return NULL;
    }
    return (*iter);
}

GCRSBaseComTask* GCRSBaseComTaskManager::searchTaskByRunningEventId(long runningEventId){
    if(this->m_TaskBuffer.empty())return NULL;
    std::vector<GCRSBaseComTask*>::iterator iter;
    iter = std::find_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),SearchTaskByRunningEventId(runningEventId));
    if(iter == this->m_TaskBuffer.end()){
        return NULL;
    }
    return (*iter);
}

GCRSBaseComTask* GCRSBaseComTaskManager::searchTaskByExpireEventId(long expireEventId){
    if(this->m_TaskBuffer.empty())return NULL;
    std::vector<GCRSBaseComTask*>::iterator iter;
    iter = std::find_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),SearchTaskByExpireEventId(expireEventId));
    if(iter == this->m_TaskBuffer.end()){
        return NULL;
    }
    return (*iter);
}

long GCRSBaseComTaskManager::searchPkt(GCRSBaseNetPkt* pkt) {
    if(pkt == NULL || this->m_TaskBuffer.empty())return -1;
    std::vector<GCRSBaseComTask*>::iterator iter;
    iter = std::find_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),SearchPkt(pkt));
    if(iter == this->m_TaskBuffer.end()){
        return -1;
    }
    return (*iter)->getTaskId();
}

void GCRSBaseComTaskManager::cleanUp() {
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    CleanUp()), this->m_TaskBuffer.end());
}

long GCRSBaseComTaskManager::getUniqueTaskId() {
    return this->m_taskIdCounter++;
}
