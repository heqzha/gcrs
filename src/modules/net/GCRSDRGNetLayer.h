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

#ifndef GCRSDRGNETLAYER_H_
#define GCRSDRGNETLAYER_H_

#include "GCRSBaseNetLayer.h"
#include "GCRSDRGComTaskManager.h"

class GCRSDRGNetLayer: public GCRSBaseNetLayer {
public:
    virtual void initialize(int);

protected:
    virtual void handleNewTask(long taskId);
    virtual void handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone);
    virtual bool handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone);
    virtual bool handleIsAck(GCRSBaseNetPkt* pkt,GCRSBaseComCollectNode::range_category zone);
    virtual void handleTaskAck(long taskId,GCRSBaseComCollectNode::range_category zone);
    virtual void handleRunningEvent(long runningEventId);

    virtual simtime_t calcBackoffTime();
    virtual simtime_t calcDistanceBOd(double Rtx, double distance);
    virtual simtime_t calcPersistenceTime(double e, double rTx, double vMax, double minCW, double maxCW);
    virtual double calcCriterionAngle(double distance, double rTx);
protected:
    GCRSDRGComTaskManager* drgTaskManager;

    simtime_t longBOd;
    simtime_t maxBOd;
    int maxReTx;
    simtime_t mimCW;
    simtime_t maxCW;
    double sd;//distance sensitivity factor
    double epsilon; //a factor for calculate persistence time.
    double maxCriterionAngle;
};

#endif /* GCRSDRGNETLAYER_H_ */
