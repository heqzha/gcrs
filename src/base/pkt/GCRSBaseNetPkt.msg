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
cplusplus {{
#include "NetwPkt_m.h"
#include "GCRSBaseComZone.h"
#include <Coord.h>

}}

class NetwPkt;
class noncobject GCRSBaseComZone;
class noncobject Coord;

packet GCRSBaseNetPkt extends NetwPkt {
    //@brief Vehicle identification number of original source node
    long vinOriginSrc = -1;
    //@brief Vehicle identification number of forwarding source node
    long vinForwardSrc = -1;
    //@brief Vehicle identification number of destination node
    long vinDest = -1;
    //@brief Power Level with which this packet was sent
	int priority = 3;
	//@brief Channel Number on which this packet was sent
	int channelNumber;
	//@brief Location of source node
    Coord locSrc;    
    //@brief Location of forwarding node
    Coord locForwad;
    //@brief Speed of source node
    Coord speedSrc;
    //@brief Speed of forwarding node
    Coord speedForwad;
    //@brief Max speed of source node
    double speedMaxSrc;
    //@brief Max speed of forwarding node
    double speedMaxForwarding;
    //@brief Zone of relevance and zone of fowarding
	long nin = -1;
    //@brief Hops
    long hops;
    //@brief Time-to-live
    simtime_t timeTtl = 0.0f;
    //@brief Forwarding time stamp
    simtime_t timestampForwarding = 0.0f;
    //@brief Time stamp
	simtime_t timestamp = 0.0f;
	//
	long version = 0;
}