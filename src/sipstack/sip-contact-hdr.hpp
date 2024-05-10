#ifndef _SIP_CONTACT_HDR_H_
#define _SIP_CONTACT_HDR_H_
#include "project-base.hpp"
#include "sip-param.hpp"
#include "sip-uri.hpp"


class sip_contact_hdr_t {
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
    std::string m_display_name;
    sip_uri_t m_uri;
    std::list<sip_param_t> m_param_list;
};

typedef sip_contact_hdr_t sip_to_hdr_t;
typedef sip_contact_hdr_t sip_from_hdr_t;


#endif // _SIP_CONTACT_HDR_H_