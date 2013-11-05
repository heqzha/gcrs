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

#include "GCRSBaseComCollectStatistics.h"
#include <math.h>

double GCRSBaseComCollectStatistics::calcPDR(int nr, int nsr) {
    if(nsr == 0) return 0.0f;
    double nrf = static_cast<double>(nr);
    double nsrf = static_cast<double>(nsr);
    return nrf / nsrf;
}

double GCRSBaseComCollectStatistics::calcEfficiency(int nr, int ni,
        simtime_t delayTime, int hr, double hif,double distance) {
    if(ni == 0 || delayTime == 0.0f || hr == 0 || distance == 0.0f){
        return 0.0f;
    }
    double nrf = static_cast<double>(nr);
    double nif = static_cast<double>(ni);

    double hrf = static_cast<double>(hr);

    double speedRadio = 3.0f * pow(10.0f, 8.0f);
    double timeIdeal = distance / speedRadio;


    //double e = (nrf/(delayTime * hrf))/(nif/(timeIdeal*hif));
    double e = ((hrf/delayTime)*nrf)/((hif/timeIdeal)*nif);
    return e;
}
