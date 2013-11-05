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

#ifndef GCRSCOMFLOODINGTASK_H_
#define GCRSCOMFLOODINGTASK_H_

#include "GCRSBaseComTask.h"

class GCRSFloodingComTask: public GCRSBaseComTask {
protected:
    enum state_category {
        SC_NOT_RX_ACK = 0, SC_RX_ACK = 1
    };
public:
    GCRSFloodingComTask();
    GCRSFloodingComTask(long taskId, long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt);
    ~GCRSFloodingComTask();

    virtual void rxAck(){
        this->m_State=SC_RX_ACK;
    }

    virtual bool isRxAck(){
        return (this->m_State == SC_RX_ACK)?true:false;
    }

};

#endif /* GCRSCOMFLOODINGTASK_H_ */
