#GeoCast Routing Simulator(GCRS)

GeoCast Routing Simulator is a vehicle-to-vehicle communication simulator. It is developed based on Vehicles in Network Simulation (Veins) framework that provides coupled network and road traffic simulation using two well-established simulators, OMNeT++ and Simulation of Urban MObility(SUMO). This simulator contains three parts, a Geocast network simulation system(GCRS), a road traffic environment generator(RTEG) and a statistical analysis and comparison tools(ReadXmlResult).

To run GCRS, you need:
  1. install VEINS and SUMO. 
  2. import this project in OMNET++ IDE. 
  3. run sumo server python sumo-launchd.py -vv -c sumo(sumo-gui)
  4. run GCRS

Change Log:
TODO:
1. Investage results.

Version: GCRS_v1.0.0_06_11_2013
1. <Modification> Modify event trigger mode. Add event trigger time. 
					When current time > event trigger time, the vehicles can trigger event.
2. <Bug Fixed> Fixed the ZOR/ZOF expire time more than simulation time.

Version: GCRS_v0.6.8_03_11_2013
1. <Bug Fixed> Print out bugs fixed.
2. <Modification> Instand of SimpleObstacleShadowing to GCRSBaseSimpleObstacleShadowing.
3. <Modification> Instand of PhyLayer80211p to GCRSBasePhyLayer.

Version: GCRS_v0.6.7_03_11_2013
1. <Bug Fixed> omnetpp.ini bug fixed.

Version: GCRS_v0.6.6_03_11_2013
1. <New> Print out result to xml files.
 
Version: GCRS_v0.6.5_01_11_2013
1. <Bug Fixed> Event contorl bugs fixed.

Version: GCRS_v0.6.4_31_10_2013
1. <Bug Fixed> Lots of bugs fixed.

Version: GCRS_v0.6.1_30_10_2013
1. <New> Add DTSG protocol for network layer

Version: GCRS_v0.6.0_29_10_2013
1. <New> Add event duration modification module.
2. <New> Add task manager for DTSG.
3. <New> Add packet for DTSG.
4. <New> Add a parameter "versoin" for GCRSBaseNetPkt and Network.
 
Version: GCRS_v0.5.12_25_10_2013(Beta)
1. <Bug Fixed> Task expire time bug fixed.
2. <Modification> Each vehicle triggers one event, each event occur once.
3. <Bug Fixed> The network createing time,location and other parameters are same if the RAND_SEED or road scenario dosen't change. 

Version: GCRS_v0.5.11_23_10_2013(Beta)
1. <Modification> Modify GCRSBaseComCollectStatistics::calcEfficiency().

Version: GCRS_v0.5.10_23_10_2013(Beta)
1. <Bug Fixed> Replace GCRSBaseComMath::calcAngle to GCRSBaseComMath::calcAngleWithDirection for calculating vehicle direction.
2. <Bug Fixed> Using OMNETPP coordination for offset instand of SUMO coordination.
3. <Bug Fixed> Fixed ZOR/ZOF Range judgement bug in GCRSBaseComMath::isInRectangleRange; 
 
Version: GCRS_v0.5.9_23_10_2013(Beta)
1. <New> Draw the range of ZOR/ZOF in simulation.
2. <Bug Fixed> Fixed some bugs.

Version: GCRS_v0.5.8_22_10_2013(Beta)
1. <Bug Fixed> Fixed formula bug in GCRSBaseComMath::tranCoordLocaltoWorld.
2. <Bug Fixed> Fixed ZOR/ZOF offset calculation bug in GCRSBaseComCollectNetworkRangeController::addNetworkRange. 
3. <Modification> Using *.node[*].appl.OFFSET = 450 instand of *.node[*].appl.OFFSET = 900.

Version: GCRS_v0.5.7_21_10_2013(Beta)
1. <Modification> Using GCRSBaseComVehicleEvent and GCRSBaseComVehicleEventControl instand of GCRSBaseComAccidentControl.
2. <New> Add getCrossRoads() function in GCRSBaseTraCIScenarioManagerLaunchd;
3. <Modification> Modify the structrue of GCRSBaseVehicleManager to fit for new Event components.

Version: GCRS_v0.5.6_17_10_2013(Beta)
1. <New>Add the network creating time in conclusion part.
2. <Modification>In conclusion part, each network will display their own property of ZOR/ZOF.
3. <Bug Fixed> The number of junctions and The number of polygons are correct.
4. <New>Add function to calculate Road/Building Density Ratio.
 
Version: GCRS_v0.5.5_16_10_2013(Beta)
1. <Bug Fixed>Add Time-to-live parameter in networkrange. When the time-to-live of network is expired, /
	the collection serivce will not count the number of vehicles passing through ZOR/ZOF.
2. <New>The position of ZOR/ZOF can be predifined which can be set in front of or behind of vehicle. 
3. <New>Add new functions to make ZOR cover same direction lanes and make ZOF cover all lanes.
4. <New>Straight line and junction use different kinds of ZOR/ZOF respectively.  
	   
Version: GCRS_v0.5.4_16_10_2013(Beta)
1. <Bug Fixed>Change omnetpp.ini file num-rngs=1000 -> num-rng=5000
2. <Modification>Change omnetpp.ini file #sim-time-limit = 1900s -> sim-time-limit = 1700s
3. <Modification>Add 3*3 building in road scenario.
4. <Modification>Change ZOR/ZOF shape ZOR_SHAPE/ZOF_SHAPE = 0 -> ZOR_SHAPE/ZOF_SHAPE = 1 (Circle to Rectangle)/
	ZOR_LENGTH/ZOF_LENGTH  = 500 -> ZOR_LENGTH/ZOF_LENGTH  = 1000 /
	ZOR_WIDTH/ZOF_WIDTH = 800/1000 -> ZOR_WIDTH/ZOF_WIDTH = 6/13
