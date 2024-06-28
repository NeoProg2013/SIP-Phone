#ifndef _SIP_VIA_HDR_H_
#define _SIP_VIA_HDR_H_
#include "global-env.hpp"
#include "sip-param.hpp"


class sip_via_hdr_t {
//
// public virtual API. Only virtual methods and ctors
public:
    sip_via_hdr_t() {}
//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
    int parse(const char* data, int data_size);
    std::string to_string() const;
    void clear();

//
// protected API. Only non-virtual methods
protected:
    int parse_protocol(const char* data, int data_size);
    int parse_by(const char* data, int data_size);

//
// public static API. Only static methods
public:

//
// protected static API. Only static methods
protected:

protected:
    uint16_t m_port                     {0};
    std::string m_host;
    std::list<sip_param_t> m_param_list;
};


#endif // _SIP_VIA_HDR_H_