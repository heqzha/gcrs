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

#include "GCRSBaseComCollectNetworkController.h"

GCRSBaseComCollectNetworkController::GCRSBaseComCollectNetworkController() {

}

GCRSBaseComCollectNetworkController::~GCRSBaseComCollectNetworkController() {
    this->cleanUp();
}

GCRSBaseComNin::NinL3Type GCRSBaseComCollectNetworkController::createNetwork(
        GCRSBaseComNin::NinL3Type nin, simtime_t ttl) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network != NULL) {
        return GCRSBaseComNin::NINL3NULL;
    }
    network = new GCRSBaseComCollectNetwork(ttl);
    this->mapNetworks.insert(
            std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetwork*>::value_type(
                    nin, network));
    return nin;
}

void GCRSBaseComCollectNetworkController::setRootNode(
        GCRSBaseComNin::NinL3Type nin, GCRSBaseComVin::VinL3Type vin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return;
    }
    network->setRootNode(vin);
}
void GCRSBaseComCollectNetworkController::addRelayNode(
        GCRSBaseComNin::NinL3Type nin, GCRSBaseComVin::VinL3Type parentVin,
        GCRSBaseComVin::VinL3Type vin,
        GCRSBaseComCollectNode::range_category rc) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return;
    }
    network->addRelayNode(parentVin, vin, rc);
}

void GCRSBaseComCollectNetworkController::cancelRelayNode(
        GCRSBaseComNin::NinL3Type nin, GCRSBaseComVin::VinL3Type vin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return;
    }
    network->cancelRelayNode(vin);
}

unsigned int GCRSBaseComCollectNetworkController::checkNetworksState() {
    unsigned int numRestNetwork = 0;
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetwork*>::iterator iter;
    for (iter = this->mapNetworks.begin(); iter != this->mapNetworks.end();
            ++iter) {
        GCRSBaseComCollectNetwork* network = (*iter).second;
        if (network != NULL ) {
            if(!network->isFinished()){
                numRestNetwork++;
            }
        }
    }
    return numRestNetwork;
}

void GCRSBaseComCollectNetworkController::updateTTL(
        GCRSBaseComNin::NinL3Type nin, simtime_t ttl) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return;
    }
    network->setTTL(ttl);
    network->setUpdateTime(simTime());
}

void GCRSBaseComCollectNetworkController::updateVersion(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return;
    }
    network->updateVersion();
}

simtime_t GCRSBaseComCollectNetworkController::getCreateTime(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return 0.0f;
    }
    return network->getCreateTime();
}

simtime_t GCRSBaseComCollectNetworkController::getUpdateTime(GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return 0.0f;
    }
    return network->getUpdateTIme();
}

simtime_t GCRSBaseComCollectNetworkController::getTTL(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return 0.0f;
    }
    return network->getTTL();
}

simtime_t GCRSBaseComCollectNetworkController::getExpireTime(GCRSBaseComNin::NinL3Type nin){
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return 0.0f;
    }
    return network->getExpireTime();
}

long GCRSBaseComCollectNetworkController::getVersion(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return 0;
    }
    return network->getVersion();
}

GCRSBaseComVin::VinL3Type GCRSBaseComCollectNetworkController::getRootNodeVin(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return GCRSBaseComVin::VINL3NULL;
    }
    return network->getRootNodeVin();
}

int GCRSBaseComCollectNetworkController::getNumRxNodesInZor(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return -1;
    }
    return network->getNumRxNodesInZor();
}

int GCRSBaseComCollectNetworkController::getNumRxNodesInZof(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return -1;
    }
    return network->getNumRxNodesInZof();
}

int GCRSBaseComCollectNetworkController::getNumRelayNodes(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return -1;
    }
    return network->getNumRelayNodes();
}

int GCRSBaseComCollectNetworkController::getMaxHops(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return -1;
    }
    return network->getMaxHops();
}

simtime_t GCRSBaseComCollectNetworkController::getMaxDelayTime(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return -1;
    }
    return network->getMaxDelayTime();
}

simtime_t GCRSBaseComCollectNetworkController::getNetworkCreateTime(
        GCRSBaseComNin::NinL3Type nin) {
    GCRSBaseComCollectNetwork* network = this->getNetworkByNin(nin);
    if (network == NULL) {
        return 0.0f;
    }
    return network->getCreateTime();
}

GCRSBaseComCollectNetwork* GCRSBaseComCollectNetworkController::getNetworkByNin(
        GCRSBaseComNin::NinL3Type nin) {
    if (this->mapNetworks.empty()) {
        return NULL;
    }
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetwork*>::iterator iter;
    iter = this->mapNetworks.find(nin);
    if (iter == this->mapNetworks.end()) {
        return NULL;
    }
    return (*iter).second;
}

void GCRSBaseComCollectNetworkController::cleanUp() {
    std::map<GCRSBaseComNin::NinL3Type, GCRSBaseComCollectNetwork*>::iterator iter;
    for (iter = this->mapNetworks.begin(); iter != this->mapNetworks.end();) {
        if ((*iter).second != NULL) {
            delete (*iter).second;
        }
        this->mapNetworks.erase(iter++);
    }
}
