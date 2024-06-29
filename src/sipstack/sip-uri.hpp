#ifndef _SIP_URI_H_
#define _SIP_URI_H_
#include "global-env.hpp"
#include "sip-param.hpp"


class sip_uri_t {
//
// public virtual API. Only virtual methods and ctors
public:
    sip_uri_t() {}
    sip_uri_t(const std::string& uri) { this->parse(uri.c_str(), uri.length()); }
    sip_uri_t(const std::string& user, const std::string& host, int port = 0)
        : m_user(user), m_host(host), m_port(port) {}
//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
    int parse(const char* data, int data_size);
    void clear();
	std::string to_string() const;

	void add_param(const std::string& name, const std::string& value);
	void add_header(const std::string& name, const std::string& value);

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
    std::string	m_user;
    std::string	m_host;
    int m_port                              {0};
    std::list<sip_param_t> m_uri_param_list;
    std::list<sip_param_t> m_hdr_list;
};


#endif // _SIP_URI_H_