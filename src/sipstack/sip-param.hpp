#ifndef _SIP_PARAM_H_
#define _SIP_PARAM_H_
#include "project-base.hpp"


class sip_param_t {
public:
    int parse(const char* data, int data_size);
    void clear();

    const std::string& get_name() const  { return m_name;  }
    const std::string& get_value() const { return m_value; }

public:
    static int list_param_parse(const char* data, int data_size, std::list<sip_param_t>* param_list);
    static int list_param_parse(const char* data, int data_size, std::list<sip_param_t>* param_list, std::function<int(char, int*)> f);

protected:
    std::string m_name;
    std::string m_value;
};


#endif // _SIP_PARAM_H_