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

#ifndef GCRSROVERCOMTASK_H_
#define GCRSROVERCOMTASK_H_

#include "GCRSBaseComTask.h"

class GCRSROVERComTask: public GCRSBaseComTask {
public:
    enum state_category {
        SC_IDLE = 0, SC_REPLY = 1, SC_REQUEST = 2, SC_DATA = 3
    };
    GCRSROVERComTask();
    GCRSROVERComTask(long taskId, long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt);
    virtual ~GCRSROVERComTask();

    virtual void setReqPkt(GCRSBaseNetPkt* pkt);
    virtual void setRepPkt(GCRSBaseNetPkt* pkt);
    virtual void setDataPkt(GCRSBaseNetPkt* pkt);

    virtual GCRSBaseNetPkt* getReqPkt() {
        return this->m_ReqPkt;
    }

    virtual GCRSBaseNetPkt* getRepPkt() {
        return this->m_RepPkt;
    }

    virtual GCRSBaseNetPkt* getDataPkt() {
        return this->m_DataPkt;
    }

    virtual void toReply() {
        this->m_State = SC_REPLY;
        this->m_Pkt = this->m_RepPkt;
    }
    virtual void toRequest() {
        this->m_State = SC_REQUEST;
        this->m_Pkt = this->m_ReqPkt;
    }
    virtual void toData() {
        this->m_State = SC_DATA;
        this->m_Pkt = this->m_DataPkt;
    }
    virtual bool isIdle() {
        return this->m_State == SC_IDLE ? true : false;
    }
    virtual bool isReply() {
        return this->m_State == SC_REPLY ? true : false;
    }
    virtual bool isRequest() {
        return this->m_State == SC_REQUEST ? true : false;
    }
    virtual bool isData() {
        return this->m_State == SC_DATA ? true : false;
    }

protected:
    GCRSBaseNetPkt* m_ReqPkt;
    GCRSBaseNetPkt* m_RepPkt;
    GCRSBaseNetPkt* m_DataPkt;
};

#endif /* GCRSROVERCOMTASK_H_ */
