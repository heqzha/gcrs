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

#ifndef GCRSBASECOMELLIPSE_H_
#define GCRSBASECOMELLIPSE_H_

#include "GCRSBaseComBaseShape.h"

class GCRSBaseComEllipse: public GCRSBaseComBaseShape {
public:
    GCRSBaseComEllipse();
    GCRSBaseComEllipse(Coord loc, double rot, double lAxis, double sAxis);
    virtual ~GCRSBaseComEllipse();
    virtual bool isInRange(Coord loc);
    double getLongAxis(){
        return this->longAxis;
    }
    double getShortAxis(){
        return this->shortAxis;
    }
    virtual std::list<Coord> getVertexes();
public:
    double longAxis;
    double shortAxis;
};

#endif /* GCRSBASECOMELLIPSE_H_ */
