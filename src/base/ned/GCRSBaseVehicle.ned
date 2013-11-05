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

package gcrs.src.base.ned;
import org.mixim.base.modules.*;
import gcrs.src.base.nic.GCRSBaseNic;

module GCRSBaseVehicle
{
    parameters:
        string applType;	//Type of the application layer.
        string netwType;	//Type of the network layer.
        string mobilityType;	//Type of the mobility module.
    gates:
        input radioIn;		//gate for sendDirect
    submodules:
        mobility: <mobilityType> like IMobility {//Defined for vehicle position
            parameters:
                @display("p=130,180;i=block/cogwheel");
        }
        appl: <applType> like IBaseApplLayer {//Defined for application layer
            parameters:
                @display("p=60,39;i=app");
        }

        net: <netwType> like IBaseNetwLayer {//Definded for network layer. TODO:We can define our protocol here.
            parameters:
                @display("p=61,108;i=block/layer");
        }
        nic: GCRSBaseNic {
            parameters:
                @display("p=61,180;i=block/wrxtx,#008000");
        }      
    connections:

        nic.upperLayerOut --> net.lowerLayerIn;
        nic.upperLayerIn <-- net.lowerLayerOut;
        nic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> net.lowerControlIn;
        nic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- net.lowerControlOut;

        net.upperLayerOut --> appl.lowerLayerIn;
        net.upperLayerIn <-- appl.lowerLayerOut;
        net.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); }--> appl.lowerControlIn;
        net.upperControlIn <--{ @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;   

        radioIn --> nic.radioIn;      
}