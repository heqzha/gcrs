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

#ifndef GCRSFLOODINGNETLAYER_H_
#define GCRSFLOODINGNETLAYER_H_

#include "GCRSBaseNetLayer.h"
#include "GCRSFloodingComTaskManager.h"

class GCRSFloodingNetLayer: public GCRSBaseNetLayer {
public:
    virtual void initialize(int);
protected:
    virtual void handleTaskFromUpper(long taskId);
    virtual void handleScheduleTask(long taskId, GCRSBaseComCollectNode::range_category zone);
    virtual bool handleSendUp(GCRSBaseNetPkt* pkt, GCRSBaseComCollectNode::range_category zone);
    virtual void handleTaskAck(long taskId,GCRSBaseComCollectNode::range_category zone);
    virtual void handleRunningEvent(long runningEventId);

    virtual double calcBackoffTime();
protected:
    GCRSFloodingComTaskManager* floodingTaskManager;
    double cwMax;
    double st;
};

#endif /* GCRSFLOODINGNETLAYER_H_ */
