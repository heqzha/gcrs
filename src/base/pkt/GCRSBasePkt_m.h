//
// Generated file, do not edit! Created by opp_msgc 4.4 from src/base/pkt/GCRSBasePkt.msg.
//

#ifndef _GCRSBASEPKT_M_H_
#define _GCRSBASEPKT_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{

// }}



/**
 * Class generated from <tt>src/base/pkt/GCRSBasePkt.msg</tt> by opp_msgc.
 * <pre>
 * packet GCRSBasePkt {
 *     
 *     int priorityClass;
 * }
 * </pre>
 */
class GCRSBasePkt : public ::cPacket
{
  protected:
    int priorityClass_var;

  private:
    void copy(const GCRSBasePkt& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GCRSBasePkt&);

  public:
    GCRSBasePkt(const char *name=NULL, int kind=0);
    GCRSBasePkt(const GCRSBasePkt& other);
    virtual ~GCRSBasePkt();
    GCRSBasePkt& operator=(const GCRSBasePkt& other);
    virtual GCRSBasePkt *dup() const {return new GCRSBasePkt(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getPriorityClass() const;
    virtual void setPriorityClass(int priorityClass);
};

inline void doPacking(cCommBuffer *b, GCRSBasePkt& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, GCRSBasePkt& obj) {obj.parsimUnpack(b);}


#endif // _GCRSBASEPKT_M_H_
