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

#include "GCRSBaseComCollectNetworkRange.h"

GCRSBaseComCollectNetworkRange::GCRSBaseComCollectNetworkRange(simtime_t ttl){
    this->zor = NULL;
    this->zof = NULL;
    this->networkTime.setCreateTime(simTime());
    this->networkTime.setTTL(ttl);
    this->annotation = AnnotationManagerAccess().getIfExists();
}

GCRSBaseComCollectNetworkRange::~GCRSBaseComCollectNetworkRange() {
    if (this->zor != NULL)
        delete this->zor;
    if(this->zof != NULL)
        delete this->zof;
}

void GCRSBaseComCollectNetworkRange::setZor(int sc, Coord loc, double direct, double par1, double par2){
    this->zor = new GCRSBaseComZone(sc, loc, direct, par1, par2);
    this->zorAnnotationGroup = this->annotation->createGroup("ZOR");
    this->annotation->drawPolygon(this->zor->getVertexes(), "blue", this->zorAnnotationGroup);
    this->annotation->showAll(this->zorAnnotationGroup);
}

void GCRSBaseComCollectNetworkRange::setZof(int sc, Coord loc, double direct, double par1, double par2){
    this->zof = new GCRSBaseComZone(sc, loc, direct, par1, par2);
    this->zofAnnotationGroup = this->annotation->createGroup("ZOF");
    this->annotation->drawPolygon(this->zof->getVertexes(), "brown", this->zofAnnotationGroup);
    this->annotation->showAll(this->zofAnnotationGroup);
}

bool GCRSBaseComCollectNetworkRange::isInZOR(Coord loc) {
    return this->zor->isInZone(loc);
}

bool GCRSBaseComCollectNetworkRange::isInZOF(Coord loc) {
    return this->zof->isInZone(loc);
}

bool GCRSBaseComCollectNetworkRange::isExpire(){
    return this->networkTime.isExpires(simTime());
}

void GCRSBaseComCollectNetworkRange::hideAnnotation(){
    this->annotation->hideAll(this->zorAnnotationGroup);
    this->annotation->hideAll(this->zofAnnotationGroup);
}

void GCRSBaseComCollectNetworkRange::addPassThroughZorNode(
        GCRSBaseComVin::VinL3Type vin) {
    if (GCRSBaseComVin::isVinL3NULL(vin)
            || GCRSBaseComVin::isVinL3Broadcast(vin)) {
        return;
    }
    this->vecPassThroughZorNodes.push_back(vin);
}

void GCRSBaseComCollectNetworkRange::addPassThroughZofNode(
        GCRSBaseComVin::VinL3Type vin) {
    if (GCRSBaseComVin::isVinL3NULL(vin)
            || GCRSBaseComVin::isVinL3Broadcast(vin)) {
        return;
    }
    this->vecPassThroughZofNodes.push_back(vin);
}

int GCRSBaseComCollectNetworkRange::getNumPassThroughZorNodes() {
    return this->vecPassThroughZorNodes.size();
}

int GCRSBaseComCollectNetworkRange::getNumPassThroughZofNodes() {
    return this->vecPassThroughZofNodes.size();
}

GCRSBaseComVin::VinL3Type GCRSBaseComCollectNetworkRange::searchPassThroughZorNodes(
        GCRSBaseComVin::VinL3Type vin) {
    return this->searchPassThroughNodes(vin, this->vecPassThroughZorNodes);
}

GCRSBaseComVin::VinL3Type GCRSBaseComCollectNetworkRange::searchPassThroughZofNodes(
        GCRSBaseComVin::VinL3Type vin) {
    return this->searchPassThroughNodes(vin, this->vecPassThroughZofNodes);
}

GCRSBaseComVin::VinL3Type GCRSBaseComCollectNetworkRange::searchPassThroughNodes(
        GCRSBaseComVin::VinL3Type vin,
        std::vector<GCRSBaseComVin::VinL3Type> v) {
    if (v.empty()) {
        return GCRSBaseComVin::VINL3NULL;
    }
    std::vector<GCRSBaseComVin::VinL3Type>::iterator iter;
    for (iter = v.begin(); iter != v.end(); ++iter) {
        if ((*iter) == vin) {
            return (*iter);
        }
    }
    return GCRSBaseComVin::VINL3NULL;
}
