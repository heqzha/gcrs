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

#ifndef GCRSREADXML_H_
#define GCRSREADXML_H_
#include <omnetpp.h>
#include <vector>

class GCRSReadXml {
public:
    GCRSReadXml();
    GCRSReadXml(std::string rootTag, cXMLElement* xml);
    virtual ~GCRSReadXml();

    std::string readAttribute(std::string tag, std::string attr, std::string id);
    std::vector<std::string> readAllRouteIds();
    std::vector<std::string> readAllVehilceTypeIds();
    std::vector<std::string> readLaneIdsOfEdge(std::string edgeId);
    std::vector<std::string> readEdgeIdsOfRoute(std::string routeId);

protected:
    void readXmlChildElement(cXMLElement* e, std::string tag);
    void readXmlAttributeValues(std::string attr);
    std::string readXmlAttributeValue(std::string attr, std::string id);
    std::string readXmlAttributeValue(cXMLElement* e, std::string tag, std::string attr, std::string id = "");

protected:
    std::string rootTag;
    cXMLElement* xml;

    std::vector<cXMLElement*> vecChildrenElement;
    std::vector<std::string> vecAttributes;
};

#endif /* GCRSREADXML_H_ */
