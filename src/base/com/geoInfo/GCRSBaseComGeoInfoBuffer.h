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

#ifndef GCRSBASECOMGEOINFOBUFFER_H_
#define GCRSBASECOMGEOINFOBUFFER_H_
#include <deque>
#include "GCRSBaseComGeoInfo.h"

class GCRSBaseComGeoInfoBuffer {
public:
    GCRSBaseComGeoInfoBuffer();
    GCRSBaseComGeoInfoBuffer(unsigned int maxBufferSize);
    virtual ~GCRSBaseComGeoInfoBuffer();

    virtual void addGeoInfo(std::string name, GCRSBaseComNin::NinL3Type nin,
            GCRSBaseComVin::VinL3Type vinSrc, GCRSBaseComVin::VinL3Type vinDest,
            Coord location, Coord speed, double speedMax, simtime_t ttl,
            simtime_t timestamp);
    virtual bool isExisted(GCRSBaseComVin::VinL3Type vinSrc,
            simtime_t timestamp);
    virtual void checkTTL();
    virtual unsigned int getBufferSize(){
        return this->geoInfoBuffer.size();
    }

protected:
    virtual GCRSBaseComGeoInfo* searchGeoInfo(GCRSBaseComVin::VinL3Type vinSrc,
            simtime_t timestamp);
    virtual void cleanUp();

protected:
    class CleanUp {
    public:
        bool operator()(GCRSBaseComGeoInfo* geoInfo) const {
            if (geoInfo == NULL)
                return true;
            delete geoInfo;
            return true;
        }
    };
    class RemoveGeoInfo {
    public:
        bool operator()(GCRSBaseComGeoInfo* geoInfo) const {
            if (geoInfo == NULL)
                return true;
            if (simTime() >= geoInfo->getTTL() + geoInfo->getTimestamp()) {
                delete geoInfo;
                return true;
            }
            return false;
        }
    };
    class SearchGeoInfo {
    public:
        SearchGeoInfo(GCRSBaseComVin::VinL3Type vinSrc, simtime_t timestamp) :
                vinSrc(vinSrc), timestamp(timestamp) {
        }
        ;
        bool operator()(GCRSBaseComGeoInfo* info) const {
            if (info == NULL) {
                return false;
            }
            if (GCRSBaseComVin::isVinL3NULL(vinSrc)) {
                if (vinSrc == info->getVinSrc()
                        && timestamp == info->getTimestamp()) {
                    return true;
                }
            }
            return false;
        }
    private:
        GCRSBaseComVin::VinL3Type vinSrc;
        simtime_t timestamp;
    };

protected:
    std::deque<GCRSBaseComGeoInfo*> geoInfoBuffer;
    unsigned int maxBufferSize;
};

#endif /* GCRSBASECOMGEOINFOBUFFER_H_ */
