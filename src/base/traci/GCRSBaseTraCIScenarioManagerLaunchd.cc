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

#include "GCRSBaseTraCIScenarioManagerLaunchd.h"
#include "GCRSBaseComMath.h"

Define_Module(GCRSBaseTraCIScenarioManagerLaunchd)
;

void GCRSBaseTraCIScenarioManagerLaunchd::initialize(int stage) {
    TraCIScenarioManagerLaunchd::initialize(stage);
    if(stage == 0){
        this->numJunctions = 0;
        //Test Code
        this->xmlRoutes = par("XML_ROUTES");
        this->xmlReader = new GCRSReadXml("routes", this->xmlRoutes);
        std::string edge = this->xmlReader->readAttribute("route", "edges", "rou_1");
        std::list<std::string> ids = this->xmlReader->readAllIdsByTag("route");
        std::list<std::string>::iterator iter;
        for(iter = ids.begin(); iter != ids.end(); ++iter){
            EV<<*iter<<endl;
        }
        EV<<edge<<endl;
        //Test Code
    }
}

void GCRSBaseTraCIScenarioManagerLaunchd::finish() {
    TraCIScenarioManagerLaunchd::finish();
}

Coord GCRSBaseTraCIScenarioManagerLaunchd::calcPlayGround(){
    Coord playground = Coord::ZERO;
    std::list<std::string> junctions =
            this->commandGetJunctionIds();
    std::list<std::string>::iterator iter;
    double maxX = 0.0f;
    double maxY = 0.0f;
    int numJunction = 0;
    for (iter = junctions.begin(); iter != junctions.end(); ++iter) {
        if(!this->isLane(*iter)){
            Coord pos = this->commandGetJunctionPosition((*iter));
            if (pos.x > maxX) {
                maxX = pos.x;
            }
            if (pos.y > maxY) {
                maxY = pos.y;
            }
            numJunction++;
        }
    }
    this->numJunctions = numJunction;
    playground.x = maxX;
    playground.y = maxY;
    return playground;
}

double GCRSBaseTraCIScenarioManagerLaunchd::calcRoadLength(Coord playground){
    return sqrt((playground.x*playground.y)/(this->numJunctions - 1));
}

bool GCRSBaseTraCIScenarioManagerLaunchd::isLane(std::string name){
    std::list<std::string> lanes = this->commandGetLaneIds();
    std::list<std::string>::iterator iter;
    for(iter = lanes.begin(); iter != lanes.end(); ++iter){
        if(name.compare((*iter)) == 0){
            return true;
        }
    }
    return false;
}

int GCRSBaseTraCIScenarioManagerLaunchd::getNumPolygonsInEachBlock(){
    int numPolygons = this->commandGetPolygonIds().size();
    int N = this->calcNumCrossRoads(this->numJunctions);
    return numPolygons/((N+1)*(N+1));
}

std::list<Coord> GCRSBaseTraCIScenarioManagerLaunchd::getCrossRoads(){
    std::list<Coord> listCrossRoads;
    Coord playground = this->calcPlayGround();
    Coord centerPlayground = Coord(playground.x/2.0f, playground.y/2.0f, playground.z/2.0f);
    double roadLength = this->calcRoadLength(playground);
    std::list<std::string> listJunctionId = this->commandGetJunctionIds();
    std::list<std::string>::iterator iter;
    for(iter = listJunctionId.begin(); iter != listJunctionId.end(); ++iter){
        if(this->isLane(*iter))continue;
        Coord junction = this->commandGetJunctionPosition((*iter));
        Coord local = GCRSBaseComMath::tranCoordWorldtoLocal(junction,centerPlayground,0.0f);
        if(GCRSBaseComMath::isInRectangleRange(local,playground.x-(roadLength/2.0f), playground.y-(roadLength/2.0f))){
            listCrossRoads.push_back(junction);
        }
    }
    return listCrossRoads;
}

Coord GCRSBaseTraCIScenarioManagerLaunchd::getNearbyCrossRoadLocation(Coord loc, double roadWidth){
    std::list<std::string> listJunctionId = this->commandGetJunctionIds();
    std::list<std::string>::iterator iter;
    for(iter = listJunctionId.begin(); iter != listJunctionId.end(); ++iter){
        Coord junction = this->commandGetJunctionPosition((*iter));
        if(this->isInJunction(loc,junction,roadWidth)){
            return junction;
        }
    }
    return Coord::ZERO;
}

bool GCRSBaseTraCIScenarioManagerLaunchd::isInJunction(Coord loc, Coord locJunction, double roadWidth){
    Coord local = GCRSBaseComMath::tranCoordWorldtoLocal(loc,
            locJunction, 0.0f);
    return GCRSBaseComMath::isInRectangleRange(local, roadWidth, roadWidth);
}

int GCRSBaseTraCIScenarioManagerLaunchd::calcNumCrossRoads(int j){
    double dJ = static_cast<double>(j);
    double result = (-4.0f + sqrt(4.0f*4.0f + 4.0*dJ))/2.0f;
    return static_cast<int>(result);
}
