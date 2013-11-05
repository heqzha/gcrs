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

#ifndef GCRSBASENETLAYER_H_
#define GCRSBASENETLAYER_H_

#include <BaseNetwLayer.h>
#include <vector>
#include "GCRSBaseNetPkt_m.h"
#include "GCRSBaseComZone.h"
#include "GCRSBaseComVehicleState.h"
#include "GCRSBaseTraCIMobility.h"
#include "GCRSBaseVehicleManager.h"
#include "GCRSBaseCollectionService.h"
#include "GCRSBaseComNetwControlInfo.h"
#include "GCRSBaseComTaskManager.h"

class GCRSBaseNetLayer: public BaseNetwLayer {
public:
    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int);
    virtual void finish();
protected:
    enum pkt_category {
        PC_BASE_NETWORK_PKT = 0
    };
    enum msg_category {
        MC_RUNNING = 0, MC_EXPIRE = 1, MC_EXTRA = 2
    };
protected:
    /**
     * @name Handle Messages
     * @brief Functions to redefine by the programmer
     *
     * These are the functions provided to add own functionality to your
     * modules. These functions are called whenever a self message or a
     * data message from the upper or lower layer arrives respectively.
     *
     **/
    /*@{*/

    /** @brief Handle messages from upper layer */
    virtual void handleUpperMsg(cMessage* msg);

    /** @brief Handle messages from lower layer */
    virtual void handleLowerMsg(cMessage* msg);

    /** @brief Handle self messages */
    virtual void handleSelfMsg(cMessage* msg);

    /** @brief Handle control messages from lower layer */
    virtual void handleLowerControl(cMessage* msg);

    /** @brief Handle control messages from upper layer */
    virtual void handleUpperControl(cMessage * msg);

    /** @brief decapsulate higher layer message from NetwPkt */
    virtual cMessage* decapsMsg(GCRSBaseNetPkt* pkt);

    /** @brief Encapsulate higher layer packet into an NetwPkt*/
    virtual NetwPkt* encapsMsg(cPacket*);

    /**
     * @brief Attaches a "control info" (NetwToMac) structure (object) to the message pMsg.
     *
     * This is most useful when passing packets between protocol layers
     * of a protocol stack, the control info will contain the destination MAC address.
     *
     * The "control info" object will be deleted when the message is deleted.
     * Only one "control info" structure can be attached (the second
     * setL3ToL2ControlInfo() call throws an error).
     *
     * @param pMsg      The message where the "control info" shall be attached.
     * @param pDestAddr The MAC address of the message receiver.
     */
    virtual cObject * const setDownControlInfo(cMessage * const pMsg,
            const LAddress::L2Type& pDestAddr);
    /**
     * @brief Attaches a "control info" (NetwToUpper) structure (object) to the message pMsg.
     *
     * This is most useful when passing packets between protocol layers
     * of a protocol stack, the control info will contain the destination MAC address.
     *
     * The "control info" object will be deleted when the message is deleted.
     * Only one "control info" structure can be attached (the second
     * setL3ToL2ControlInfo() call throws an error).
     *
     * @param pMsg      The message where the "control info" shall be attached.
     * @param pSrcAddr  The MAC address of the message receiver.
     */
    virtual cObject * const setUpControlInfo(cMessage * const pMsg,
            const LAddress::L3Type& pSrcAddr);
    /*
     *GCRS Network Layer Framework Functions
     */
    virtual long handleTask(GCRSBaseNetPkt* pkt);
    virtual void handleCreateTask(GCRSBaseNetPkt* pkt);
    virtual void handleUpdateTask(GCRSBaseNetPkt* pkt);
    virtual void handleScheduleRunningEvent(long taskId);
    virtual void handleScheduleExpireEvent(long taskId);
    virtual bool handleSchedule(long eventId, simtime_t t);
    virtual void handleExpireEvent(long expireEventId);
    virtual GCRSBaseNetPkt* packetBaseNetPkt(const char *name, int kind,
            cObject* cInfo);
    virtual void handleSendDown(long eventId);
    virtual void handleTaskInZone(GCRSBaseNetPkt* pkt, GCRSBaseComNin::NinL3Type nin ,GCRSBaseComCollectNode::range_category zone);


    /*
     * Implement in derive
     */
    virtual void handleNewTask(long taskId) {
    }
    ;
    virtual void handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone){

    };
    virtual bool handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone){
        return false;
    };
    virtual bool handleIsAck(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone) {
        return true;
    }
    ;
    virtual void handleTaskAck(long taskId,GCRSBaseComCollectNode::range_category zone) {
    }
    ;
    virtual void handleRunningEvent(long runningEventId) {
    }
    virtual void handleTaskOutZone(GCRSBaseNetPkt* pkt, GCRSBaseComNin::NinL3Type nin){};
    ;

protected:
    class SearchEvent {
    public:
        SearchEvent(long eventId) :
                m_EventId(eventId) {
        }
        ;
        bool operator()(cMessage* event) {
            if (event == NULL)
                return false;
            if (this->m_EventId == event->getId()) {
                return true;
            }
            return false;
        }
    private:
        long m_EventId;
    };
    class DeleteEvent {
    public:
        DeleteEvent(long eventId, GCRSBaseNetLayer* layer) :
                m_EventId(eventId), m_Layer(layer) {
        }
        ;
        bool operator()(cMessage* event) {
            if (event == NULL)
                return true;
            if (this->m_EventId == event->getId()) {
                if (event->isScheduled()) {
                    this->m_Layer->cancelAndDelete(event);
                } else {
                    delete (event);
                }
                return true;
            }
            return false;
        }
    private:
        long m_EventId;
        GCRSBaseNetLayer* m_Layer;
    };
    class CleanUp {
    public:
        CleanUp(GCRSBaseNetLayer* layer) :
                m_Layer(layer) {
        }
        ;
        bool operator()(cMessage* event) {
            if (event == NULL)
                return true;
            if (event->isScheduled()) {
                this->m_Layer->cancelAndDelete(event);
            } else {
                delete (event);
            }
            return true;
        }
    private:
        GCRSBaseNetLayer* m_Layer;
    };

protected:
    virtual cMessage* seachEvent(long eventId);
    virtual void deleteEvent(long eventId);
    virtual void cleanUp();
protected:
    std::vector<cMessage*> eventBuffer;
    GCRSBaseComTaskManager* tManager;

    //@brief Vehicle State
    GCRSBaseTraCIMobility* traciMobility;
    GCRSBaseVehicleManager* vManager;
    GCRSBaseComVin::VinL3Type vin;
    GCRSBaseCollectionService* collectionService;
    GCRSBaseConnectionManager* connectionManager;
};

#endif /* GCRSBASENETLAYER_H_ */
