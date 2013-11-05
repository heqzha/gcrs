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

#ifndef GCRSDTSGNETLAYER_H_
#define GCRSDTSGNETLAYER_H_

#include "GCRSBaseNetLayer.h"
#include "GCRSDTSGComTaskManager.h"
#include "GCRSDTSGNetPkt_m.h"

class GCRSDTSGNetLayer: public GCRSBaseNetLayer {
public:
    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int);
protected:
    /*
     * Implement in derive
     */
    virtual void handleNewTask(long taskId);
    virtual void handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone);
    virtual bool handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone);
    virtual bool handleIsAck(GCRSBaseNetPkt* pkt,GCRSBaseComCollectNode::range_category zone);
    virtual void handleTaskAck(long taskId, GCRSBaseComCollectNode::range_category zone);
    virtual void handleTaskOutZone(GCRSBaseNetPkt* pkt, GCRSBaseComNin::NinL3Type nin);
    virtual void handleRunningEvent(long runningEventId);
    virtual GCRSBaseNetPkt* packetBaseNetPkt(const char *name, int kind,
            cObject* cInfo);

    virtual bool isInExtraRegion(GCRSBaseNetPkt* pkt);
    virtual GCRSDTSGNetPkt* convertBasePktToDTSGPkt(GCRSBaseNetPkt* pkt);
    virtual bool getPreStableFlg(GCRSBaseNetPkt* pkt);
    virtual void setPreStableFlg(GCRSBaseNetPkt* pkt, bool flg);
    virtual simtime_t calcCompetitionBackoffTime(double txRange, Coord srcLoc, Coord myLoc);
    virtual simtime_t calcBackoffTime();
    virtual double calcExtraRegionLength(double zoneLength, double vehicleDensity);
protected:
    GCRSDTSGComTaskManager* dtsgTaskManager;
};

#endif /* GCRSDTSGNETLAYER_H_ */
