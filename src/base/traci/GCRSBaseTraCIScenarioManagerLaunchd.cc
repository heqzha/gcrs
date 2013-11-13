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
#include "mobility/traci/TraCIConstants.h"
#include "GCRSBaseString.h"
#include "Convert.h"

Define_Module(GCRSBaseTraCIScenarioManagerLaunchd)
;

void GCRSBaseTraCIScenarioManagerLaunchd::initialize(int stage) {
    TraCIScenarioManagerLaunchd::initialize(stage);
    if (stage == 0) {
        this->numJunctions = 0;

        this->xmlRoutes = par("XML_ROUTES");
        this->xmlNetwork = par("XML_NETWORK");

        this->xmlRoutesReader = new GCRSReadXml("routes", this->xmlRoutes);
        this->xmlNetworkReader = new GCRSReadXml("net", this->xmlNetwork);

        this->vecVehicleTypeIds =
                this->xmlRoutesReader->readAllVehilceTypeIds();
        this->vecRouteIds = this->xmlRoutesReader->readAllRouteIds();

        this->vehicleIdIndex = 0;
        this->vehicleTypeIdsIndex = 0;
        this->routeIdsIndex = 0;
        this->laneIdsIndex = 0;

        this->numVehicleWaitingToAdd = 0;
        double minimalWarmupTime = ceil(firstStepAt.dbl());
        this->warnUpTime = (int) par("WARN_UP_TIME").doubleValue();
        if(this->warnUpTime < minimalWarmupTime){
            this->warnUpTime =  simulation.getWarmupPeriod().dbl();
            if(this->warnUpTime < minimalWarmupTime){
                this->warnUpTime = minimalWarmupTime;
            }
        }

        this->selfMsg = new cMessage("Add Vehicle", MC_ADD_VEHICLE);
        scheduleAt(simTime() + this->warnUpTime, this->selfMsg);
    }
}

void GCRSBaseTraCIScenarioManagerLaunchd::finish() {
    if (this->selfMsg->isScheduled()) {
        cancelAndDelete(this->selfMsg);
    } else {
        delete (this->selfMsg);
    }
    TraCIScenarioManagerLaunchd::finish();
}

Coord GCRSBaseTraCIScenarioManagerLaunchd::calcPlayGround() {
    Coord playground = Coord::ZERO;
    std::list<std::string> junctions = this->commandGetJunctionIds();
    std::list<std::string>::iterator iter;
    double maxX = 0.0f;
    double maxY = 0.0f;
    int numJunction = 0;
    for (iter = junctions.begin(); iter != junctions.end(); ++iter) {
        if (!this->isLane(*iter)) {
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

double GCRSBaseTraCIScenarioManagerLaunchd::calcRoadLength(Coord playground) {
    return sqrt((playground.x * playground.y) / (this->numJunctions - 1));
}

bool GCRSBaseTraCIScenarioManagerLaunchd::isLane(std::string name) {
    std::list<std::string> lanes = this->commandGetLaneIds();
    std::list<std::string>::iterator iter;
    for (iter = lanes.begin(); iter != lanes.end(); ++iter) {
        if (name.compare((*iter)) == 0) {
            return true;
        }
    }
    return false;
}

int GCRSBaseTraCIScenarioManagerLaunchd::getNumPolygonsInEachBlock() {
    int numPolygons = this->commandGetPolygonIds().size();
    int N = this->calcNumCrossRoads(this->numJunctions);
    return numPolygons / ((N + 1) * (N + 1));
}

std::list<Coord> GCRSBaseTraCIScenarioManagerLaunchd::getCrossRoads() {
    std::list<Coord> listCrossRoads;
    Coord playground = this->calcPlayGround();
    Coord centerPlayground = Coord(playground.x / 2.0f, playground.y / 2.0f,
            playground.z / 2.0f);
    double roadLength = this->calcRoadLength(playground);
    std::list<std::string> listJunctionId = this->commandGetJunctionIds();
    std::list<std::string>::iterator iter;
    for (iter = listJunctionId.begin(); iter != listJunctionId.end(); ++iter) {
        if (this->isLane(*iter))
            continue;
        Coord junction = this->commandGetJunctionPosition((*iter));
        Coord local = GCRSBaseComMath::tranCoordWorldtoLocal(junction,
                centerPlayground, 0.0f);
        if (GCRSBaseComMath::isInRectangleRange(local,
                playground.x - (roadLength / 2.0f),
                playground.y - (roadLength / 2.0f))) {
            listCrossRoads.push_back(junction);
        }
    }
    return listCrossRoads;
}

Coord GCRSBaseTraCIScenarioManagerLaunchd::getNearbyCrossRoadLocation(Coord loc,
        double roadWidth) {
    std::list<std::string> listJunctionId = this->commandGetJunctionIds();
    std::list<std::string>::iterator iter;
    for (iter = listJunctionId.begin(); iter != listJunctionId.end(); ++iter) {
        Coord junction = this->commandGetJunctionPosition((*iter));
        if (this->isInJunction(loc, junction, roadWidth)) {
            return junction;
        }
    }
    return Coord::ZERO;
}

bool GCRSBaseTraCIScenarioManagerLaunchd::addNewVehicle() {
    std::string vehicleId = "veh_rt_"
            + Convert::LongToString(this->vehicleIdIndex);
    std::string vehicleTypeId = this->getVehicleTypeId();

    std::string routeId = this->getRouteId();
    std::string edgeId = this->getEdgeId(routeId);
    std::string laneId = this->getLaneId(edgeId);

    double emitPosition = 0.0f;
    double emitSpeed = this->commandGetLaneMaxSpeed(laneId);
    if(this->commandAddVehicle(vehicleId, vehicleTypeId, routeId, laneId,
            emitPosition, emitSpeed)){
        this->vehicleIdIndex++;
        return true;
    }
    return false;
}

void GCRSBaseTraCIScenarioManagerLaunchd::aVehicleWaitingToAdd() {
    this->numVehicleWaitingToAdd++;
}

std::string GCRSBaseTraCIScenarioManagerLaunchd::getVehicleTypeId() {
    if (this->vecVehicleTypeIds.empty())
        return "";
    this->vehicleTypeIdsIndex = this->vehicleTypeIdsIndex
            % this->vecVehicleTypeIds.size();
    return this->vecVehicleTypeIds[this->vehicleTypeIdsIndex++];
}

std::string GCRSBaseTraCIScenarioManagerLaunchd::getRouteId() {
    if (this->vecRouteIds.empty())
        return "";
    this->routeIdsIndex = this->routeIdsIndex % this->vecRouteIds.size();
    return this->vecRouteIds[this->routeIdsIndex++];
}

std::string GCRSBaseTraCIScenarioManagerLaunchd::getEdgeId(std::string route) {
    std::vector<std::string> edges = this->xmlRoutesReader->readEdgeIdsOfRoute(
            route);
    if (edges.empty())
        return "";
    return edges[0];
}

std::string GCRSBaseTraCIScenarioManagerLaunchd::getLaneId(std::string edge) {
    std::vector<std::string> landIds =
            this->xmlNetworkReader->readLaneIdsOfEdge(edge);
    if (landIds.empty())
        return "";
    this->laneIdsIndex = this->laneIdsIndex % landIds.size();
    return landIds[this->laneIdsIndex++];
}

void GCRSBaseTraCIScenarioManagerLaunchd::handleMessage(cMessage *msg) {
    switch (msg->getKind()) {
    case MC_ADD_VEHICLE:{
        int cancelAdding = this->numVehicleWaitingToAdd;
        while(this->numVehicleWaitingToAdd > 0){
            if (this->addNewVehicle()) {
                this->numVehicleWaitingToAdd--;
            }
            if(cancelAdding > 0){
                cancelAdding--;
            }else{
                break;
            }
        }
        scheduleAt(simTime() + this->warnUpTime, msg);
        break;
    }
    default:{
        TraCIScenarioManagerLaunchd::handleMessage(msg);
        break;
    }
    }
}

bool GCRSBaseTraCIScenarioManagerLaunchd::isInJunction(Coord loc,
        Coord locJunction, double roadWidth) {
    Coord local = GCRSBaseComMath::tranCoordWorldtoLocal(loc, locJunction,
            0.0f);
    return GCRSBaseComMath::isInRectangleRange(local, roadWidth, roadWidth);
}

int GCRSBaseTraCIScenarioManagerLaunchd::calcNumCrossRoads(int j) {
    double dJ = static_cast<double>(j);
    double result = (-4.0f + sqrt(4.0f * 4.0f + 4.0 * dJ)) / 2.0f;
    return static_cast<int>(result);
}

