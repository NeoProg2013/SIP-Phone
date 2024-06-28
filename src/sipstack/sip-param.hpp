#ifndef _SIP_PARAM_H_
#define _SIP_PARAM_H_
#include "global-env.hpp"


class sip_param_t {
//
// public virtual API. Only virtual methods and ctors
public:
	sip_param_t() {}
    sip_param_t(const std::string& n, const std::string& v) : m_name(n), m_value(v) {}

//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
    int parse(const char* data, int data_size);
    void clear();
    
    std::string to_string() const        { return m_name + "=" + m_value; }
    const std::string& get_name() const  { return m_name;  }
    const std::string& get_value() const { return m_value; }

//
// protected API. Only non-virtual methods
protected:

//
// public static API. Only static methods
public:
    static int list_parse(const char* data, int data_size, std::list<sip_param_t>* param_list);
    static int list_parse(const char* data, int data_size, std::list<sip_param_t>* param_list, std::function<int(char, int*)> f);
    static std::string list_to_string(const std::list<sip_param_t>& param_list, char first_sep = ';', char sep = ';');


//
// protected static API. Only static methods
protected:

protected:
    std::string m_name;
    std::string m_value;
};


#endif // _SIP_PARAM_H_