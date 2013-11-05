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

#include "GCRSROVERComTask.h"

GCRSROVERComTask::GCRSROVERComTask() :
        GCRSBaseComTask() {
    this->m_State = SC_IDLE;
    this->m_ReqPkt = NULL;
    this->m_RepPkt = NULL;
    this->m_DataPkt = NULL;
}
GCRSROVERComTask::GCRSROVERComTask(long taskId, long runningEventId,
        long expireEventId, GCRSBaseNetPkt* pkt) :
        GCRSBaseComTask(taskId, runningEventId, expireEventId, pkt) {
    this->m_State = SC_IDLE;
    this->m_ReqPkt = this->m_Pkt;
    this->m_RepPkt = NULL;
    this->m_DataPkt = NULL;
}
GCRSROVERComTask::~GCRSROVERComTask() {
    if(this->m_ReqPkt != NULL)
        delete this->m_ReqPkt;
    if(this->m_RepPkt != NULL)
        delete this->m_RepPkt;
    if(this->m_DataPkt != NULL)
        delete this->m_DataPkt;
    this->m_ReqPkt = NULL;
    this->m_RepPkt = NULL;
    this->m_DataPkt = NULL;
    this->m_Pkt = NULL;
}

void GCRSROVERComTask::setReqPkt(GCRSBaseNetPkt* pkt) {
    if (pkt == NULL)
        return;
    if(this->m_ReqPkt != NULL)
        return;
    this->m_ReqPkt = pkt;
}

void GCRSROVERComTask::setRepPkt(GCRSBaseNetPkt* pkt) {
    if (pkt == NULL)
        return;
    if(this->m_RepPkt != NULL)
        return;
    this->m_RepPkt = pkt;
}

void GCRSROVERComTask::setDataPkt(GCRSBaseNetPkt* pkt) {
    if (pkt == NULL)
        return;
    if(this->m_DataPkt != NULL)
        return;
    this->m_DataPkt = pkt;
}
