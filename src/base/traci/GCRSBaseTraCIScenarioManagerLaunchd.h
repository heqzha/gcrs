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

#ifndef GCRSBASETRACISCENARIOMANAGERLAUNCHD_H_
#define GCRSBASETRACISCENARIOMANAGERLAUNCHD_H_

#include <TraCIScenarioManagerLaunchd.h>
#include "GCRSReadXml.h"

class GCRSBaseTraCIScenarioManagerLaunchd: public TraCIScenarioManagerLaunchd {
public:
    GCRSBaseTraCIScenarioManagerLaunchd(){
        this->isInitialized = false;
    }
    virtual void initialize(int stage);
    virtual void finish();
public:
    Coord calcPlayGround();
    double calcRoadLength(Coord playground);
    bool isLane(std::string name);
    int getNumCrossRoads(){
        int numCrossRoads = this->calcNumCrossRoads(this->numJunctions);
        return numCrossRoads*numCrossRoads;
    }
    int getNumPolygonsInEachBlock();
    std::list<Coord> getCrossRoads();
    Coord getNearbyCrossRoadLocation(Coord loc, double roadWidth);
protected:
    bool isInJunction(Coord loc, Coord locJunction, double roadWidth);
    int calcNumCrossRoads(int j);
protected:
    int numJunctions;
    bool isInitialized;

    cXMLElement* xmlRoutes;
    GCRSReadXml* xmlReader;
};

class GCRSBaseTraCIScenarioManagerLaunchdAccess {
public:
    GCRSBaseTraCIScenarioManagerLaunchd* get() {
        return FindModule<GCRSBaseTraCIScenarioManagerLaunchd*>::findGlobalModule();
    }
    ;
};
#endif /* GCRSBASETRACISCENARIOMANAGERLAUNCHD_H_ */
