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

#ifndef GCRSBASESIMPLEOBSTACLESHADOWING_H_
#define GCRSBASESIMPLEOBSTACLESHADOWING_H_

#include <SimpleObstacleShadowing.h>

class GCRSBaseSimpleObstacleShadowing: public SimpleObstacleShadowing {
public:
    GCRSBaseSimpleObstacleShadowing(ObstacleControl& obstacleControl, double carrierFrequency, bool useTorus, const Coord& playgroundSize, bool debug);
    virtual ~GCRSBaseSimpleObstacleShadowing();

    /**
     * @brief Filters a specified Signal by adding an attenuation
     * over time to the Signal.
     */
    virtual void filterSignal(AirFrame *frame, const Coord& sendersPos, const Coord& receiverPos);
};

#endif /* GCRSBASESIMPLEOBSTACLESHADOWING_H_ */
