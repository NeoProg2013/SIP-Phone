#ifndef _SIP_CREDENTIAL_H_
#define _SIP_CREDENTIAL_H_
#include "project-base.hpp"
#include "sip-param.hpp"


class sip_credential_t {
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
    int parse_params(const char* data, int data_size);
    std::string dequote_string(const std::string& s) const;
//
// public static API. Only static methods
public:

//
// protected static API. Only static methods
protected:

protected:
    std::string	m_type;
    std::string	m_user_name;
    std::string	m_realm;
    std::string	m_nonce;
    std::string	m_uri;
    std::string	m_response;
    std::string	m_algorithm;
    std::string	m_cnonce;
    std::string	m_opaque;
    std::string	m_qop;
    std::string	m_nonce_count;
    std::list<sip_param_t> m_param_list;
};


#endif // _SIP_CREDENTIAL_H_