#ifndef _SIP_URI_H_
#define _SIP_URI_H_
#include "project-base.hpp"
#include "sip-param.hpp"


class sip_uri_t {
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
    int parse_protocol(const char* data, int data_size);
    int parse_user(const char* data, int data_size);
    int parse_host(const char* data, int data_size);

//
// public static API. Only static methods
public:

//
// protected static API. Only static methods
protected:

protected:
    std::string	m_protocol;
    std::string	m_user;
    std::string	m_host;
    int m_port                              {-1};
    std::list<sip_param_t> m_uri_param_list;
    std::list<sip_param_t> m_hdr_list;
};


#endif // _SIP_URI_H_