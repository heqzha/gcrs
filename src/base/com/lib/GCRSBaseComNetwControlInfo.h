/*
 * GCRSBaseNetwControlInfo.h
 *
 *  Created on: Aug 1, 2013
 *      Author: tony
 */

#ifndef GCRSBASECOMNETWCONTROLINFO_H_
#define GCRSBASECOMNETWCONTROLINFO_H_
#include <Coord.h>
#include "GCRSBaseComVin.h"
#include "GCRSBaseComNin.h"

class GCRSBaseComNetwControlInfo: public cObject {
public:
    enum ctrl_category{
        CC_CREATE = 0, CC_UPDATE
    };
protected:
    /** @brief vin of the sending or receiving node*/
    int ctrlType;
    GCRSBaseComVin::VinL3Type destVin;
    int srcTxChannelType;
    int srcMsgPriority;
    GCRSBaseComVin::VinL3Type srcVin;
    Coord srcLocation;
    Coord srcSpeed;
    double srcSpeedMax;
    GCRSBaseComNin::NinL3Type nin;
    simtime_t timestamp;
public:

    /** @brief Constructor with geographic info*/
    GCRSBaseComNetwControlInfo(const int ctrlT = CC_CREATE, const GCRSBaseComVin::VinL3Type& dVin = GCRSBaseComVin::VINL3NULL,
            const int channelType = 1, const int priority = 3,
            const GCRSBaseComNin::NinL3Type& nin = GCRSBaseComNin::NINL3NULL,
            const GCRSBaseComVin::VinL3Type& vin = GCRSBaseComVin::VINL3NULL,
            const Coord loc = Coord(),
            const Coord speed = Coord(),
            const double speedMax = 0.0f,
            const simtime_t timestamp = 0.0f) : ctrlType(ctrlT),
            destVin(dVin), srcTxChannelType(channelType), srcMsgPriority(priority),srcVin(vin), srcLocation(
                    loc), srcSpeed(speed), srcSpeedMax(speedMax), nin(nin), timestamp(timestamp){
    }
    ;
    /** @brief Destructor*/
    virtual ~GCRSBaseComNetwControlInfo() {
    }
    ;

    /** @brief Getter method*/
    virtual const int getCtrlType(){
        return this->ctrlType;
    }

    virtual const GCRSBaseComVin::VinL3Type& getSrcVin() {
        return this->srcVin;
    }
    ;
    virtual const GCRSBaseComVin::VinL3Type& getDestVin() {
        return this->destVin;
    }
    ;

    virtual const int getSrcMsgPriority(){
        return this->srcMsgPriority;
    }
    virtual const Coord getSrcLocation() {
        return this->srcLocation;
    }
    ;
    virtual const Coord getSrcSpeed() {
        return this->srcSpeed;
    }
    ;
    virtual const double getSrcSpeedMax() {
        return this->srcSpeedMax;
    }
    ;
    virtual const int getSrcTxChannelType(){
        return this->srcTxChannelType;
    };

    virtual const GCRSBaseComNin::NinL3Type getNin(){
        return this->nin;
    };

    virtual const simtime_t getTimestamp(){
        return this->timestamp;
    };
    /** @brief Setter method*/
    virtual void setCtrlType(const int type){
        this->ctrlType = type;
    }
    virtual void setSrcVin(const GCRSBaseComVin::VinL3Type& vin) {
        this->srcVin = vin;
    }
    ;
    virtual void setDestVin(const GCRSBaseComVin::VinL3Type& vin) {
        this->destVin = vin;
    }
    ;
    virtual void setSrcMsgPriority(const int priority){
        this->srcMsgPriority = priority;
    }
    virtual void setSrcLocation(const Coord loc) {
        this->srcLocation = loc;
    }
    ;
    virtual void setSrcSpeed(const Coord speed) {
        this->srcSpeed = speed;
    }
    virtual void setSrcSpeedMax(const double speedMax) {
        this->srcSpeedMax = speedMax;
    }
    ;
    virtual void setSrcTxChannelType(const int channelType){
        this->srcTxChannelType = channelType;
    };
    virtual void setNin(const GCRSBaseComNin::NinL3Type nin){
        this->nin = nin;
    };
    virtual void setTimestamp(const simtime_t timestamp){
        this->timestamp = timestamp;
    };
    /**
     * @brief Attaches a "control info" structure (object) to the message pMsg.
     *
     * This is most useful when passing packets between protocol layers
     * of a protocol stack, the control info will contain the destination Vin.
     *
     * The "control info" object will be deleted when the message is deleted.
     * Only one "control info" structure can be attached (the second
     * setL3ToL2ControlInfo() call throws an error).
     *
     * @param pMsg  The message where the "control info" shall be attached.
     * @param pVin The network vin of to save.
     */
    static cObject * const setControlInfo(cMessage * const pMsg, int ctrlType,
            const GCRSBaseComVin::VinL3Type& pDVin, const int channelType, const int priority, const GCRSBaseComNin::NinL3Type nin) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                new GCRSBaseComNetwControlInfo(ctrlType, pDVin, channelType, priority, nin);
        pMsg->setControlInfo(cCtrlInfo);

        return cCtrlInfo;
    }
    static cObject * const setControlInfo(cMessage * const pMsg, int ctrlType,
            const GCRSBaseComVin::VinL3Type& pVin,
            const GCRSBaseComVin::VinL3Type& pDVin, const Coord loc,
            const Coord speed, const double speedMax, const int channelType,
            const int priority, const GCRSBaseComNin::NinL3Type nin, const simtime_t timestamp) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                new GCRSBaseComNetwControlInfo(ctrlType, pDVin, channelType, priority, nin,pVin, loc, speed,
                        speedMax, timestamp);
        pMsg->setControlInfo(cCtrlInfo);

        return cCtrlInfo;
    }
    /**
     * @brief extracts the address from "control info".
     */
    static const int getCtrlType(cObject * const pCtrlInfo){
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if (cCtrlInfo)
            return cCtrlInfo->getCtrlType();
        return CC_CREATE;
    }
    static const GCRSBaseComVin::VinL3Type& getSrcVinFromControlInfo(
            cObject * const pCtrlInfo) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);

        if (cCtrlInfo)
            return cCtrlInfo->getSrcVin();
        return GCRSBaseComVin::VINL3NULL;
    }
    static const GCRSBaseComVin::VinL3Type& getDestVinFromControlInfo(
            cObject * const pCtrlInfo) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if (cCtrlInfo)
            return cCtrlInfo->getDestVin();
        return GCRSBaseComVin::VINL3NULL;
    }
    static const Coord getSrcLocationFromControlInfo(cObject * const pCtrlInfo) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if (cCtrlInfo)
            return cCtrlInfo->getSrcLocation();
        return Coord();
    }
    static const Coord getSrcSpeedFromControlInfo(cObject * const pCtrlInfo) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if (cCtrlInfo)
            return cCtrlInfo->getSrcSpeed();
        return Coord();
    }
    static const double getSrcSpeedMaxFromControlInfo(
            cObject * const pCtrlInfo) {
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if (cCtrlInfo)
            return cCtrlInfo->getSrcSpeedMax();
        return 0.0f;
    }
    static const int getSrcTxChannelTypeFromControlInfo(cObject * const pCtrlInfo){
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if(cCtrlInfo)
            return cCtrlInfo->getSrcTxChannelType();
        return 1;
    }
    static const int getSrcMsgPriorityFromControlInfo(cObject * const pCtrlInfo){
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if(cCtrlInfo)
            return cCtrlInfo->getSrcMsgPriority();
        return -1;
    }
    static const GCRSBaseComNin::NinL3Type getNinFromControlInfo(cObject * const pCtrlInfo){
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if(cCtrlInfo)
            return cCtrlInfo->getNin();
        return GCRSBaseComNin::NINL3NULL;
    }
    static const simtime_t getTimestampFromControlInfo(cObject * const pCtrlInfo){
        GCRSBaseComNetwControlInfo * const cCtrlInfo =
                dynamic_cast<GCRSBaseComNetwControlInfo * const >(pCtrlInfo);
        if(cCtrlInfo)
            return cCtrlInfo->getTimestamp();
        return 0.0f;
    }
};

#endif /* GCRSBASECOMNETWCONTROLINFO_H_ */
