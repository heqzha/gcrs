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

#ifndef GCRSBASECOMTTL_H_
#define GCRSBASECOMTTL_H_
#include <omnetpp.h>

class GCRSBaseComTTL {
public:
    GCRSBaseComTTL();
    virtual ~GCRSBaseComTTL();

    void setCreateTime(simtime_t t){
        this->m_CreateT = t;
    }
    void setUpdateTime(simtime_t t){
        this->m_UpdateT = t;
    }
    void setTTL(simtime_t t){
        this->m_TTL = t;
    }

    simtime_t getCreateTime(){
        return this->m_CreateT;
    }
    simtime_t getUpdateTime(){
        return this->m_UpdateT;
    }
    simtime_t getTTL(){
        return this->m_TTL;
    }

    simtime_t getExpireTime(){
        return this->m_CreateT + this->m_UpdateT + this->m_TTL;
    }

    bool isExpires(simtime_t t){
        return t >= this->getExpireTime()? true:false;
    }
protected:
    simtime_t m_CreateT;
    simtime_t m_UpdateT;
    simtime_t m_TTL;
};

#endif /* GCRSBASECOMTTL_H_ */
