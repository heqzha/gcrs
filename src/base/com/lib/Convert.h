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

#ifndef CONVERT_H_
#define CONVERT_H_
#include <string>
#include "Coord.h"

class Convert {
public:
    Convert();
    virtual ~Convert();

    static std::string IntegerToString(int i);
    static std::string LongToString(long l);
    static std::string DoubleToString(double d);
    static std::string CoordToString(Coord c);

    static double StringToDouble(std::string s);
};

#endif /* CONVERT_H_ */
