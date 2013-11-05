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

#ifndef GCRSDRGCOMTASK_H_
#define GCRSDRGCOMTASK_H_

#include "GCRSBaseComTask.h"

class GCRSDRGComTask: public GCRSBaseComTask {
public:
    enum state_category {
        SC_IDLE = 0, SC_RELAY = 1, SC_SLEEP = 2, SC_KEEPMESSAGEALIVE = 3
    };
public:
    GCRSDRGComTask();
    GCRSDRGComTask(long taskId, long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt);
    virtual ~GCRSDRGComTask();

    virtual void toRelay() {
        this->setState(SC_RELAY);
    }

    virtual void toSleep() {
        this->setState(SC_SLEEP);
    }

    virtual void toKeepMessageAlive() {
        this->setState(SC_KEEPMESSAGEALIVE);
    }

    virtual bool isIdle() {
        return this->getState() == SC_IDLE ? true : false;
    }

    virtual bool isRelay() {
        return this->getState() == SC_RELAY ? true : false;
    }

    virtual bool isSleep() {
        return this->getState() == SC_SLEEP ? true : false;
    }

    virtual bool isKeepMessageAlive() {
        return this->getState() == SC_KEEPMESSAGEALIVE ? true : false;
    }

    virtual void resetReTx(){
        this->m_ReTx = 0;
    }

    virtual void reTx(){
        ++this->m_ReTx;
    }

    virtual long getReTx(){
        return this->m_ReTx;
    }
protected:
    long m_ReTx;
};

#endif /* GCRSDRGCOMTASK_H_ */
