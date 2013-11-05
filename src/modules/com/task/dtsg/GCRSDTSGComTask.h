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

#ifndef GCRSDTSGCOMTASK_H_
#define GCRSDTSGCOMTASK_H_

#include "GCRSBaseComTask.h"

class GCRSDTSGComTask: public GCRSBaseComTask {
public:
    enum state_category{
        SC_IDLE = 0, SC_RELAY = 1, SC_SLEEP = 2, SC_KEEPMESSAGEALIVE = 3, SC_CANCEL = 4
    };
public:
    GCRSDTSGComTask();
    GCRSDTSGComTask(long taskId, long runningEventId, long expireEventId,
            GCRSBaseNetPkt* pkt);
    virtual ~GCRSDTSGComTask();
    virtual void toIdle(){
        this->setState(SC_IDLE);
    }

    virtual void toRelay() {
        this->setState(SC_RELAY);
    }

    virtual void toSleep() {
        this->setState(SC_SLEEP);
    }

    virtual void toKeepMessageAlive() {
        this->setState(SC_KEEPMESSAGEALIVE);
    }
    virtual void toCancel(){
        this->setState(SC_CANCEL);
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

    virtual bool isCancel(){
        return this->getState() == SC_CANCEL ? true: false;
    }

    virtual void rxAckFromHelpVehicle(){
        ++this->m_AckFromHelpVehicle;
    }
    virtual void rxAckFromIntendedVehicle(){
        ++this->m_AckFromIntendedVehicle;
    }
    virtual void setBroadcastOnce(bool YorN){
        this->m_isBroadcastOnce = YorN;
    }
    virtual long getAckFromHelpVehicle(){
        return this->m_AckFromHelpVehicle;
    }
    virtual long getAckFromIntendedVehicle(){
        return this->m_AckFromIntendedVehicle;
    }
    virtual bool isBroadcastOnce(){
        return this->m_isBroadcastOnce;
    }

protected:
    long m_AckFromHelpVehicle;
    long m_AckFromIntendedVehicle;
    bool m_isBroadcastOnce;
};

#endif /* GCRSDTSGCOMTASK_H_ */
