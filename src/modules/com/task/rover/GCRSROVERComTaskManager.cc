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

#include "GCRSROVERComTaskManager.h"
#include <algorithm>//std::remove_if std::find_if std::sort
GCRSROVERComTaskManager::GCRSROVERComTaskManager() :
        GCRSBaseComTaskManager() {
    // TODO Auto-generated constructor stub

}

GCRSROVERComTaskManager::GCRSROVERComTaskManager(unsigned int maxSize) :
        GCRSBaseComTaskManager(maxSize) {
    // TODO Auto-generated constructor stub

}

GCRSROVERComTaskManager::~GCRSROVERComTaskManager() {
    this->cleanUp();
}

long GCRSROVERComTaskManager::addTask(long runningEventId, long expireEventId,
        GCRSBaseNetPkt* pkt, simtime_t expireTime) {
    if (this->m_BufferMaxSize <= 0
            || this->m_BufferMaxSize <= this->m_TaskBuffer.size()) {
        return -1;
    };
    GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(pkt->dup());
    if (pktCopy == NULL)
        return -1;
    GCRSROVERComTask *task = new GCRSROVERComTask(this->getUniqueTaskId(),
            runningEventId, expireEventId, pktCopy);
    task->setExpireTime(expireTime);
    this->m_TaskBuffer.push_back(task);
    return task->getTaskId();
}

void GCRSROVERComTaskManager::deleteTask(long taskId) {
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    DeleteTask(taskId)), this->m_TaskBuffer.end());
}

void GCRSROVERComTaskManager::addData(long taskId, int kind, GCRSBaseNetPkt* dataPkt) {
    if (dataPkt == NULL)
        return;
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if (task == NULL)
        return;
    GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(dataPkt->dup());
    if (pktCopy == NULL)
        return;
    pktCopy->setKind(kind);
    task->setDataPkt(pktCopy);
}

bool GCRSROVERComTaskManager::hasDataPkt(long taskId) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return false;
    GCRSBaseNetPkt* dataPkt = task->getDataPkt();
    if(dataPkt == NULL)
        return false;
    return true;
}

void GCRSROVERComTaskManager::toReply(long taskId, int kind) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return;
    GCRSBaseNetPkt* repPkt = task->getRepPkt();
    if(repPkt == NULL) {
        GCRSBaseNetPkt* reqPkt = task->getReqPkt();
        GCRSBaseNetPkt* pktCopy = check_and_cast<GCRSBaseNetPkt*>(reqPkt->dup());
        if(pktCopy == NULL)return;
        pktCopy->setKind(kind);
        pktCopy->setVinDest(reqPkt->getVinForwardSrc());
        task->setRepPkt(pktCopy);
    }
    task->toReply();
}

void GCRSROVERComTaskManager::toRequest(long taskId, int kind) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return;
    GCRSBaseNetPkt* reqPkt = task->getReqPkt();
    reqPkt->setKind(kind);
    task->toRequest();
}

void GCRSROVERComTaskManager::toData(long taskId, int kind,
        GCRSBaseNetPkt* repData) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return;
    GCRSBaseNetPkt* dataPkt = task->getDataPkt();
    if(dataPkt == NULL) return;
    dataPkt->setKind(kind);
    dataPkt->setVinDest(repData->getVinForwardSrc());
    task->toData();
}

bool GCRSROVERComTaskManager::isIdle(long taskId) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isIdle();
}

bool GCRSROVERComTaskManager::isReply(long taskId) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isReply();
}

bool GCRSROVERComTaskManager::isRequest(long taskId) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isRequest();
}

bool GCRSROVERComTaskManager::isData(long taskId) {
    GCRSROVERComTask* task = ConvertToRoverTask(this->searchTask(taskId));
    if(task == NULL)return false;
    return task->isData();
}

long GCRSROVERComTaskManager::searchPkt(GCRSBaseNetPkt* pkt) {
    if (pkt == NULL || this->m_TaskBuffer.empty())
        return -1;
    std::vector<GCRSBaseComTask*>::iterator iter;
    iter = std::find_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
            SearchPkt(pkt));
    if (iter == this->m_TaskBuffer.end()) {
        return -1;
    }
    return (*iter)->getTaskId();
}

void GCRSROVERComTaskManager::cleanUp() {
    this->m_TaskBuffer.erase(
            std::remove_if(this->m_TaskBuffer.begin(), this->m_TaskBuffer.end(),
                    CleanUp()), this->m_TaskBuffer.end());
}
