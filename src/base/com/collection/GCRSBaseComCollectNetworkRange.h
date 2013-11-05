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

#ifndef GCRSBASECOMCOLLECTNETWORKRANGE_H_
#define GCRSBASECOMCOLLECTNETWORKRANGE_H_
#include <vector>
#include "GCRSBaseComZone.h"
#include "Coord.h"
#include "GCRSBaseComVin.h"
#include "AnnotationManager.h"
#include "GCRSBaseComTTL.h"

class GCRSBaseComCollectNetworkRange {
public:
    GCRSBaseComCollectNetworkRange(simtime_t ttl);
    virtual ~GCRSBaseComCollectNetworkRange();

    void setZor(int sc, Coord loc, double direct, double par1, double par2);
    void setZof(int sc, Coord loc, double direct, double par1, double par2);
    bool isInZOR(Coord loc);
    bool isInZOF(Coord loc);
    bool isExpire();
    void hideAnnotation();

    void addPassThroughZorNode(GCRSBaseComVin::VinL3Type vin);
    void addPassThroughZofNode(GCRSBaseComVin::VinL3Type vin);
    int getNumPassThroughZorNodes();
    int getNumPassThroughZofNodes();
    GCRSBaseComVin::VinL3Type searchPassThroughZorNodes(
            GCRSBaseComVin::VinL3Type vin);
    GCRSBaseComVin::VinL3Type searchPassThroughZofNodes(
            GCRSBaseComVin::VinL3Type vin);

    Coord getLocationZor() {
        if (zor == NULL)
            return Coord::ZERO;
        return this->zor->getLocation();
    }

    Coord getLocationZof() {
        if (zof == NULL)
            return Coord::ZERO;
        return this->zof->getLocation();
    }

    int getShapeZor() {
        if (zor == NULL)
            return -1;
        return this->zor->getShape();
    }

    int getShapeZof() {
        if (zof == NULL)
            return -1;
        return this->zof->getShape();
    }
    double getLengthZor() {
        if (zor == NULL)
            return 0.0;
        return this->zor->getLength();
    }
    double getLengthZof() {
        if (zof == NULL)
            return 0.0;
        return this->zof->getLength();
    }
    double getWidthZor() {
        if (zor == NULL)
            return 0.0;
        return this->zor->getWidth();
    }
    double getWidthZof() {
        if (zof == NULL)
            return 0.0;
        return this->zof->getWidth();
    }
    double getDirectionZor() {
        if (zor == NULL)
            return 0.0f;
        return this->zor->getDirection();
    }
    double getDirrectionZof() {
        if (zof == NULL)
            return 0.0f;
        return this->zof->getDirection();
    }
    simtime_t getCreateTime(){
        return this->networkTime.getCreateTime();
    }
    simtime_t getUpdateTime(){
        return this->networkTime.getUpdateTime();
    }
    simtime_t getTTL(){
        return this->networkTime.getTTL();
    }
    simtime_t getExpireTime(){
        return this->networkTime.getExpireTime();
    }
    void setUpdateTime(simtime_t t){
        this->networkTime.setUpdateTime(t);
    }
    void setTTL(simtime_t t){
        this->networkTime.setTTL(t);
    }

protected:
    GCRSBaseComVin::VinL3Type searchPassThroughNodes(
            GCRSBaseComVin::VinL3Type vin,
            std::vector<GCRSBaseComVin::VinL3Type> v);
protected:
    GCRSBaseComZone* zor;
    GCRSBaseComZone* zof;
    AnnotationManager::Group* zorAnnotationGroup;
    AnnotationManager::Group* zofAnnotationGroup;
    std::vector<GCRSBaseComVin::VinL3Type> vecPassThroughZorNodes;
    std::vector<GCRSBaseComVin::VinL3Type> vecPassThroughZofNodes;
    GCRSBaseComTTL networkTime;

    AnnotationManager* annotation;
};

#endif /* GCRSBASECOMCOLLECTNETWORKRANGE_H_ */
