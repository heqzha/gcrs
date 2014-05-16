//
// Generated file, do not edit! Created by opp_msgc 4.4 from src/base/pkt/GCRSBaseNetPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GCRSBaseNetPkt_m.h"

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




Register_Class(GCRSBaseNetPkt);

GCRSBaseNetPkt::GCRSBaseNetPkt(const char *name, int kind) : ::NetwPkt(name,kind)
{
    this->vinOriginSrc_var = -1;
    this->vinForwardSrc_var = -1;
    this->vinDest_var = -1;
    this->priority_var = 3;
    this->channelNumber_var = 0;
    this->speedMaxSrc_var = 0;
    this->speedMaxForwarding_var = 0;
    this->nin_var = -1;
    this->hops_var = 0;
    this->timeTtl_var = 0.0f;
    this->timestampForwarding_var = 0.0f;
    this->timestamp_var = 0.0f;
    this->version_var = 0;
}

GCRSBaseNetPkt::GCRSBaseNetPkt(const GCRSBaseNetPkt& other) : ::NetwPkt(other)
{
    copy(other);
}

GCRSBaseNetPkt::~GCRSBaseNetPkt()
{
}

GCRSBaseNetPkt& GCRSBaseNetPkt::operator=(const GCRSBaseNetPkt& other)
{
    if (this==&other) return *this;
    ::NetwPkt::operator=(other);
    copy(other);
    return *this;
}

void GCRSBaseNetPkt::copy(const GCRSBaseNetPkt& other)
{
    this->vinOriginSrc_var = other.vinOriginSrc_var;
    this->vinForwardSrc_var = other.vinForwardSrc_var;
    this->vinDest_var = other.vinDest_var;
    this->priority_var = other.priority_var;
    this->channelNumber_var = other.channelNumber_var;
    this->locSrc_var = other.locSrc_var;
    this->locForwad_var = other.locForwad_var;
    this->speedSrc_var = other.speedSrc_var;
    this->speedForwad_var = other.speedForwad_var;
    this->speedMaxSrc_var = other.speedMaxSrc_var;
    this->speedMaxForwarding_var = other.speedMaxForwarding_var;
    this->nin_var = other.nin_var;
    this->hops_var = other.hops_var;
    this->timeTtl_var = other.timeTtl_var;
    this->timestampForwarding_var = other.timestampForwarding_var;
    this->timestamp_var = other.timestamp_var;
    this->version_var = other.version_var;
}

void GCRSBaseNetPkt::parsimPack(cCommBuffer *b)
{
    ::NetwPkt::parsimPack(b);
    doPacking(b,this->vinOriginSrc_var);
    doPacking(b,this->vinForwardSrc_var);
    doPacking(b,this->vinDest_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->channelNumber_var);
    doPacking(b,this->locSrc_var);
    doPacking(b,this->locForwad_var);
    doPacking(b,this->speedSrc_var);
    doPacking(b,this->speedForwad_var);
    doPacking(b,this->speedMaxSrc_var);
    doPacking(b,this->speedMaxForwarding_var);
    doPacking(b,this->nin_var);
    doPacking(b,this->hops_var);
    doPacking(b,this->timeTtl_var);
    doPacking(b,this->timestampForwarding_var);
    doPacking(b,this->timestamp_var);
    doPacking(b,this->version_var);
}

void GCRSBaseNetPkt::parsimUnpack(cCommBuffer *b)
{
    ::NetwPkt::parsimUnpack(b);
    doUnpacking(b,this->vinOriginSrc_var);
    doUnpacking(b,this->vinForwardSrc_var);
    doUnpacking(b,this->vinDest_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->channelNumber_var);
    doUnpacking(b,this->locSrc_var);
    doUnpacking(b,this->locForwad_var);
    doUnpacking(b,this->speedSrc_var);
    doUnpacking(b,this->speedForwad_var);
    doUnpacking(b,this->speedMaxSrc_var);
    doUnpacking(b,this->speedMaxForwarding_var);
    doUnpacking(b,this->nin_var);
    doUnpacking(b,this->hops_var);
    doUnpacking(b,this->timeTtl_var);
    doUnpacking(b,this->timestampForwarding_var);
    doUnpacking(b,this->timestamp_var);
    doUnpacking(b,this->version_var);
}

long GCRSBaseNetPkt::getVinOriginSrc() const
{
    return vinOriginSrc_var;
}

void GCRSBaseNetPkt::setVinOriginSrc(long vinOriginSrc)
{
    this->vinOriginSrc_var = vinOriginSrc;
}

long GCRSBaseNetPkt::getVinForwardSrc() const
{
    return vinForwardSrc_var;
}

void GCRSBaseNetPkt::setVinForwardSrc(long vinForwardSrc)
{
    this->vinForwardSrc_var = vinForwardSrc;
}

long GCRSBaseNetPkt::getVinDest() const
{
    return vinDest_var;
}

void GCRSBaseNetPkt::setVinDest(long vinDest)
{
    this->vinDest_var = vinDest;
}

int GCRSBaseNetPkt::getPriority() const
{
    return priority_var;
}

void GCRSBaseNetPkt::setPriority(int priority)
{
    this->priority_var = priority;
}

int GCRSBaseNetPkt::getChannelNumber() const
{
    return channelNumber_var;
}

void GCRSBaseNetPkt::setChannelNumber(int channelNumber)
{
    this->channelNumber_var = channelNumber;
}

Coord& GCRSBaseNetPkt::getLocSrc()
{
    return locSrc_var;
}

void GCRSBaseNetPkt::setLocSrc(const Coord& locSrc)
{
    this->locSrc_var = locSrc;
}

Coord& GCRSBaseNetPkt::getLocForwad()
{
    return locForwad_var;
}

void GCRSBaseNetPkt::setLocForwad(const Coord& locForwad)
{
    this->locForwad_var = locForwad;
}

Coord& GCRSBaseNetPkt::getSpeedSrc()
{
    return speedSrc_var;
}

void GCRSBaseNetPkt::setSpeedSrc(const Coord& speedSrc)
{
    this->speedSrc_var = speedSrc;
}

Coord& GCRSBaseNetPkt::getSpeedForwad()
{
    return speedForwad_var;
}

void GCRSBaseNetPkt::setSpeedForwad(const Coord& speedForwad)
{
    this->speedForwad_var = speedForwad;
}

double GCRSBaseNetPkt::getSpeedMaxSrc() const
{
    return speedMaxSrc_var;
}

void GCRSBaseNetPkt::setSpeedMaxSrc(double speedMaxSrc)
{
    this->speedMaxSrc_var = speedMaxSrc;
}

double GCRSBaseNetPkt::getSpeedMaxForwarding() const
{
    return speedMaxForwarding_var;
}

void GCRSBaseNetPkt::setSpeedMaxForwarding(double speedMaxForwarding)
{
    this->speedMaxForwarding_var = speedMaxForwarding;
}

long GCRSBaseNetPkt::getNin() const
{
    return nin_var;
}

void GCRSBaseNetPkt::setNin(long nin)
{
    this->nin_var = nin;
}

long GCRSBaseNetPkt::getHops() const
{
    return hops_var;
}

void GCRSBaseNetPkt::setHops(long hops)
{
    this->hops_var = hops;
}

simtime_t GCRSBaseNetPkt::getTimeTtl() const
{
    return timeTtl_var;
}

void GCRSBaseNetPkt::setTimeTtl(simtime_t timeTtl)
{
    this->timeTtl_var = timeTtl;
}

simtime_t GCRSBaseNetPkt::getTimestampForwarding() const
{
    return timestampForwarding_var;
}

void GCRSBaseNetPkt::setTimestampForwarding(simtime_t timestampForwarding)
{
    this->timestampForwarding_var = timestampForwarding;
}

simtime_t GCRSBaseNetPkt::getTimestamp() const
{
    return timestamp_var;
}

void GCRSBaseNetPkt::setTimestamp(simtime_t timestamp)
{
    this->timestamp_var = timestamp;
}

long GCRSBaseNetPkt::getVersion() const
{
    return version_var;
}

void GCRSBaseNetPkt::setVersion(long version)
{
    this->version_var = version;
}

class GCRSBaseNetPktDescriptor : public cClassDescriptor
{
  public:
    GCRSBaseNetPktDescriptor();
    virtual ~GCRSBaseNetPktDescriptor();

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

Register_ClassDescriptor(GCRSBaseNetPktDescriptor);

GCRSBaseNetPktDescriptor::GCRSBaseNetPktDescriptor() : cClassDescriptor("GCRSBaseNetPkt", "NetwPkt")
{
}

GCRSBaseNetPktDescriptor::~GCRSBaseNetPktDescriptor()
{
}

bool GCRSBaseNetPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GCRSBaseNetPkt *>(obj)!=NULL;
}

const char *GCRSBaseNetPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GCRSBaseNetPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 17+basedesc->getFieldCount(object) : 17;
}

unsigned int GCRSBaseNetPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<17) ? fieldTypeFlags[field] : 0;
}

const char *GCRSBaseNetPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "vinOriginSrc",
        "vinForwardSrc",
        "vinDest",
        "priority",
        "channelNumber",
        "locSrc",
        "locForwad",
        "speedSrc",
        "speedForwad",
        "speedMaxSrc",
        "speedMaxForwarding",
        "nin",
        "hops",
        "timeTtl",
        "timestampForwarding",
        "timestamp",
        "version",
    };
    return (field>=0 && field<17) ? fieldNames[field] : NULL;
}

int GCRSBaseNetPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "vinOriginSrc")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "vinForwardSrc")==0) return base+1;
    if (fieldName[0]=='v' && strcmp(fieldName, "vinDest")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelNumber")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "locSrc")==0) return base+5;
    if (fieldName[0]=='l' && strcmp(fieldName, "locForwad")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "speedSrc")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "speedForwad")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "speedMaxSrc")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "speedMaxForwarding")==0) return base+10;
    if (fieldName[0]=='n' && strcmp(fieldName, "nin")==0) return base+11;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+12;
    if (fieldName[0]=='t' && strcmp(fieldName, "timeTtl")==0) return base+13;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestampForwarding")==0) return base+14;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+15;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+16;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GCRSBaseNetPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "long",
        "long",
        "long",
        "int",
        "int",
        "Coord",
        "Coord",
        "Coord",
        "Coord",
        "double",
        "double",
        "long",
        "long",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "long",
    };
    return (field>=0 && field<17) ? fieldTypeStrings[field] : NULL;
}

const char *GCRSBaseNetPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GCRSBaseNetPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GCRSBaseNetPkt *pp = (GCRSBaseNetPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GCRSBaseNetPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GCRSBaseNetPkt *pp = (GCRSBaseNetPkt *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVinOriginSrc());
        case 1: return long2string(pp->getVinForwardSrc());
        case 2: return long2string(pp->getVinDest());
        case 3: return long2string(pp->getPriority());
        case 4: return long2string(pp->getChannelNumber());
        case 5: {std::stringstream out; out << pp->getLocSrc(); return out.str();}
        case 6: {std::stringstream out; out << pp->getLocForwad(); return out.str();}
        case 7: {std::stringstream out; out << pp->getSpeedSrc(); return out.str();}
        case 8: {std::stringstream out; out << pp->getSpeedForwad(); return out.str();}
        case 9: return double2string(pp->getSpeedMaxSrc());
        case 10: return double2string(pp->getSpeedMaxForwarding());
        case 11: return long2string(pp->getNin());
        case 12: return long2string(pp->getHops());
        case 13: return double2string(pp->getTimeTtl());
        case 14: return double2string(pp->getTimestampForwarding());
        case 15: return double2string(pp->getTimestamp());
        case 16: return long2string(pp->getVersion());
        default: return "";
    }
}

bool GCRSBaseNetPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GCRSBaseNetPkt *pp = (GCRSBaseNetPkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setVinOriginSrc(string2long(value)); return true;
        case 1: pp->setVinForwardSrc(string2long(value)); return true;
        case 2: pp->setVinDest(string2long(value)); return true;
        case 3: pp->setPriority(string2long(value)); return true;
        case 4: pp->setChannelNumber(string2long(value)); return true;
        case 9: pp->setSpeedMaxSrc(string2double(value)); return true;
        case 10: pp->setSpeedMaxForwarding(string2double(value)); return true;
        case 11: pp->setNin(string2long(value)); return true;
        case 12: pp->setHops(string2long(value)); return true;
        case 13: pp->setTimeTtl(string2double(value)); return true;
        case 14: pp->setTimestampForwarding(string2double(value)); return true;
        case 15: pp->setTimestamp(string2double(value)); return true;
        case 16: pp->setVersion(string2long(value)); return true;
        default: return false;
    }
}

const char *GCRSBaseNetPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "Coord",
        "Coord",
        "Coord",
        "Coord",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<17) ? fieldStructNames[field] : NULL;
}

void *GCRSBaseNetPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GCRSBaseNetPkt *pp = (GCRSBaseNetPkt *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getLocSrc()); break;
        case 6: return (void *)(&pp->getLocForwad()); break;
        case 7: return (void *)(&pp->getSpeedSrc()); break;
        case 8: return (void *)(&pp->getSpeedForwad()); break;
        default: return NULL;
    }
}


