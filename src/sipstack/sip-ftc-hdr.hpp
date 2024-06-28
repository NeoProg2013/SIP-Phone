#ifndef _SIP_FTC_HDR_H_
#define _SIP_FTC_HDR_H_
#include "global-env.hpp"
#include "sip-hdr.hpp"
#include "sip-param.hpp"
#include "sip-uri.hpp"


// From, To, Contact headers

class sip_ftc_hdr_t {
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
    std::string to_string() const;
    void clear();

    void set_display_name(const std::string& v) { m_display_name = v;               }
    void set_uri(const std::string& v)          { m_uri.parse(v.c_str(), v.size()); }
    void set_uri(const sip_uri_t& v)            { m_uri = v;                        }

    void add_param(const std::string& n, const std::string& v);

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
    sip_uri_t m_uri;
    std::string m_display_name;
    std::list<sip_param_t> m_param_list;
};

typedef sip_ftc_hdr_t sip_contact_hdr_t;
typedef sip_ftc_hdr_t sip_to_hdr_t;
typedef sip_ftc_hdr_t sip_from_hdr_t;


#endif // _SIP_FTC_HDR_H_