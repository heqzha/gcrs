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

#include "GCRSBaseComCircle.h"
#include "GCRSBaseComMath.h"

GCRSBaseComCircle::GCRSBaseComCircle():GCRSBaseComBaseShape() {
    this->diameter = 0.0f;
}

GCRSBaseComCircle::GCRSBaseComCircle(Coord loc, double direct, double dia) :
        GCRSBaseComBaseShape(GCRSBaseComBaseShape::CIRCLE, loc, direct), diameter(
                dia) {

}

GCRSBaseComCircle::~GCRSBaseComCircle(){

}

bool GCRSBaseComCircle::isInRange(Coord loc) {
    double radius = this->diameter / 2.0f;
    Coord localCoord = GCRSBaseComMath::tranCoordWorldtoLocal(loc,
            this->location, this->direction);
    return GCRSBaseComMath::isInCircleRange(localCoord, radius);
}

std::list<Coord> GCRSBaseComCircle::getVertexes(){
    std::list<Coord> worldVertexes;
    std::list<Coord> localVertexes = GCRSBaseComMath::calcVertexes(this->diameter,this->diameter,100);
    std::list<Coord>::iterator iter;
    for(iter = localVertexes.begin(); iter != localVertexes.end(); ++iter){
        Coord world = GCRSBaseComMath::tranCoordLocaltoWorld((*iter),this->location, this->direction);
        worldVertexes.push_back(world);
    }
    return worldVertexes;
}
