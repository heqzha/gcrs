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

#ifndef GCRSBASECOMGEOINFO_H_
#define GCRSBASECOMGEOINFO_H_
#include "GCRSBaseComNin.h"
#include "GCRSBaseComVin.h"
#include "Coord.h"

class GCRSBaseComGeoInfo {
public:
    GCRSBaseComGeoInfo();
    virtual ~GCRSBaseComGeoInfo();

    void setName(std::string name){
        this->name = name;
    }

    void setNin(GCRSBaseComNin::NinL3Type nin){
        this->nin = nin;
    }

    void setVinSrc(GCRSBaseComVin::VinL3Type vinSrc){
        this->vinSrc = vinSrc;
    }

    void setVinDest(GCRSBaseComVin::VinL3Type vinDest){
        this->vinDest = vinDest;
    }

    void setLocation(Coord location){
        this->location = location;
    }

    void setSpeed(Coord speed){
        this->speed = speed;
    }

    void setSpeedMax(double speedMax){
        this->speedMax = speedMax;
    }

    void setTTL(simtime_t ttl){
        this->ttl = ttl;
    }

    void setTimestampe(simtime_t timestamp){
        this->timestamp = timestamp;
    }

    std::string getName(){
        return this->name;
    }

    GCRSBaseComNin::NinL3Type getNin(){
        return this->nin;
    }

    GCRSBaseComVin::VinL3Type getVinSrc(){
        return this->vinSrc;
    }

    GCRSBaseComVin::VinL3Type getVinDest(){
        return this->vinDest;
    }

    Coord getLocation(){
        return this->location;
    }

    Coord getSpeed(){
        return this->speed;
    }

    double getSpeedMax(){
        return this->speedMax;
    }

    simtime_t getTTL(){
        return this->ttl;
    }

    simtime_t getTimestamp(){
        return this->timestamp;
    }

protected:
    std::string name;
    GCRSBaseComNin::NinL3Type nin;
    GCRSBaseComVin::VinL3Type vinSrc;
    GCRSBaseComVin::VinL3Type vinDest;
    Coord location;
    Coord speed;
    double speedMax;
    simtime_t ttl;
    simtime_t timestamp;
};

#endif /* GCRSBASECOMGEOINFO_H_ */
