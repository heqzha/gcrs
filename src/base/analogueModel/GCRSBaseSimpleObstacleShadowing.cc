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

#include "GCRSBaseSimpleObstacleShadowing.h"

#define debugEV (ev.isDisabled()||!debug) ? ev : ev << "PhyLayer(GCRSBaseSimpleObstacleShadowing): "

GCRSBaseSimpleObstacleShadowing::GCRSBaseSimpleObstacleShadowing(
        ObstacleControl& obstacleControl, double carrierFrequency,
        bool useTorus, const Coord& playgroundSize, bool debug) :
        SimpleObstacleShadowing(obstacleControl, carrierFrequency, useTorus,
                playgroundSize, debug) {
    // TODO Auto-generated constructor stub

}

GCRSBaseSimpleObstacleShadowing::~GCRSBaseSimpleObstacleShadowing() {
    // TODO Auto-generated destructor stub
}

void GCRSBaseSimpleObstacleShadowing::filterSignal(AirFrame *frame, const Coord& sendersPos, const Coord& receiverPos){
    Signal& s = frame->getSignal();

    double factor = obstacleControl.calculateAttenuation(sendersPos, receiverPos);
    //If there is one obstacle, then block the signal.
    factor = factor < 1.0f? 0.0f:factor;

    debugEV << "value is: " << factor << endl;

    bool hasFrequency = s.getTransmissionPower()->getDimensionSet().hasDimension(Dimension::frequency);
    const DimensionSet& domain = hasFrequency ? DimensionSet::timeFreqDomain : DimensionSet::timeDomain;
    ConstantSimpleConstMapping* attMapping = new ConstantSimpleConstMapping(domain, factor);
    s.addAttenuation(attMapping);
}
