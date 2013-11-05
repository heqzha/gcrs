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

#include "GCRSBaseComGeoInfo.h"

GCRSBaseComGeoInfo::GCRSBaseComGeoInfo() {
    this->name = "";
    this->nin = GCRSBaseComNin::NINL3NULL;
    this->vinSrc = GCRSBaseComVin::VINL3NULL;
    this->vinDest = GCRSBaseComVin::VINL3NULL;
    this->location = Coord::ZERO;
    this->speed = Coord::ZERO;
    this->speedMax = 0.0f;
    this->ttl = 0.0f;
    this->timestamp = 0.0f;
}

GCRSBaseComGeoInfo::~GCRSBaseComGeoInfo() {
    // TODO Auto-generated destructor stub
}

