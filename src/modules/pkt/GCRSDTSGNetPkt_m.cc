//
// Generated file, do not edit! Created by opp_msgc 4.4 from src/modules/pkt/GCRSDTSGNetPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GCRSDTSGNetPkt_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(GCRSDTSGNetPkt);

GCRSDTSGNetPkt::GCRSDTSGNetPkt(const char *name, int kind) : ::GCRSBaseNetPkt(name,kind)
{
    this->preStableFlg_var = true;
}

GCRSDTSGNetPkt::GCRSDTSGNetPkt(const GCRSDTSGNetPkt& other) : ::GCRSBaseNetPkt(other)
{
    copy(other);
}

GCRSDTSGNetPkt::~GCRSDTSGNetPkt()
{
}

GCRSDTSGNetPkt& GCRSDTSGNetPkt::operator=(const GCRSDTSGNetPkt& other)
{
    if (this==&other) return *this;
    ::GCRSBaseNetPkt::operator=(other);
    copy(other);
    return *this;
}

void GCRSDTSGNetPkt::copy(const GCRSDTSGNetPkt& other)
{
    this->preStableFlg_var = other.preStableFlg_var;
}

void GCRSDTSGNetPkt::parsimPack(cCommBuffer *b)
{
    ::GCRSBaseNetPkt::parsimPack(b);
    doPacking(b,this->preStableFlg_var);
}

void GCRSDTSGNetPkt::parsimUnpack(cCommBuffer *b)
{
    ::GCRSBaseNetPkt::parsimUnpack(b);
    doUnpacking(b,this->preStableFlg_var);
}

bool GCRSDTSGNetPkt::getPreStableFlg() const
{
    return preStableFlg_var;
}

void GCRSDTSGNetPkt::setPreStableFlg(bool preStableFlg)
{
    this->preStableFlg_var = preStableFlg;
}

class GCRSDTSGNetPktDescriptor : public cClassDescriptor
{
  public:
    GCRSDTSGNetPktDescriptor();
    virtual ~GCRSDTSGNetPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(GCRSDTSGNetPktDescriptor);

GCRSDTSGNetPktDescriptor::GCRSDTSGNetPktDescriptor() : cClassDescriptor("GCRSDTSGNetPkt", "GCRSBaseNetPkt")
{
}

GCRSDTSGNetPktDescriptor::~GCRSDTSGNetPktDescriptor()
{
}

bool GCRSDTSGNetPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GCRSDTSGNetPkt *>(obj)!=NULL;
}

const char *GCRSDTSGNetPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GCRSDTSGNetPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int GCRSDTSGNetPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GCRSDTSGNetPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "preStableFlg",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int GCRSDTSGNetPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "preStableFlg")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GCRSDTSGNetPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *GCRSDTSGNetPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int GCRSDTSGNetPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GCRSDTSGNetPkt *pp = (GCRSDTSGNetPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GCRSDTSGNetPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GCRSDTSGNetPkt *pp = (GCRSDTSGNetPkt *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getPreStableFlg());
        default: return "";
    }
}

bool GCRSDTSGNetPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GCRSDTSGNetPkt *pp = (GCRSDTSGNetPkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setPreStableFlg(string2bool(value)); return true;
        default: return false;
    }
}

const char *GCRSDTSGNetPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *GCRSDTSGNetPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GCRSDTSGNetPkt *pp = (GCRSDTSGNetPkt *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


