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

#ifndef GCRSBASEAPPLAYER_H_
#define GCRSBASEAPPLAYER_H_

#include <BaseApplLayer.h>
#include "GCRSBaseComVin.h"
#include "GCRSBaseComNin.h"
#include "GCRSBasePkt_m.h"
#include "GCRSBaseComGeoInfoBuffer.h"
#include "GCRSBaseTraCIMobility.h"
#include "GCRSBaseVehicleManager.h"
#include "GCRSBaseCollectionService.h"

class GCRSBaseAppLayer: public BaseApplLayer {
protected:
    enum msg_category{
        MC_SELF_MESSAGE = 0
    };
    enum pkt_category{
        PC_BASE_MESSAGE = 0, PC_ACCIDENT_MESSAGE = 1, PC_EMERGENCY_MESSAGE = 2
    };
public:
    virtual void initialize(int stage);
    virtual void finish();

protected:
    /** @brief handle messages from below */
    virtual void handleLowerMsg(cMessage* msg);
    /** @brief handle self messages */
    virtual void handleSelfMsg(cMessage* msg);

    virtual void handleEvent(GCRSBaseComVin::VinL3Type vin){};

    virtual GCRSBasePkt* preparePkt(int ctrlType, GCRSBaseComNin::NinL3Type nin, int priorityClass, GCRSBaseComVin::VinL3Type dest, int priority, int pktType);
    virtual void sendPkt(GCRSBasePkt* pkt);

protected:
    cMessage* selfMsg;

    GCRSBaseComGeoInfoBuffer geoInfoBuffer;
    simtime_t selfMsgInterval;
    simtime_t individualOffset;
    bool isOnSch;
    int priorityClass;


    GCRSBaseComVin::VinL3Type vin;
    GCRSBaseComNin::NinL3Type nin;

    /*
     * Vehicle Manager
     */
    GCRSBaseVehicleManager* vManager;
    /*
     * Mobility Control
     */
    GCRSBaseTraCIMobility* traciMobility;
    /*
     *Communication Data Collection Service
     */
    GCRSBaseCollectionService* collectionService;

};

#endif /* GCRSBASEAPPLAYER_H_ */
