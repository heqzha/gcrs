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

#include "GCRSBaseComZone.h"
#include "GCRSBaseConst.h"

GCRSBaseComZone::GCRSBaseComZone() {
    this->base = NULL;
}

GCRSBaseComZone::GCRSBaseComZone(int sc, Coord loc, double direct, double par1,
        double par2) {
    switch (sc) {
    case GCRSBaseComBaseShape::CIRCLE:
        this->base = new GCRSBaseComCircle(loc, direct, par1);
        break;
    case GCRSBaseComBaseShape::RECTANGLE:
        this->base = new GCRSBaseComRectangle(loc, direct, par1, par2);
        break;
    case GCRSBaseComBaseShape::ELLIPSE:
        this->base = new GCRSBaseComEllipse(loc, direct, par1, par2);
        break;
    default:
        GCRSBaseComZone();
        break;
    }
}

GCRSBaseComZone::~GCRSBaseComZone() {
    if(this->base == NULL)return;
    switch(this->base->getShape()){
    case GCRSBaseComBaseShape::CIRCLE:{
        GCRSBaseComCircle* circle = dynamic_cast<GCRSBaseComCircle*>(this->base);
        delete circle;
        break;
    }
    case GCRSBaseComBaseShape::RECTANGLE:{
        GCRSBaseComRectangle* rectangle = dynamic_cast<GCRSBaseComRectangle*>(this->base);
        delete rectangle;
        break;
    }
    case GCRSBaseComBaseShape::ELLIPSE:{
        GCRSBaseComEllipse* ellipse = dynamic_cast<GCRSBaseComEllipse*>(this->base);
        delete ellipse;
        break;
    }
    default:
        break;
    }
    this->base = NULL;
}

bool GCRSBaseComZone::isInZone(Coord loc) {
    if(this->base == NULL)return false;
    switch (this->base->getShape()) {
    case GCRSBaseComBaseShape::CIRCLE:{
        GCRSBaseComCircle* circle = dynamic_cast<GCRSBaseComCircle*>(this->base);
        return circle->isInRange(loc);
    }
    case GCRSBaseComBaseShape::RECTANGLE:{
        GCRSBaseComRectangle* rectangle = dynamic_cast<GCRSBaseComRectangle*>(this->base);
        return rectangle->isInRange(loc);
    }
    case GCRSBaseComBaseShape::ELLIPSE:{
        GCRSBaseComEllipse* ellipse = dynamic_cast<GCRSBaseComEllipse*>(this->base);
        return ellipse->isInRange(loc);
    }
    default:{
        return false;
    }
    }
}

double GCRSBaseComZone::getLength(){
    if(this->base == NULL)return 0.0f;
    switch (this->base->getShape()) {
    case GCRSBaseComBaseShape::CIRCLE:{
        GCRSBaseComCircle* circle = dynamic_cast<GCRSBaseComCircle*>(this->base);
        return circle->getDiameter();
    }
    case GCRSBaseComBaseShape::RECTANGLE:{
        GCRSBaseComRectangle* rectangle = dynamic_cast<GCRSBaseComRectangle*>(this->base);
        return rectangle->getLength();
    }
    case GCRSBaseComBaseShape::ELLIPSE:{
        GCRSBaseComEllipse* ellipse = dynamic_cast<GCRSBaseComEllipse*>(this->base);
        return ellipse->getLongAxis();
    }
    default:{
        return 0.0f;
    }
    }
}

double GCRSBaseComZone::getWidth(){
    if(this->base == NULL)return 0.0f;
    switch (this->base->getShape()) {
    case GCRSBaseComBaseShape::CIRCLE:{
        GCRSBaseComCircle* circle = dynamic_cast<GCRSBaseComCircle*>(this->base);
        return circle->getDiameter();
    }
    case GCRSBaseComBaseShape::RECTANGLE:{
        GCRSBaseComRectangle* rectangle = dynamic_cast<GCRSBaseComRectangle*>(this->base);
        return rectangle->getWidth();
    }
    case GCRSBaseComBaseShape::ELLIPSE:{
        GCRSBaseComEllipse* ellipse = dynamic_cast<GCRSBaseComEllipse*>(this->base);
        return ellipse->getShortAxis();
    }
    default:{
        return 0.0f;
    }
    }
}

std::list<Coord> GCRSBaseComZone::getVertexes(){
    std::list<Coord> list;
    if(this->base == NULL)return list;
    switch (this->base->getShape()) {
    case GCRSBaseComBaseShape::CIRCLE:{
        GCRSBaseComCircle* circle = dynamic_cast<GCRSBaseComCircle*>(this->base);
        list = circle->getVertexes();
        break;
    }
    case GCRSBaseComBaseShape::RECTANGLE:{
        GCRSBaseComRectangle* rectangle = dynamic_cast<GCRSBaseComRectangle*>(this->base);
        list = rectangle->getVertexes();
        break;
    }
    case GCRSBaseComBaseShape::ELLIPSE:{
        GCRSBaseComEllipse* ellipse = dynamic_cast<GCRSBaseComEllipse*>(this->base);
        list = ellipse->getVertexes();
        break;
    }
    default:{
        break;
    }
    }
    return list;
}
