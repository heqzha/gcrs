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

#include "GCRSBaseComCollectNetworkRangeController.h"
#include "GCRSBaseComMath.h"

GCRSBaseComCollectNetworkRangeController::~GCRSBaseComCollectNetworkRangeController() {
    this->cleanUp();
}

void GCRSBaseComCollectNetworkRangeController::addNetworkRange(
        GCRSBaseComNin::NinL3Type nin, Coord loc, double offset,
                    double direct, simtime_t ttl, int landIndex, double roadWidth, Coord locJunction) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange != NULL) {
        return;
    }
    networkRange = new GCRSBaseComCollectNetworkRange(ttl);
    double rotate = 0.0f;
    if (Coord::ZERO != locJunction) {
        rotate = floor(direct/(PI/2.0f)) * (PI/2.0f);
    }else{
        rotate = direct;
    }

    double maxLaneNum = roadWidth / this->laneWidth;
    Coord zorOffset = this->calcZoneOffset(offset,
            this->zorWidth, this->laneWidth, maxLaneNum,landIndex);
    Coord zofOffset = this->calcZoneOffset(offset,
            this->zofWidth, this->laneWidth, maxLaneNum,landIndex);
    Coord zorLoc =GCRSBaseComMath::tranCoordLocaltoWorld(zorOffset, loc, rotate);
    Coord zofLoc =GCRSBaseComMath::tranCoordLocaltoWorld(zofOffset, loc, rotate);
    networkRange->setZof(this->zofShape, zofLoc, rotate,
            this->zofLength, this->zofWidth);
    networkRange->setZor(this->zorShape, zorLoc, rotate,
            this->zorLength, this->zorWidth);

    this->mapNetworkRange.insert(
            std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetworkRange*>::value_type(
                    nin, networkRange));
}

void GCRSBaseComCollectNetworkRangeController::checkPassThroughNode(
        GCRSBaseComVin::VinL3Type vin, Coord loc) {
    if (vin == GCRSBaseComVin::VINL3NULL
            || vin == GCRSBaseComVin::VINL3BROADCAST) {
        return;
    }
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetworkRange*>::iterator iter;
    for (iter = this->mapNetworkRange.begin();
            iter != this->mapNetworkRange.end(); ++iter) {
        GCRSBaseComCollectNetworkRange* networkRange = (*iter).second;
        if (networkRange != NULL) {
            if (networkRange->isExpire()){
                networkRange->hideAnnotation();
                continue;
            }
            if (networkRange->isInZOF(loc)) {
                if (networkRange->searchPassThroughZofNodes(vin)
                        == GCRSBaseComVin::VINL3NULL) {
                    networkRange->addPassThroughZofNode(vin);
                }
                if (networkRange->isInZOR(loc)) {
                    if (networkRange->searchPassThroughZorNodes(vin)
                            == GCRSBaseComVin::VINL3NULL) {
                        networkRange->addPassThroughZorNode(vin);
                    }
                }
            }
        }
    }
}

void GCRSBaseComCollectNetworkRangeController::updateTTL(GCRSBaseComNin::NinL3Type nin, simtime_t ttl){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return;
    networkRange->setTTL(ttl);
    networkRange->setUpdateTime(simTime());
}

Coord GCRSBaseComCollectNetworkRangeController::getLocationZor(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return Coord::ZERO;
    return networkRange->getLocationZor();
}

Coord GCRSBaseComCollectNetworkRangeController::getLocationZof(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return Coord::ZERO;
    return networkRange->getLocationZof();
}

int GCRSBaseComCollectNetworkRangeController::getShapeZor(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return -1;
    return networkRange->getShapeZor();
}

int GCRSBaseComCollectNetworkRangeController::getShapeZof(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return -1;
    return networkRange->getShapeZof();
}

double GCRSBaseComCollectNetworkRangeController::getLengthZor(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return 0.0f;
    return networkRange->getLengthZor();
}

double GCRSBaseComCollectNetworkRangeController::getLengthZof(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return 0.0f;
    return networkRange->getLengthZof();
}

double GCRSBaseComCollectNetworkRangeController::getWidthZor(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return 0.0f;
    return networkRange->getWidthZor();
}

double GCRSBaseComCollectNetworkRangeController::getWidthZof(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return 0.0f;
    return networkRange->getWidthZof();
}

double GCRSBaseComCollectNetworkRangeController::getDirectionZor(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return 0.0f;
    return networkRange->getDirectionZor();
}

double GCRSBaseComCollectNetworkRangeController::getDirectionZof(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL)
        return 0.0f;
    return networkRange->getDirrectionZof();
}

bool GCRSBaseComCollectNetworkRangeController::isInZorRange(
        GCRSBaseComNin::NinL3Type nin, Coord loc) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL) {
        return false;
    }
    return networkRange->isInZOR(loc);
}

bool GCRSBaseComCollectNetworkRangeController::isInZofRange(
        GCRSBaseComNin::NinL3Type nin, Coord loc) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL) {
        return false;
    }
    return networkRange->isInZOF(loc);
}

int GCRSBaseComCollectNetworkRangeController::getNumPassThroughZorNodes(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL) {
        return 0;
    }
    return networkRange->getNumPassThroughZorNodes();
}

int GCRSBaseComCollectNetworkRangeController::getNumPassThroughZofNodes(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetworkRange* networkRange = this->getNetworkRange(nin);
    if (networkRange == NULL) {
        return 0;
    }
    return networkRange->getNumPassThroughZofNodes();
}

GCRSBaseComCollectNetworkRange* GCRSBaseComCollectNetworkRangeController::getNetworkRange(
        GCRSBaseComNin::NinL3Type nin) {
    if (this->mapNetworkRange.empty()) {
        return NULL;
    }
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetworkRange*>::iterator iter;
    iter = this->mapNetworkRange.find(nin);
    if (iter == this->mapNetworkRange.end()) {
        return NULL;
    }

    return (*iter).second;
}

Coord GCRSBaseComCollectNetworkRangeController::calcZoneOffset(
        double horizontalOffset, double zoneWidth, double maxLandNum, double landWith,
        int laneIndex) {
    if (landWith <= 0.0)
        return Coord::ZERO;
    double dLaneIndex = static_cast<double>(laneIndex);
    double coveredLane = (zoneWidth / landWith);
    if(coveredLane > maxLandNum){
        coveredLane = maxLandNum;
    }
    double laneCenter = coveredLane / 2.0f - (dLaneIndex + 0.5);
    double verticalOffset = (-laneCenter) * landWith;
    return Coord(horizontalOffset, verticalOffset, 0.0f);
}

void GCRSBaseComCollectNetworkRangeController::cleanUp() {
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetworkRange*>::iterator iter;
    for (iter = this->mapNetworkRange.begin();
            iter != this->mapNetworkRange.end();) {
        if ((*iter).second != NULL) {
            delete (*iter).second;
        }
        this->mapNetworkRange.erase(iter++);
    }
}
