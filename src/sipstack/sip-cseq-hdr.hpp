#ifndef _SIP_CSEQ_HDR_H_
#define _SIP_CSEQ_HDR_H_
#include "global-env.hpp"


class sip_cseq_hdr_t {
//
// public virtual API. Only virtual methods and ctors
public:
    sip_cseq_hdr_t() {}
    sip_cseq_hdr_t(int cseq) : m_cseq(cseq) {}
    sip_cseq_hdr_t(int cseq, const std::string& method) : m_cseq(cseq), m_method(method) {}

//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
    int parse(const char* data, int data_size);
    std::string to_string() const;
    void clear();

    void set_cseq(int cseq)                    { m_cseq = cseq;     }
    void set_method(const std::string& method) { m_method = method; }

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
    int m_cseq               {-1};
    std::string m_method;
};


#endif // _SIP_CSEQ_HDR_H_