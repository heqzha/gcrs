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

#include "GCRSBaseComGeoInfoBuffer.h"
#include <algorithm>//std::remove_if std::find_if std::sort
GCRSBaseComGeoInfoBuffer::GCRSBaseComGeoInfoBuffer() {
    this->maxBufferSize = 0;
}

GCRSBaseComGeoInfoBuffer::GCRSBaseComGeoInfoBuffer(unsigned int maxBufferSize) {
    this->maxBufferSize = maxBufferSize;
}

GCRSBaseComGeoInfoBuffer::~GCRSBaseComGeoInfoBuffer() {
    this->cleanUp();
}

void GCRSBaseComGeoInfoBuffer::addGeoInfo(std::string name,
        GCRSBaseComNin::NinL3Type nin, GCRSBaseComVin::VinL3Type vinSrc,
        GCRSBaseComVin::VinL3Type vinDest, Coord location, Coord speed,
        double speedMax, simtime_t ttl, simtime_t timestamp) {
    if (this->maxBufferSize > 0
            && this->geoInfoBuffer.size() >= this->maxBufferSize) {
        return;
    }
    GCRSBaseComGeoInfo* geoInfo = new GCRSBaseComGeoInfo();
    geoInfo->setName(name);
    geoInfo->setNin(nin);
    geoInfo->setVinSrc(vinSrc);
    geoInfo->setVinDest(vinDest);
    geoInfo->setLocation(location);
    geoInfo->setSpeed(speed);
    geoInfo->setSpeedMax(speedMax);
    geoInfo->setTTL(ttl);
    geoInfo->setTimestampe(timestamp);
    this->geoInfoBuffer.push_back(geoInfo);
}

bool GCRSBaseComGeoInfoBuffer::isExisted(GCRSBaseComVin::VinL3Type vinSrc,
        simtime_t timestamp) {
    GCRSBaseComGeoInfo* geoInfo = this->searchGeoInfo(vinSrc, timestamp);
    if (geoInfo == NULL)
        return false;
    return true;
}

void GCRSBaseComGeoInfoBuffer::checkTTL() {
    this->geoInfoBuffer.erase(
            std::remove_if(this->geoInfoBuffer.begin(),
                    this->geoInfoBuffer.end(), RemoveGeoInfo()),
            this->geoInfoBuffer.end());
}

GCRSBaseComGeoInfo* GCRSBaseComGeoInfoBuffer::searchGeoInfo(
        GCRSBaseComVin::VinL3Type vinSrc, simtime_t timestamp) {
    if (this->geoInfoBuffer.empty())
        return NULL;
    std::deque<GCRSBaseComGeoInfo*>::iterator iter;
    iter = std::find_if(this->geoInfoBuffer.begin(), this->geoInfoBuffer.end(),
            SearchGeoInfo(vinSrc, timestamp));
    if (iter == this->geoInfoBuffer.end()) {
        return NULL;
    }
    return (*iter);
}

void GCRSBaseComGeoInfoBuffer::cleanUp(){
    this->geoInfoBuffer.erase(
            std::remove_if(this->geoInfoBuffer.begin(),
                    this->geoInfoBuffer.end(), CleanUp()),
            this->geoInfoBuffer.end());
}
