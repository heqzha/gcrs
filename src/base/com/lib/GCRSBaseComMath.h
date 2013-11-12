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

#ifndef GCRSBASECOMMATH_H_
#define GCRSBASECOMMATH_H_
#include "Coord.h"

class GCRSBaseComMath {
public:
    /*
     * Coordinate transformations
     */
    static Coord tranCoordWorldtoLocal(Coord pos, Coord center, double rotate);
    static Coord tranCoordLocaltoWorld(Coord pos, Coord center, double rotate);

    /*
     * Vector calcualtions
     */
    static double calcAngle(Coord a, Coord b);
    static double calcAngleWithDirection(Coord a, Coord b);

    /*
     * Random number
     */
    static double geDoubleRandomNumber(double a, double b, int seed = 0);
    static long geLongRandomNumber(long a, long b, int seed = 0);
    static int geIntRandomNumber(int a, int b, int seed = 0);
    static unsigned geUnsignedRandomNumer(unsigned a, unsigned b, int seed = 0);

    static std::list<int> geRandomIndex(int size, int seed = 0);

    /*
     * Calculate distance between two points
     */
    static double calcDistance(Coord a, Coord b);

    /*
     *
     */
    static double convertToRadian(double degree);
    static double convertToDegree(double radian);
    /*
     *
     */
    static bool isInCircleRange(Coord loc, double radius);
    static bool isInRectangleRange(Coord loc, double length, double width);
    static bool isInEllipseRange(Coord loc, double longAxis, double shortAxis);

    /*
     *
     */
    static std::list<Coord> calcVertexes(double length, double width, int numVertex);

    /*
     *
     */
    static double convertVectorToScalar(Coord a);
};

#endif /* GCRSBASECOMMATH_H_ */
