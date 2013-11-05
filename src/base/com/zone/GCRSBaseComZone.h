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

#ifndef GCRSBASECOMZONE_H_
#define GCRSBASECOMZONE_H_
#include "GCRSBaseComCircle.h"
#include "GCRSBaseComRectangle.h"
#include "GCRSBaseComEllipse.h"

class GCRSBaseComZone {
public:
    GCRSBaseComZone();
    GCRSBaseComZone(int sc, Coord loc, double direct, double par1, double par2);
    virtual ~GCRSBaseComZone();
    bool isInZone(Coord loc);
    Coord getLocation(){
        if(base == NULL)return Coord::ZERO;
        return this->base->getLocation();
    }
    double getDirection(){
        if(base == NULL)return 0.0f;
        return this->base->getDirection();
    }
    int getShape(){
        if(base == NULL)return -1;
        return this->base->getShape();
    }
    double getLength();
    double getWidth();
    std::list<Coord> getVertexes();
public:
    GCRSBaseComBaseShape* base;
};

#endif /* GCRSBASECOMZONE_H_ */
