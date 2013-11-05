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

#include "GCRSBaseComCollectPrintOut.h"
#include "omnetpp.h"

GCRSBaseComCollectPrintOut::GCRSBaseComCollectPrintOut(){
/*    this->m_Document = NULL;
    this->m_rootElement = NULL;*/
}
GCRSBaseComCollectPrintOut::GCRSBaseComCollectPrintOut(std::string protocol) {
    try {
        this->m_ProtocolName = protocol;
        std::string fullPath = RESULT_PATH+protocol+".xml";
        this->m_Document = new TiXmlDocument(fullPath.c_str());
        this->m_rootElement = new TiXmlElement("Protocol");
        this->m_rootElement->SetAttribute("Name", this->m_ProtocolName.c_str());
        this->m_Document->LinkEndChild(this->m_rootElement);
    } catch (std::string& e) {
        EV<< "ERROR:" << e << endl;
    }
}

GCRSBaseComCollectPrintOut::~GCRSBaseComCollectPrintOut() {
/*    if (this->m_rootElement != NULL) {
        delete this->m_rootElement;
    }*/
}

TiXmlElement* GCRSBaseComCollectPrintOut::addElement(std::string name, std::string context, TiXmlElement* parentElement){
    TiXmlElement* element = this->addElement(name,parentElement);
    this->addContent(element,context);
    return element;
}

TiXmlElement* GCRSBaseComCollectPrintOut::addElement(std::string elemntName,
        TiXmlElement* parentElement) {
    try {
        if (parentElement == NULL)
            return NULL;
        TiXmlElement* element = new TiXmlElement(elemntName.c_str());
        parentElement->LinkEndChild(element);
        return element;
    } catch (std::string& e) {
        EV<< "ERROR:" << e << endl;
        return NULL;
    }
}

void GCRSBaseComCollectPrintOut::addContent(TiXmlElement* element,
        std::string strContent) {
    try{
        if(element == NULL)return;
        TiXmlText* content = new TiXmlText(strContent.c_str());
        element->LinkEndChild(content);
    }catch (std::string& e) {
        EV<< "ERROR:" << e << endl;
    }
}

void GCRSBaseComCollectPrintOut::setElementAttribute(TiXmlElement* element,
        std::string attrName, std::string attrValue) {
    try{
        if(element == NULL)return;
        element->SetAttribute(attrName.c_str(), attrValue.c_str());
    }catch (std::string& e) {
        EV<< "ERROR:" << e << endl;
    }
}

void GCRSBaseComCollectPrintOut::PrintOut(){
    if(this->m_Document->Error()){
        EV << "Error in "<< this->m_Document->Value() << ": " << this->m_Document->ErrorDesc()<<endl;
        return;
    }
    this->m_Document->SaveFile();
}
