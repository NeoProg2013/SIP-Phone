#ifndef _SIP_MESSAGE_H_
#define _SIP_MESSAGE_H_
#include "project-base.hpp"
#include "sip-hdr.hpp"
#include "sip-contact-hdr.hpp"
#include "sip-cseq-hdr.hpp"
#include "sip-credential-hdr.hpp"

static const int SIP_MESSAGE_MAX_LEN = 8192;
static const int SIP_TAG_MAX_SIZE = 21;
static const int SIP_BRANCH_MAX_SIZE = 61;
static const int SIP_CALL_ID_NAME_MAX_SIZE = 51;

static const char* const VIA_PREFIX = "z9hG4bK";
static const int VIA_PREFIX_LEN = 7;

static const char* const SIP_PROTOCOL = "sip";
static const char* const SIP_VERSION = "SIP/2.0";

static const char* const SIP_TRANSPORT = "transport";
static const char* const SIP_RECEIVED = "received";
static const char* const SIP_RPORT = "rport";

static const char* const SIP_TRANSPORT_TCP_S  = "tcp";
static const char* const SIP_TRANSPORT_TLS_S  = "tls";

static const char* const SIP_METHOD_INVITE    = "INVITE";
static const char* const SIP_METHOD_ACK       = "ACK";
static const char* const SIP_METHOD_CANCEL    = "CANCEL";
static const char* const SIP_METHOD_BYE       = "BYE";
static const char* const SIP_METHOD_REGISTER  = "REGISTER";
static const char* const SIP_METHOD_PRACK     = "PRACK";
static const char* const SIP_METHOD_REFER     = "REFER";
static const char* const SIP_METHOD_INFO      = "INFO";
static const char* const SIP_METHOD_NOTIFY    = "NOTIFY";
static const char* const SIP_METHOD_MESSAGE   = "MESSAGE";
static const char* const SIP_METHOD_OPTIONS   = "OPTIONS";
static const char* const SIP_METHOD_SUBSCRIBE = "SUBSCRIBE";

static const char* const SIP_TAG              = "tag";
static const char* const SIP_BRANCH           = "branch";

enum sip_transport_t {
    SIP_TRANSPORT_UDP,
    //SIP_TRANSPORT_TCP,
    //SIP_TRANSPORT_TLS
};

#define S_SIP_UDP		"UDP"
#define S_SIP_TCP		"TCP"
#define S_SIP_TLS		"TLS"

class sip_message_t {
public:
    bool parse(const char* data, uint16_t data_size);
    void clear();

    void add_header(const std::string& name, const std::string& value);

    void set_method(const std::string& m)        { m_sip_method = m;                         }
    void set_call_id(const std::string& call_id) { m_call_id = call_id;                      }
    void set_transport(sip_transport_t t)        { m_transport = t;                          }
    void set_req_uri(const std::string& uri)     { m_req_uri.parse(uri.c_str(), uri.size()); }
    void set_req_uri(const sip_uri_t& uri)       { m_req_uri = uri;                          }

    sip_from_hdr_t& mutable_from_hdr()           { return m_from_hdr;                        }
    sip_to_hdr_t& mutable_to_hdr()               { return m_to_hdr;                          }
    sip_cseq_hdr_t& mutable_cseq_hdr()           { return m_cseq_hdr;                        }

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
    int parse_contacts(const char* data, int data_size);
    int parse_credentials(const char* data, int data_size);

protected:
    std::string m_sip_method;
    std::string m_sip_version;
    std::string m_reason_phrase;
    std::string m_user_agent;
	std::string m_call_id;
    std::string m_body;
    int m_status_code                       {-1};
    int m_max_forwards                      {-1};
    int m_content_data_size                 {-1};
    int m_expires                           {-1};
    sip_transport_t m_transport             {SIP_TRANSPORT_UDP};

    sip_from_hdr_t m_from_hdr;
    sip_to_hdr_t m_to_hdr;
    sip_cseq_hdr_t m_cseq_hdr;
    std::list<sip_contact_hdr_t> m_contact_hdr_list;
    std::list<sip_credential_hdr_t> m_credential_hdr_list;

    sip_uri_t m_req_uri;

    std::list<sip_hdr_t> m_sip_hdr_list;
};


#endif // _SIP_MESSAGE_H_