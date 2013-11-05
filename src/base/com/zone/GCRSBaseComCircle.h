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

#ifndef GCRSBASECOMCIRCLE_H_
#define GCRSBASECOMCIRCLE_H_

#include "GCRSBaseComBaseShape.h"

class GCRSBaseComCircle: public GCRSBaseComBaseShape {
public:
    GCRSBaseComCircle();
    GCRSBaseComCircle(Coord loc, double direct, double dia);
    virtual ~GCRSBaseComCircle();
    virtual bool isInRange(Coord loc);
    double getDiameter(){
        return this->diameter;
    }
    virtual std::list<Coord> getVertexes();
protected:
    double diameter;
};

#endif /* GCRSBASECOMCIRCLE_H_ */
