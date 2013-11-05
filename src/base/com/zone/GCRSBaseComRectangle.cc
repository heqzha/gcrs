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

#include "GCRSBaseComRectangle.h"
#include "GCRSBaseComMath.h"

GCRSBaseComRectangle::GCRSBaseComRectangle() :
        GCRSBaseComBaseShape() {
    this->length = 0.0f;
    this->width = 0.0f;
}

GCRSBaseComRectangle::GCRSBaseComRectangle(Coord loc, double rot, double l,
        double w) :
        GCRSBaseComBaseShape(GCRSBaseComBaseShape::RECTANGLE, loc, rot), length(
                l), width(w) {

}

GCRSBaseComRectangle::~GCRSBaseComRectangle(){

}

bool GCRSBaseComRectangle::isInRange(Coord loc) {
    Coord localCoord = GCRSBaseComMath::tranCoordWorldtoLocal(loc,
            this->location, this->direction);
    return GCRSBaseComMath::isInRectangleRange(localCoord,this->length,this->width);
}

std::list<Coord> GCRSBaseComRectangle::getVertexes(){
    std::list<Coord> worldVertexes;
    std::list<Coord> localVertexes = GCRSBaseComMath::calcVertexes(this->length,this->width,4);
    std::list<Coord>::iterator iter;
    for(iter = localVertexes.begin(); iter != localVertexes.end(); ++iter){
        Coord world = GCRSBaseComMath::tranCoordLocaltoWorld((*iter),this->location, this->direction);
        worldVertexes.push_back(world);
    }
    return worldVertexes;
}
