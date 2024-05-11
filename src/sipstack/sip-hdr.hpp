#ifndef _SIP_HDR_H_
#define _SIP_HDR_H_
#include "project-base.hpp"


class sip_hdr_t {
//
// public virtual API. Only virtual methods and ctors
public:
	sip_hdr_t() {}
    sip_hdr_t(const std::string& n, const std::string& v) : m_name(n), m_value(v) {}
//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
    int parse(const char* data, int data_size);
    void clear();

    const std::string& get_name() const  { return m_name;  }
    const std::string& get_value() const { return m_value; }
    std::string to_string() const { return get_name() + ": " + get_value(); }

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
    std::string m_name;
    std::string m_value;
};


#endif // _SIP_HDR_H_