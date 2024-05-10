#ifndef _SIP_HDR_H_
#define _SIP_HDR_H_
#include "project-base.hpp"


class sip_hdr_t {
public:
    int parse(const char* data, int data_size);
    void reset();

    const std::string& get_name() const  { return m_name;  }
    const std::string& get_value() const { return m_value; }

protected:
    std::string m_name;
    std::string m_value;
};

class sip_from_hdr_t {
public:
    int parse(const char* data, int data_size);
    void reset();

protected:
    std::string m_display_name;
    //CSipUri	m_clsUri;
};


#endif // _SIP_HDR_H_