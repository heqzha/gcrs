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

#ifndef GCRSBASECOMCOLLECTPRINTOUT_H_
#define GCRSBASECOMCOLLECTPRINTOUT_H_
#include "tinyxml.h"
#include <string>

#define RESULT_PATH "results/"
class GCRSBaseComCollectPrintOut {
public:
    GCRSBaseComCollectPrintOut();
    GCRSBaseComCollectPrintOut(std::string protocol);
    virtual ~GCRSBaseComCollectPrintOut();

    TiXmlElement* addElement(std::string name, std::string context, TiXmlElement* parentElement);
    TiXmlElement* addElement(std::string elemntName, TiXmlElement* parentElement);
    void addContent(TiXmlElement* element, std::string strContent);
    void setElementAttribute(TiXmlElement* element, std::string attrName, std::string attrValue);

    void PrintOut();

    TiXmlElement* getRootElement(){
        return this->m_rootElement;
    }
protected:
    std::string m_ProtocolName;
    TiXmlDocument* m_Document;
    TiXmlElement* m_rootElement;

};

#endif /* GCRSBASECOMCOLLECTPRINTOUT_H_ */
