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

#include "GCRSReadXml.h"

GCRSReadXml::GCRSReadXml() {
    this->rootTag = "";
    this->xml = NULL;
}

GCRSReadXml::GCRSReadXml(std::string rootTag, cXMLElement* xml) {
    if (xml != NULL) {
        this->rootTag = rootTag;
        this->xml = xml;
        std::string root = this->xml->getTagName();
        ASSERT(root.compare(this->rootTag) == 0);
    } else {
        this->rootTag = "";
        this->xml = NULL;
    }

}

GCRSReadXml::~GCRSReadXml() {
    if (this->xml == NULL)
        delete this->xml;
}
//TODO test
std::string GCRSReadXml::readAttribute(std::string tag, std::string attr,
        std::string id) {
    return this->readXmlAttributeValue(this->xml, tag, attr, id);
}

std::list<std::string> GCRSReadXml::readAllRouteIds() {
/*    this->listAttributes.clear();
    this->readXmlAttributeValue(this->xml, "route", "id");
    return this->listAttributes;*/
    this->listAttributes.clear();
    this->listChildrenElement.clear();
    this->readXmlChildElement(this->xml, "route");
    this->readXmlAttributeValues("id");
    return this->listAttributes;
}

std::list<std::string> GCRSReadXml::readAllVehilceTypeIds(){
/*    this->listAttributes.clear();
    this->readXmlAttributeValue(this->xml, "vType", "id");
    return this->listAttributes;*/
    this->listAttributes.clear();
    this->listChildrenElement.clear();
    this->readXmlChildElement(this->xml, "vType");
    this->readXmlAttributeValues("id");
    return this->listAttributes;
}

std::list<std::string> GCRSReadXml::readLaneIdsOfEdge(std::string edgeId){
    this->listAttributes.clear();
    this->listChildrenElement.clear();

    this->readXmlChildElement(this->xml, "edge");
    std::list<cXMLElement*> listElement = this->listChildrenElement;
    std::list<cXMLElement*>::iterator iter;
    for(iter = listElement.begin(); iter != listElement.end(); ++iter){
        ASSERT((*iter)->getAttribute("id"));
        std::string id = (*iter)->getAttribute("id");
        if(edgeId.compare(id) == 0){
            this->readXmlChildElement((*iter), "lane");
            break;
        }
    }
    this->readXmlAttributeValues("id");
    return this->listAttributes;
}

void GCRSReadXml::readXmlChildElement(cXMLElement* e, std::string tag){
    if(e == NULL)
        return;
    std::string eTag = e->getTagName();
    if (eTag.compare(tag) == 0) {
        this->listChildrenElement.push_back(e);
        return;
    }
    cXMLElementList list = e->getChildren();
    for (cXMLElementList::const_iterator i = list.begin(); i != list.end();
            ++i) {
        this->readXmlChildElement(*i, tag);
    }
}

void GCRSReadXml::readXmlAttributeValues(std::string attr){
    std::list<cXMLElement*>::iterator iter;
    for(iter = this->listChildrenElement.begin(); iter != this->listChildrenElement.end(); ++iter){
        ASSERT((*iter)->getAttribute(attr.c_str()));
        std::string value = std::string((*iter)->getAttribute(attr.c_str()));
        this->listAttributes.push_back(value);
    }
}

std::string GCRSReadXml::readXmlAttributeValue(std::string attr, std::string id){
    std::string value = "";
    std::list<cXMLElement*>::iterator iter;
    for(iter = this->listChildrenElement.begin(); iter != this->listChildrenElement.end(); ++iter){
        ASSERT((*iter)->getAttribute("id"));
        std::string eId = std::string((*iter)->getAttribute("id"));
        if(eId.compare(id) == 0){
            ASSERT((*iter)->getAttribute(attr.c_str()));
            value = std::string((*iter)->getAttribute(attr.c_str()));
            return value;
        }
    }
    return value;
}

std::string GCRSReadXml::readXmlAttributeValue(cXMLElement* e, std::string tag,
        std::string attr, std::string id) {
    if (e == NULL)
        return "";
    std::string eTag = e->getTagName();
    if (eTag.compare(tag) == 0) {
        if (id.compare("") == 0) {
            ASSERT(e->getAttribute(attr.c_str()));
            std::string attrV = std::string(e->getAttribute(attr.c_str()));
            this->listAttributes.push_back(attrV);
            return "";
        } else {
            ASSERT(e->getAttribute("id"));
            std::string eid = e->getAttribute("id");
            if (eid.compare(id) == 0) {
                ASSERT(e->getAttribute(attr.c_str()));
                return e->getAttribute(attr.c_str());
            }
        }
    }

    cXMLElementList list = e->getChildren();
    std::string result = "";
    for (cXMLElementList::const_iterator i = list.begin(); i != list.end();
            ++i) {
        result = this->readXmlAttributeValue(*i, tag, attr, id);
        if (result.compare("") != 0)
            return result;
    }
    return result;
}
