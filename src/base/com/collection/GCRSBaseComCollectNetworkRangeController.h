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

#ifndef GCRSBASECOMCOLLECTNETWORKRANGECONTROLLER_H_
#define GCRSBASECOMCOLLECTNETWORKRANGECONTROLLER_H_
#include <map>
#include "GCRSBaseComCollectNetworkRange.h"
#include "GCRSBaseComVin.h"
#include "GCRSBaseComNin.h"

class GCRSBaseComCollectNetworkRangeController {
public:
    GCRSBaseComCollectNetworkRangeController(int zorShape, int zofShape,
            double zorLength, double zofLength, double zorWidth,
            double zofWidth, double laneWidth) :
            zorShape(zorShape), zofShape(zofShape), zorLength(zorLength), zofLength(
                    zofLength), zorWidth(zorWidth), zofWidth(zofWidth), laneWidth(
                    laneWidth) {
    }
    ;
    virtual ~GCRSBaseComCollectNetworkRangeController();

    void addNetworkRange(GCRSBaseComNin::NinL3Type nin, Coord loc, double offset,
            double direct, simtime_t ttl,int landIndex, double roadWidth,Coord locJunction);
    void checkPassThroughNode(GCRSBaseComVin::VinL3Type vin, Coord loc);
    void updateTTL(GCRSBaseComNin::NinL3Type nin, simtime_t ttl);

    Coord getLocationZor(GCRSBaseComNin::NinL3Type nin);
    Coord getLocationZof(GCRSBaseComNin::NinL3Type nin);
    int getShapeZor(GCRSBaseComNin::NinL3Type nin);
    int getShapeZof(GCRSBaseComNin::NinL3Type nin);
    double getLengthZor(GCRSBaseComNin::NinL3Type nin);
    double getLengthZof(GCRSBaseComNin::NinL3Type nin);
    double getWidthZor(GCRSBaseComNin::NinL3Type nin);
    double getWidthZof(GCRSBaseComNin::NinL3Type nin);
    double getDirectionZor(GCRSBaseComNin::NinL3Type nin);
    double getDirectionZof(GCRSBaseComNin::NinL3Type nin);
    bool isInZorRange(GCRSBaseComNin::NinL3Type nin, Coord loc);
    bool isInZofRange(GCRSBaseComNin::NinL3Type nin, Coord loc);
    int getNumPassThroughZorNodes(GCRSBaseComNin::NinL3Type nin);
    int getNumPassThroughZofNodes(GCRSBaseComNin::NinL3Type nin);

protected:

    Coord calcZoneOffset(double horizontalOffset, double zoneWidth,
            double landWith, double maxLandNum, int laneIndex);
    void cleanUp();
    GCRSBaseComCollectNetworkRange* getNetworkRange(
            GCRSBaseComNin::NinL3Type nin);

protected:
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetworkRange*> mapNetworkRange;

    int zorShape;
    int zofShape;
    double zorLength;
    double zofLength;
    double zorWidth;
    double zofWidth;
    double laneWidth;
};

#endif /* GCRSBASECOMCOLLECTNETWORKRANGECONTROLLER_H_ */
