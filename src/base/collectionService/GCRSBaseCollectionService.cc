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

#include "GCRSBaseCollectionService.h"
#include "GCRSBaseConst.h"
#include "Convert.h"

Define_Module(GCRSBaseCollectionService)
;
#define EV_HEAD "GCRSBaseCollectionService: "
#define EV_WARNING_HEAD "GCRSBaseCollectionService:<WARNING> "
#define EV_ERROR_HEAD "GCRSBaseCollectionService:<ERROR> "

void GCRSBaseCollectionService::initialize(int stage) {
    if (stage == 0) {

        this->ninCounter = 0;

        std::string protocolName = hasPar("PROTOCOL")?par("PROTOCOL").stringValue():"";
        if(protocolName.size() > 0){
            this->printOut = new GCRSBaseComCollectPrintOut(protocolName);
        }
        int zorShape =
                hasPar("ZOR_SHAPE") ?
                        par("ZOR_SHAPE").longValue() :
                        CON_NET_DEFAULT_ZOR_SHAPE_RECTANGLE;
        double zorLength =
                hasPar("ZOR_LENGTH") ?
                        par("ZOR_LENGTH").doubleValue() :
                        CON_NET_DEFAULT_ZOR_SHAPE_RECTANGLE_LENGTH;
        double zorWidth =
                hasPar("ZOR_WIDTH") ?
                        par("ZOR_WIDTH").doubleValue() :
                        CON_NET_DEFAULT_ZOR_SHAPE_RECTANGLE_WIDTH;

        int zofShape =
                hasPar("ZOF_SHAPE") ?
                        par("ZOF_SHAPE").longValue() :
                        CON_NET_DEFAULT_ZOF_SHAPE_RECTANGLE;
        double zofLength =
                hasPar("ZOF_LENGTH") ? par("ZOF_LENGTH").doubleValue() :
                CON_NET_DEFAULT_ZOF_SHAPE_RECTANGLE_LENGTH;

        double zofWidth =
                hasPar("ZOF_WIDTH") ?
                        par("ZOF_WIDTH").doubleValue() :
                        CON_NET_DEFAULT_ZOF_SHAPE_RECTANGLE_WIDTH;

        double laneWidth =
                hasPar("LANE_WIDTH") ? par("LANE_WIDTH").doubleValue() : 0.0f;
        this->buildingInterval = hasPar("BUILDINGINTERVAL")?par("BUILDINGINTERVAL").doubleValue():0.0f;



        this->roadWidth = zofWidth;

        this->networkCtrl = new GCRSBaseComCollectNetworkController();
        this->networkRangeCtrl = new GCRSBaseComCollectNetworkRangeController(
                zorShape, zofShape, zorLength, zofLength, zorWidth, zofWidth,laneWidth);

        this->traciManager = GCRSBaseTraCIScenarioManagerLaunchdAccess().get();
        this->vManager = GCRSBaseVehicleManagerAccess().get();
        this->connectionManager = GCRSBaseConnectionManagerAccess().get();

        this->selfMsg_CollectBasicInfo = new cMessage("UsecasInfo",
                SC_USECASE_INFO);
        scheduleAt(simTime() + 0.1f, this->selfMsg_CollectBasicInfo);

        this->updateInterval =
                hasPar("UPDATEINTERVAL") ?
                        par("UPDATEINTERVAL").doubleValue() : 0.1f;
        this->selfMsg_Update = new cMessage("Update", SC_UPDATE);
        scheduleAt(simTime() + updateInterval, this->selfMsg_Update);
    }
}

void GCRSBaseCollectionService::finish() {
    this->simEnd = time(NULL);
    if (this->selfMsg_CollectBasicInfo->isScheduled()) {
        cancelAndDelete(this->selfMsg_CollectBasicInfo);
    } else {
        delete (this->selfMsg_CollectBasicInfo);
    }

    if (this->selfMsg_Update->isScheduled()) {
        cancelAndDelete(this->selfMsg_Update);
    } else {
        delete (this->selfMsg_Update);
    }
    /*
     * Calculate Statistics
     */
    this->conclusion();
    /*
     * Print out
     */
    EV<<EV_HEAD<<"All results are printed out to XML file"<<endl;
    delete this->printOut;
    delete this->networkCtrl;
    delete this->networkRangeCtrl;
}

void GCRSBaseCollectionService::handleMessage(cMessage* msg) {
    if (msg == NULL) {
        return;
    }
    switch (msg->getKind()) {
    case SC_USECASE_INFO: {
        Coord playground = this->traciManager->calcPlayGround();
        this->playgroundX = playground.x;
        this->playgroundY = playground.y;
        this->roadLength = this->traciManager->calcRoadLength(playground);
        this->numCrossRoads = this->traciManager->getNumCrossRoads();
        this->numPolygon = this->traciManager->getNumPolygonsInEachBlock();
        this->txRange = this->connectionManager->getMaxIterferenceDistance();
        this->simStart = time(NULL);
        break;
    }
    case SC_UPDATE: {
        this->numVehicle = this->vManager->getNumVehicles();
        this->checkNetworkRanges();
        this->networkCtrl->checkNetworksState();
        scheduleAt(simTime() + updateInterval, this->selfMsg_Update);
        break;
    }
    default: {
        delete msg;
        break;
    }
    }
}

double GCRSBaseCollectionService::calcRoadBuidingDensityRatio(double roadLength, int numPolygons, double interval){
    if(numPolygons <= 0 || interval <= 0.0f)return 0.0f;
    //Calculate the width between different sides buildings.
    double dNumPolygons = static_cast<double>(numPolygons);
    double widthBetweenBuildings = roadLength/(2*sqrt(dNumPolygons)*interval);
    return widthBetweenBuildings/roadLength;
}

void GCRSBaseCollectionService::checkNetworkRanges() {
    std::list<GCRSBaseComVin::VinL3Type> listVin = this->vManager->getAllVin();
    if (listVin.empty()) {
        return;
    }
    std::list<GCRSBaseComVin::VinL3Type>::iterator iter;
    for (iter = listVin.begin(); iter != listVin.end(); ++iter) {
        Coord loc = this->vManager->getLocation((*iter));
        this->networkRangeCtrl->checkPassThroughNode((*iter), loc);
    }
}

GCRSBaseComNin::NinL3Type GCRSBaseCollectionService::getUniqueNin() {
    return this->ninCounter++;
}
void GCRSBaseCollectionService::conclusion() {
//    EV<< EV_HEAD <<"<Conclusion>"<<endl;
    char str_simStart[100];
    char str_simEnd[100];
    GCRSBaseRealWorldTimer::convert(str_simStart, sizeof(str_simStart), this->simStart);
    GCRSBaseRealWorldTimer::convert(str_simEnd, sizeof(str_simEnd), this->simEnd);
    this->printOut->addElement("The_Simulation_Start_at", str_simStart,this->printOut->getRootElement());
    this->printOut->addElement("The_Simulation_End_at", str_simEnd,this->printOut->getRootElement());
    this->printOut->addElement("Playground_X", Convert::DoubleToString(this->playgroundX),this->printOut->getRootElement());
    this->printOut->addElement("Playground_Y", Convert::DoubleToString(this->playgroundY),this->printOut->getRootElement());
    this->printOut->addElement("Road_Length", Convert::DoubleToString(this->roadLength),this->printOut->getRootElement());
    this->printOut->addElement("Road_Building_Density_Ratio", Convert::DoubleToString(this->calcRoadBuidingDensityRatio(this->roadLength,this->numPolygon,this->buildingInterval)),this->printOut->getRootElement());
    this->printOut->addElement("Number_of_CrossRoads", Convert::IntegerToString(this->numCrossRoads),this->printOut->getRootElement());
    this->printOut->addElement("Number_of_Polygons", Convert::IntegerToString(this->numPolygon),this->printOut->getRootElement());
    this->printOut->addElement("Number_of_Vehicles", Convert::IntegerToString(this->numVehicle),this->printOut->getRootElement());
    this->printOut->addElement("The_Range_of_Transmission", Convert::DoubleToString(this->txRange),this->printOut->getRootElement());
/*    EV << EV_HEAD <<"The simulation start at: "<< str_simStart <<endl;
    EV << EV_HEAD <<"The simulation end at: "<< str_simEnd <<endl;
    EV << EV_HEAD <<"Playground X:"<<this->playgroundX<<endl;
    EV << EV_HEAD <<"Playground Y:"<<this->playgroundY<<endl;
    EV << EV_HEAD <<"Road Length:"<<this->roadLength<<endl;
    EV << EV_HEAD <<"Road/Building Density Ratio:"<<
            this->calcRoadBuidingDensityRatio(this->roadLength,this->numPolygon,this->buildingInterval)<<endl;
    EV << EV_HEAD <<"Number of CrossRoads:"<<this->numCrossRoads<<endl;
    EV << EV_HEAD <<"Number of Polygons:"<<this->numPolygon<<endl;
    EV << EV_HEAD <<"Number of Vehicles:"<<this->numVehicle<<endl;
    EV << EV_HEAD <<"The Range of transmission:"<<this->txRange<<endl;*/
    for(GCRSBaseComNin::NinL3Type nin = 0; nin < this->ninCounter; nin++) {
        int numRxNodesInZor = this->networkCtrl->getNumRxNodesInZor(nin);
        int numRxNodesInZof = this->networkCtrl->getNumRxNodesInZof(nin);
        simtime_t createTime = this->networkCtrl->getNetworkCreateTime(nin);
        simtime_t ttl = this->networkCtrl->getTTL(nin);
        int maxHops = this->networkCtrl->getMaxHops(nin);
        simtime_t maxDelayTime = this->networkCtrl->getMaxDelayTime(nin);
        int numPassThroughZorNodes = this->networkRangeCtrl->getNumPassThroughZorNodes(nin);
        int numPassThroughZofNodes = this->networkRangeCtrl->getNumPassThroughZofNodes(nin);
        double lhopi = this->networkRangeCtrl->getLengthZor(nin) / this->txRange;
        double whopi = this->networkRangeCtrl->getWidthZor(nin) / this->txRange;
        double hopi = ceil(lhopi + whopi);
        double efficiency = GCRSBaseComCollectStatistics::calcEfficiency(numRxNodesInZor, numPassThroughZorNodes, maxDelayTime, maxHops, hopi,this->networkRangeCtrl->getLengthZor(nin));
        TiXmlElement* networkElement = this->printOut->addElement("Network_Identification_Number", this->printOut->getRootElement());
        this->printOut->setElementAttribute(networkElement, "ID", Convert::LongToString(nin));
        this->printOut->addElement("Network_Created_by", Convert::LongToString(this->networkCtrl->getRootNodeVin(nin)), networkElement);
        this->printOut->addElement("Network_Creating_Time", Convert::DoubleToString(createTime.dbl()), networkElement);
        this->printOut->addElement("Network_Time_to_live", Convert::DoubleToString(ttl.dbl()), networkElement);
        this->printOut->addElement("The_Location_of_ZOR", Convert::CoordToString(this->networkRangeCtrl->getLocationZor(nin)), networkElement);
        this->printOut->addElement("The_Shape_of_ZOR", Convert::IntegerToString(this->networkRangeCtrl->getShapeZor(nin)), networkElement);
        this->printOut->addElement("The_Length_of_ZOR", Convert::DoubleToString(this->networkRangeCtrl->getLengthZor(nin)), networkElement);
        this->printOut->addElement("The_Width_of_ZOR", Convert::DoubleToString(this->networkRangeCtrl->getWidthZor(nin)), networkElement);
        this->printOut->addElement("The_Location_of_ZOF", Convert::CoordToString(this->networkRangeCtrl->getLocationZof(nin)), networkElement);
        this->printOut->addElement("The_Shape_of_ZOF", Convert::IntegerToString(this->networkRangeCtrl->getShapeZof(nin)), networkElement);
        this->printOut->addElement("The_Length_of_ZOF", Convert::DoubleToString(this->networkRangeCtrl->getLengthZof(nin)), networkElement);
        this->printOut->addElement("The_Width_of_ZOF", Convert::DoubleToString(this->networkRangeCtrl->getWidthZof(nin)), networkElement);
        this->printOut->addElement("The_Number_of_Received_Message_Nodes_ZOR", Convert::IntegerToString(numRxNodesInZor), networkElement);
        this->printOut->addElement("The_Number_of_Received_Message_Nodes_ZOF", Convert::IntegerToString(numRxNodesInZof), networkElement);
        this->printOut->addElement("The_Max_Hops", Convert::IntegerToString(maxHops), networkElement);
        this->printOut->addElement("The_Max_Delay_Time", Convert::DoubleToString(maxDelayTime.dbl()), networkElement);
        this->printOut->addElement("The_Number_of_Nodes_Which_Passing_Through_ZOR", Convert::IntegerToString(numPassThroughZorNodes), networkElement);
        this->printOut->addElement("The_Number_of_Nodes_Which_Passing_Through_ZOF", Convert::IntegerToString(numPassThroughZofNodes), networkElement);
        this->printOut->addElement("The_Packet_Delivery_Ratio", Convert::DoubleToString(GCRSBaseComCollectStatistics::calcPDR(numRxNodesInZor, numPassThroughZorNodes)), networkElement);
        this->printOut->addElement("The_Efficiency", Convert::DoubleToString(efficiency), networkElement);
/*        EV << EV_HEAD <<"---------------------------------------------------------------------------------"<<endl;
        EV << EV_HEAD <<"Network Identification Number:"<<nin<<endl;
        EV << EV_HEAD <<"Network Created by: " <<this->networkCtrl->getRootNodeVin(nin)<<endl;
        EV << EV_HEAD <<"Network Creating Time: "<<createTime<<endl;
        EV << EV_HEAD <<"Network Time-to-live: "<<ttl<<endl;
        EV << EV_HEAD <<"The location of ZOR: " << this->networkRangeCtrl->getLocationZor(nin)<<endl;
        EV << EV_HEAD <<"The Shape of ZOR:" << this->networkRangeCtrl->getShapeZor(nin)<<endl;
        EV << EV_HEAD <<"The Length of ZOR:" << this->networkRangeCtrl->getLengthZor(nin)<<endl;
        EV << EV_HEAD <<"The Width of ZOR:" << this->networkRangeCtrl->getWidthZor(nin)<<endl;
        EV << EV_HEAD <<"The Shape of ZOF:" << this->networkRangeCtrl->getShapeZof(nin)<<endl;
        EV << EV_HEAD <<"The Length of ZOF:" << this->networkRangeCtrl->getLengthZof(nin)<<endl;
        EV << EV_HEAD <<"The Width of ZOF:" << this->networkRangeCtrl->getWidthZof(nin)<<endl;
        EV << EV_HEAD <<"The Number of Received Message Nodes(ZOR):"<<numRxNodesInZor<<endl;
        EV << EV_HEAD <<"The Number of Received Message Nodes(ZOF):"<<numRxNodesInZof<<endl;
        EV << EV_HEAD <<"The Max Hops:"<<maxHops<<endl;
        EV << EV_HEAD <<"The Max Delay Time:"<<maxDelayTime<<endl;
        EV << EV_HEAD <<"The Number of Nodes Which Passing Through ZOR:"<<numPassThroughZorNodes<<endl;
        EV << EV_HEAD <<"The Number of Nodes Which Passing Through ZOF:"<<numPassThroughZofNodes<<endl;
        EV << EV_HEAD <<"The Packet Delivery Ratio:" << GCRSBaseComCollectStatistics::calcPDR(numRxNodesInZor, numPassThroughZorNodes)<<endl;
        double lhopi = this->networkRangeCtrl->getLengthZor(nin) / this->txRange;
        double whopi = this->networkRangeCtrl->getWidthZor(nin) / this->txRange;
        double hopi = ceil(lhopi + whopi);
        EV << EV_HEAD <<"The Efficiency: "<< GCRSBaseComCollectStatistics::calcEfficiency(numRxNodesInZor, numPassThroughZorNodes, maxDelayTime, maxHops, hopi,this->networkRangeCtrl->getLengthZor(nin))<<endl;
        EV << EV_HEAD <<"---------------------------------------------------------------------------------"<<endl;*/
    }
    this->printOut->PrintOut();
    /*EV << EV_HEAD <<"</Conclusion>"<<endl;*/
}
GCRSBaseComNin::NinL3Type GCRSBaseCollectionService::createNetwork(
        GCRSBaseComVin::VinL3Type vin, simtime_t ttl, Coord loc, double offset,
        double direct,int landIndex) {
    GCRSBaseComNin::NinL3Type nin = this->networkCtrl->createNetwork(
            this->getUniqueNin(), ttl);
    this->networkCtrl->setRootNode(nin, vin);
    Coord junction = this->traciManager->getNearbyCrossRoadLocation(loc,this->roadWidth);
    this->networkRangeCtrl->addNetworkRange(nin, loc, offset, direct, ttl,landIndex,junction);
    return nin;
}

void GCRSBaseCollectionService::addRelayNode(GCRSBaseComNin::NinL3Type nin,
        GCRSBaseComVin::VinL3Type parentVin, GCRSBaseComVin::VinL3Type vin,
        GCRSBaseComCollectNode::range_category rc) {
    this->networkCtrl->addRelayNode(nin, parentVin, vin, rc);
}

void GCRSBaseCollectionService::cancelRelayNode(GCRSBaseComNin::NinL3Type nin,
        GCRSBaseComVin::VinL3Type vin) {
    this->networkCtrl->cancelRelayNode(nin, vin);
}

bool GCRSBaseCollectionService::isInZorNetworkRange(
        GCRSBaseComNin::NinL3Type nin, Coord loc) {
    return this->networkRangeCtrl->isInZorRange(nin, loc);
}

bool GCRSBaseCollectionService::isInZofNetworkRange(
        GCRSBaseComNin::NinL3Type nin, Coord loc) {
    return this->networkRangeCtrl->isInZofRange(nin, loc);
}

void GCRSBaseCollectionService::updateNetworkTTL(GCRSBaseComNin::NinL3Type nin, simtime_t ttl){
    this->networkCtrl->updateTTL(nin,ttl);
    this->networkRangeCtrl->updateTTL(nin,ttl);
}

void GCRSBaseCollectionService::updateNetworkVersion(GCRSBaseComNin::NinL3Type nin){
    this->networkCtrl->updateVersion(nin);
}

simtime_t GCRSBaseCollectionService::getNetworkCreateTime(GCRSBaseComNin::NinL3Type nin){
    return this->networkCtrl->getCreateTime(nin);
}

simtime_t GCRSBaseCollectionService::getNetworkUpdateTime(GCRSBaseComNin::NinL3Type nin){
    return this->networkCtrl->getUpdateTime(nin);
}

simtime_t GCRSBaseCollectionService::getNetworkTTL(
        GCRSBaseComNin::NinL3Type nin) {
    return this->networkCtrl->getTTL(nin);
}

simtime_t GCRSBaseCollectionService::getNetworkExipreTime(GCRSBaseComNin::NinL3Type nin){
    return this->networkCtrl->getExpireTime(nin);
}

long GCRSBaseCollectionService::getNetworkVersion(GCRSBaseComNin::NinL3Type nin){
    return this->networkCtrl->getVersion(nin);
}

GCRSBaseCollectionService::NetworkParams GCRSBaseCollectionService::getNetworkParameters(GCRSBaseComNin::NinL3Type nin, int networkType){
    GCRSBaseCollectionService::NetworkParams nPars;
    switch(networkType){
    case GCRSBaseComCollectNode::RC_ZOR:
        nPars.location = this->networkRangeCtrl->getLocationZor(nin);
        nPars.shape = this->networkRangeCtrl->getShapeZor(nin);
        nPars.length = this->networkRangeCtrl->getLengthZor(nin);
        nPars.width = this->networkRangeCtrl->getWidthZor(nin);
        nPars.direction = this->networkRangeCtrl->getDirectionZor(nin);
        break;
    case GCRSBaseComCollectNode::RC_ZOF:
        nPars.location = this->networkRangeCtrl->getLocationZof(nin);
        nPars.shape = this->networkRangeCtrl->getShapeZof(nin);
        nPars.length = this->networkRangeCtrl->getLengthZof(nin);
        nPars.width = this->networkRangeCtrl->getWidthZof(nin);
        nPars.direction = this->networkRangeCtrl->getDirectionZof(nin);
        break;
    }
    return nPars;
}

int GCRSBaseCollectionService::getNumVehiclePassThroughZor(GCRSBaseComNin::NinL3Type nin){
    return this->networkRangeCtrl->getNumPassThroughZorNodes(nin);
}

int GCRSBaseCollectionService::getNumVehiclePassThroughZof(GCRSBaseComNin::NinL3Type nin){
    return this->networkRangeCtrl->getNumPassThroughZofNodes(nin);
}
