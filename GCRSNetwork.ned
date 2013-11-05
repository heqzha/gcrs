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

package gcrs;

//import org.mixim.base.connectionManager.ConnectionManager;
import gcrs.src.base.connectionManager.GCRSBaseConnectionManager;
import gcrs.src.base.world.GCRSBaseWorldUtility;
import org.mixim.modules.obstacle.ObstacleControl;
import org.mixim.modules.world.annotations.AnnotationManager;
import gcrs.src.base.traci.GCRSBaseTraCIScenarioManagerLaunchd;
import gcrs.src.base.vehicleManager.GCRSBaseVehicleManager;
import gcrs.src.base.collectionService.GCRSBaseCollectionService;

network GCRSNetwork
{
    parameters:
        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
    //@display("bgb=306,200,white;bgp=0,0");	
    	string vehicleManagerType = default("GCRSBaseVehicleManager");
    submodules:
        obstacles: ObstacleControl {
            @display("p=38,74");
        }
        annotations: AnnotationManager {
            @display("p=150,76");
        }
        connectionManager: GCRSBaseConnectionManager {
            parameters:
                @display("p=150,0;b=42,42,rect,green,,;i=abstract/multicast");
        }
        world: GCRSBaseWorldUtility {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                playgroundSizeZ = playgroundSizeZ;
                @display("p=30,0;i=misc/globe");
        }
        manager: GCRSBaseTraCIScenarioManagerLaunchd {
            parameters:
                @display("p=239,76");
        }
        vehicleManager: GCRSBaseVehicleManager {
            @display("p=328,76");
        }
        collectService: GCRSBaseCollectionService {
            @display("p=306,15");
        }
    connections allowunconnected:
}
