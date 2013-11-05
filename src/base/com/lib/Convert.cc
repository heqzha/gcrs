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

#include "Convert.h"
#include <sstream>
Convert::Convert() {
    // TODO Auto-generated constructor stub

}

Convert::~Convert() {
    // TODO Auto-generated destructor stub
}

std::string Convert::IntegerToString(int i) {
    double di = static_cast<double>(i);
    return Convert::DoubleToString(di);
}

std::string Convert::LongToString(long l) {
    double dl = static_cast<double>(l);
    return Convert::DoubleToString(dl);
}

std::string Convert::DoubleToString(double d) {
    std::ostringstream strs;
    strs << d;
    return strs.str();
}

std::string Convert::CoordToString(Coord c) {
    std::string strCoord = Convert::DoubleToString(c.x) + ","
            + Convert::DoubleToString(c.y) + "," + Convert::DoubleToString(c.z);
    return strCoord;
}
