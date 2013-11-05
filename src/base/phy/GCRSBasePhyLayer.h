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

#ifndef GCRSBASEPHYLAYER_H_
#define GCRSBASEPHYLAYER_H_

#include <PhyLayer80211p.h>

class GCRSBasePhyLayer: public PhyLayer80211p {
protected:
    /**
     * @brief Creates and returns an instance of the AnalogueModel with the
     * specified name.
     *
     * Is able to initialize the following AnalogueModels:
     */
    virtual AnalogueModel* getAnalogueModelFromName(std::string name, ParameterMap& params);
    /**
     * @brief Creates and initializes a SimpleObstacleShadowing with the
     * passed parameter values.
     */
    AnalogueModel* initializeGCRSBaseSimpleObstacleShadowing(ParameterMap& params);
};

#endif /* GCRSBASEPHYLAYER_H_ */
