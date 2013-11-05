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

package gcrs.src.base.nic;

import gcrs.src.base.mac.GCRSBaseMacLayer;
import gcrs.src.base.phy.GCRSBasePhyLayer;
//import org.mixim.modules.phy.PhyLayer80211p;

module GCRSBaseNic{
    gates:
        input upperLayerIn; // to upper layers
        output upperLayerOut; // from upper layers
        output upperControlOut; // control information 
        input upperControlIn; // control information 
        input radioIn; // radioIn gate for sendDirect
    submodules:
        phy: GCRSBasePhyLayer {
            @display("p=69,218;i=block/process_s");
        }

        mac: GCRSBaseMacLayer {
            @display("p=69,82");
        }
    connections:
        radioIn --> phy.radioIn;
        
        mac.lowerControlOut --> phy.upperControlIn;
        mac.lowerLayerOut --> phy.upperLayerIn;
        phy.upperLayerOut --> mac.lowerLayerIn;
        phy.upperControlOut --> mac.lowerControlIn;
        
        mac.upperControlIn <-- upperControlIn;
        mac.upperLayerIn <-- upperLayerIn;

        mac.upperLayerOut --> upperLayerOut;
        mac.upperControlOut --> upperControlOut;        
}