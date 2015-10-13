#GeoCast Routing Simulator(GCRS)

GeoCast Routing Simulator is a vehicle-to-vehicle communication simulator. It is developed based on Vehicles in Network Simulation (Veins) framework that provides coupled network and road traffic simulation using two well-established simulators, OMNeT++ and Simulation of Urban MObility(SUMO). This simulator contains three parts, a Geocast network simulation system(GCRS), a road traffic environment generator(RTEG) and a statistical analysis and comparison tools(ReadXmlResult).

To run GCRS, you need:
  1. install VEINS and SUMO. 
  2. import this project in OMNET++ IDE. 
  3. run sumo server python sumo-launchd.py -vv -c sumo(sumo-gui)
  4. run GCRS
  5. all results are in results/
