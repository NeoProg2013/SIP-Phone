#ifndef _SIP_MESSAGE_H_
#define _SIP_MESSAGE_H_
#include "project-base.hpp"
#include "sip-hdr.hpp"
#include "sip-contact-hdr.hpp"
#include "sip-cseq-hdr.hpp"


class sip_message_t {
public:
    bool parse(const char* data, uint16_t data_size);

    void print() {
        printf("m_sip_method=%s\r\n", m_sip_method.c_str());
        printf("m_sip_version=%s\r\n", m_sip_version.c_str());
        printf("m_reason_phrase=%s\r\n", m_reason_phrase.c_str());
        printf("m_user_agent=%s\r\n", m_user_agent.c_str());
        printf("m_body=\r\n%s\r\n", m_body.c_str());
        printf("m_status_code=%d\r\n", m_status_code);
        printf("m_max_forwards=%d\r\n", m_max_forwards);
        printf("m_content_data_size=%d\r\n", m_content_data_size);
        printf("m_expires=%d\r\n", m_expires);
    }

protected:
    int parse_request_line(const char* data, int data_size);
    int parse_status_line(const char* data, int data_size);
    int parse_contact(const char* data, int data_size);

protected:
    std::string m_sip_method;
    std::string m_sip_version;
    std::string m_reason_phrase;
    std::string m_user_agent;
	std::string m_call_id;
    std::string m_body;
    std::list<sip_hdr_t> m_sip_hdr_list;
    int m_status_code                       {-1};
    int m_max_forwards                      {-1};
    int m_content_data_size                 {-1};
    int m_expires                           {-1};

    sip_from_hdr_t m_from_hdr;
    sip_to_hdr_t m_to_hdr;
    sip_cseq_hdr_t m_cseq_hdr;
    std::list<sip_contact_hdr_t*> m_contact_hdr_list;
};


#endif // _SIP_MESSAGE_H_