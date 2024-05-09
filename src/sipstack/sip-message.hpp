#ifndef _SIP_MESSAGE_H_
#define _SIP_MESSAGE_H_
#include "project-base.hpp"
#include "sip-hdr.hpp"


class sip_message_t {
public:
    bool parse(const char* data, uint16_t data_size);

protected:
    int parse_request_line(const char* data, int data_size);
    int parse_status_line(const char* data, int data_size);

protected:
    std::string m_sip_method;
    std::string m_sip_version;
    std::string m_reason_phrase;
    std::string m_user_agent;
    std::string m_body;
    std::list<sip_hdr_t> m_sip_hdr_list;
    int m_status_code                       {0};
    int m_max_forwards                      {0};
    int m_content_data_size                 {0};
    int m_expires                           {0};
};


#endif // _SIP_MESSAGE_H_