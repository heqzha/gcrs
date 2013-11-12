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

#include "GCRSBaseComMath.h"
#define VPA(x)  (roundf(x*1000.0f)/1000.0f)

Coord GCRSBaseComMath::tranCoordWorldtoLocal(Coord pos, Coord center,
        double rotate) {
    double localX, localY, localZ;
    localX = (pos.x - center.x) * cos(rotate)
            + (pos.y - center.y) * sin(rotate);
    localY = (pos.y - center.y) * cos(rotate)
            - (pos.x - center.x) * sin(rotate);
    localZ = 0.0f;
    return Coord(localX, localY, localZ);
}

Coord GCRSBaseComMath::tranCoordLocaltoWorld(Coord pos, Coord center,
        double rotate) {
    double worldX, worldY, worldZ;
    worldX = (pos.x) * cos(rotate) - (pos.y) * sin(rotate) + center.x;
    worldY = (pos.x) * sin(rotate) + (pos.y) * cos(rotate) + center.y;
    worldZ = 0.0f;
    return Coord(worldX, worldY, worldZ);
}

double GCRSBaseComMath::calcAngle(Coord a, Coord b) {
    double ab = a.x * b.x + a.y * b.y + a.z * b.z;
    double norm_a = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    double norm_b = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
    return acos(ab / (norm_a * norm_b));
}

double GCRSBaseComMath::calcAngleWithDirection(Coord a, Coord b){
    double thetaA, thetaB;
    double cosThetaA = a.x / sqrt(a.x * a.x + a.y * a.y);
    double sinThetaA = a.y / sqrt(a.x * a.x + a.y * a.y);
    double cosThetaB = b.x / sqrt(b.x * b.x + b.y * b.y);
    double sinThetaB = b.y / sqrt(b.x * b.x + b.y * b.y);
    thetaA = atan2(sinThetaA,cosThetaA);
    thetaB = atan2(sinThetaB,cosThetaB);
    if((thetaB < 0.0f)&&(thetaA > 0.0f)&&(thetaB < (-PI/2.0f))){
        return 2.0f*PI-(thetaA - thetaB);
    }else if((thetaB > 0.0f)&&(thetaA < 0.0f)&&(thetaA < (-PI/2.0f))){
        return -(2.0f*PI-(thetaB - thetaA));
    }else if((thetaB < 0.0f)&&(thetaA > 0.0f)&&(thetaB > (-PI/2.0f))){
        return -(thetaA - thetaB);
    }else if((thetaB > 0.0f)&&(thetaA < 0.0f)&&(thetaA > (-PI/2.0f))){
        return thetaB - thetaA;
    }else{
        return thetaB - thetaA;
    }
}

double GCRSBaseComMath::geDoubleRandomNumber(double a, double b, int seed) {
    //int rng = static_cast<int>(floor(simTime().dbl()));
    return uniform(a, b, seed);
}

long GCRSBaseComMath::geLongRandomNumber(long a, long b, int seed) {
    double da = static_cast<double>(a);
    double db = static_cast<double>(b);
    return static_cast<long>(floor(geDoubleRandomNumber(da, db, seed)));
}

int GCRSBaseComMath::geIntRandomNumber(int a, int b, int seed) {
    double da = static_cast<double>(a);
    double db = static_cast<double>(b);
    return static_cast<int>(floor(geDoubleRandomNumber(da, db, seed)));
}

unsigned GCRSBaseComMath::geUnsignedRandomNumer(unsigned a, unsigned b, int seed){
    double da = static_cast<double>(a);
    double db = static_cast<double>(b);
    return static_cast<unsigned>(floor(geDoubleRandomNumber(da, db, seed)));
}

std::list<int> GCRSBaseComMath::geRandomIndex(int size, int seed){
    std::list<int> listIndex;
    for(int i = 0; i < size; i++){
        listIndex.push_back(GCRSBaseComMath::geIntRandomNumber(0, size, seed));
    }
    return listIndex;
}

double GCRSBaseComMath::calcDistance(Coord a, Coord b) {
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0) + pow(a.z - b.z, 2.0));
}

double GCRSBaseComMath::convertToRadian(double degree) {
    return (degree / 180.0) * PI;
}

double GCRSBaseComMath::convertToDegree(double radian) {
    return (radian / PI) * 180;
}

bool GCRSBaseComMath::isInCircleRange(Coord loc, double radius) {
    double result = loc.x * loc.x + loc.y * loc.y - radius * radius;
    if (result <= 0)
        return true;
    return false;
}

bool GCRSBaseComMath::isInRectangleRange(Coord loc, double length,
        double width) {
    double left = -length / 2.0;
    double right = length / 2.0;
    double top =  width/ 2.0;
    double bottom = -width / 2.0;
    if (loc.x <= right && loc.x >= left) {
        if (loc.y <= top && loc.y >= bottom) {
            return true;
        }
    }
    return false;
}

bool GCRSBaseComMath::isInEllipseRange(Coord loc, double longAxis,
        double shortAxis) {
    double result = (loc.x * loc.x) / (longAxis * longAxis)
            + (loc.y * loc.y) / (shortAxis * shortAxis) - 1;
    if (result <= 0)
        return true;
    return false;
}

std::list<Coord> GCRSBaseComMath::calcVertexes(double length, double width, int numVertex){
    Coord center = Coord::ZERO;
    std::list<Coord> listV;
    double radius = 0.0f;
    std::list<double> listTheta;

    if(length != width){
        double theta = atan(width/length);
        listTheta.push_back(theta);
        listTheta.push_back(PI - theta);
        listTheta.push_back(PI + theta);
        listTheta.push_back(2 * PI - theta);
        radius = sqrt((length/2.0f)*(length/2.0f) + (width/2.0f)*(width/2.0f));
    }else{
        double dNumVertex = static_cast<double>(numVertex);
        for(int i = 0; i < numVertex*2; ++i){
            if(i%2 != 0){
                double di = static_cast<double>(i);
                listTheta.push_back((di/dNumVertex)*PI);
            }
        }
        radius = length / 2.0f;
    }
    std::list<double>::iterator iter;
    for(iter = listTheta.begin(); iter != listTheta.end(); ++iter){
        double x = center.x + radius * cos((*iter));
        double y = center.y + radius * sin((*iter));
        listV.push_back(Coord(x,y,0.0f));
    }
    return listV;
}

double GCRSBaseComMath::convertVectorToScalar(Coord a){
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
