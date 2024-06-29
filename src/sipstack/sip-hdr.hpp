#ifndef _SIP_HDR_H_
#define _SIP_HDR_H_
#include "global-env.hpp"
#include "sip-ftc-hdr.hpp"


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
    virtual int parse(const char* data, int data_size);
    virtual std::string to_string() const;
    virtual void clear();

	void set_name(const std::string& n)  { m_name = n;             }
	void set_value(const std::string& v) { m_value = v;            }
    const std::string& get_name() const  { return m_name;          }
    const std::string& get_value() const { return m_value;         }
	bool empty() const                   { return m_value.empty(); }

//
// protected API. Only non-virtual methods
protected:

//
// public static API. Only static methods
public:

//
// protected static API. Only static methods
protected:

//
// fields
protected:
    std::string m_name;
    std::string m_value;
};


#endif // _SIP_HDR_H_