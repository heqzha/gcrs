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

#ifndef GCRSBASECOMBASESHAPE_H_
#define GCRSBASECOMBASESHAPE_H_
#include "Coord.h"

class GCRSBaseComBaseShape {
public:
    enum shape_category {
        CIRCLE = 0, RECTANGLE=1, ELLIPSE=2, OTHER=3
    };
    GCRSBaseComBaseShape();
    GCRSBaseComBaseShape(shape_category sc, Coord loc, double direct);

    shape_category getShape(){
        return this->sc;
    }
    virtual Coord getLocation(){
        return this->location;
    }
    virtual double getDirection(){
        return this->direction;
    }

    virtual bool isInRange(Coord loc) = 0;
    virtual std::list<Coord> getVertexes() = 0;
protected:
    //@brief Shape type from shape_category
    shape_category sc;
    //@brief Location of shape
    Coord location;
    //@brief direction of shape
    double direction;
};

#endif /* GCRSBASECOMBASESHAPE_H_ */
