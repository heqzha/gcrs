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

#include "GCRSBaseConnectionManager.h"
#include "BaseWorldUtility.h"

#ifndef ccEV
#define ccEV (ev.isDisabled()||!coreDebug) ? ev : ev << getName() << ": "
#endif

Define_Module( GCRSBaseConnectionManager );

double GCRSBaseConnectionManager::calcInterfDist(){
    double pMax = par("pMax").doubleValue();
    double interfDistance = par("InterfDistance").doubleValue();

    if(pMax <= 0.0f){
        return interfDistance;
    }
    return calcInterfDistByPowerMax(pMax);
}

double GCRSBaseConnectionManager::calcPowerMax(double interfDistance) {
    double pMax;
    //the maximum interference distance
    if (interfDistance <= 0.0f) {
            error("Interference distance is <=0!");
        }
    //the minimum carrier frequency for this cell
    double carrierFrequency = par("carrierFrequency").doubleValue();
    //minimum signal attenuation threshold
    double sat = par("sat").doubleValue();
    //minimum path loss coefficient
    double alpha = par("alpha").doubleValue();

    double waveLength = (BaseWorldUtility::speedOfLight / carrierFrequency);
    //minimum power level to be able to physically receive a signal
    double minReceivePower = pow(10.0, sat / 10.0);

    pMax = (pow(interfDistance, alpha) * (16 * M_PI * M_PI * minReceivePower))
            / (waveLength * waveLength);

    ccEV << "maximum transmission power possible:" << pMax << endl;

    return pMax;
}

double GCRSBaseConnectionManager::calcInterfDistByPowerMax(double pMax){
    double interfDistance;
    if(pMax <= 0.0f){
        //maximum transmission power possible
        error("Max transmission power is <=0!");
    }
    //the minimum carrier frequency for this cell
    double carrierFrequency = par("carrierFrequency").doubleValue();
    //minimum signal attenuation threshold
    double sat              = par("sat").doubleValue();
    //minimum path loss coefficient
    double alpha            = par("alpha").doubleValue();

    double waveLength     = (BaseWorldUtility::speedOfLight/carrierFrequency);
    //minimum power level to be able to physically receive a signal
    double minReceivePower = pow(10.0, sat/10.0);

    interfDistance = pow(waveLength * waveLength * pMax
                           / (16.0*M_PI*M_PI*minReceivePower),
                         1.0 / alpha);

    ccEV << "max interference distance:" << interfDistance << endl;

    return interfDistance;
}
