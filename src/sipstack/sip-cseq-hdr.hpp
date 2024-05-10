#ifndef _SIP_CSEQ_HDR_H_
#define _SIP_CSEQ_HDR_H_
#include "project-base.hpp"


class sip_cseq_hdr_t {
//
// public virtual API. Only virtual methods and ctors
public:

//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
    int parse(const char* data, int data_size);
    void clear();

//
// protected API. Only non-virtual methods
protected:

//
// public static API. Only static methods
public:

//
// protected static API. Only static methods
protected:

protected:
    int m_seq               {-1};
    std::string m_method;
};


#endif // _SIP_CSEQ_HDR_H_