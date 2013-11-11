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
#include <list>

class GCRSReadXml {
public:
    GCRSReadXml();
    GCRSReadXml(std::string rootTag, cXMLElement* xml);
    virtual ~GCRSReadXml();

    std::string readAttribute(std::string tag, std::string attr, std::string id);
    std::list<std::string> readAllIdsByTag(std::string tag);
protected:
    std::string readXml(cXMLElement* e, std::string tag, std::string attr, std::string id = "");

protected:
    std::string rootTag;
    cXMLElement* xml;

    std::list<std::string> listAttributes;
};

#endif /* GCRSREADXML_H_ */
