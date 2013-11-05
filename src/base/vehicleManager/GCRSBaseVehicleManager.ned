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

package gcrs.src.base.vehicleManager;

simple GCRSBaseVehicleManager{
    parameters:
        int NUM_VEHICLES = default(0);
        int RAND_SEED = default(0);
        int NUM_EVENT = default(50);
        int EVENT_TYPE = default(0); //0: Accident Event 1: Emergency
        double EVENT_AREA_RANGE = default(500);
        double MAX_EVENT_OCCUR_RATIO = default(0.8);
        double MAX_EVENT_START = default(1.0);
		int EVENT_DURATION_MODIFY_TIMES = default(1);
 	    double EVENT_DURATION_MIN = default(15.0);
 	    double EVENT_DURATION_MAX = default(60.0);
        @class(GCRSBaseVehicleManager);
}