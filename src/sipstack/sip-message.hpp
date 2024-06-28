#ifndef _SIP_MESSAGE_H_
#define _SIP_MESSAGE_H_
#include "global-env.hpp"
#include "sip-hdr.hpp"
#include "sip-via-hdr.hpp"
#include "sip-ftc-hdr.hpp"
#include "sip-cseq-hdr.hpp"
#include "sip-credential-hdr.hpp"
#include "sip-codes.hpp"

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
    std::string to_string() const;
    void clear();

    void add_header(const std::string& name, const std::string& value);

    void set_method(const std::string& m)        { m_sip_method = m;                         }
    void set_req_uri(const std::string& uri)     { m_req_uri.parse(uri.c_str(), uri.size()); }
    void set_req_uri(const sip_uri_t& uri)       { m_req_uri = uri;                          }

	sip_hdr_t& mutable_call_id_hdr()             { return m_call_id;                         }
    sip_from_hdr_t& mutable_from_hdr()           { return m_from_hdr;                        }
    sip_to_hdr_t& mutable_to_hdr()               { return m_to_hdr;                          }
    sip_cseq_hdr_t& mutable_cseq_hdr()           { return m_cseq_hdr;                        }

protected:
    int parse_request_line(const char* data, int data_size);
    int parse_status_line(const char* data, int data_size);
    int parse_contacts(const char* data, int data_size);
    int parse_credentials(const char* data, int data_size);
    int parse_via(const char* data, int data_size);

protected:
    sip_uri_t   m_req_uri;
    std::string m_sip_method;
    int m_status_code                       {0};
    std::string m_reason;

    std::string m_content_data;

    sip_hdr_t m_call_id;
    sip_hdr_t m_max_forwards;
    sip_from_hdr_t m_from_hdr;
    sip_to_hdr_t m_to_hdr;
    sip_cseq_hdr_t m_cseq_hdr;
    std::list<sip_contact_hdr_t> m_contact_hdr_list;
    std::list<sip_credential_hdr_t> m_credential_hdr_list;
    std::list<sip_via_hdr_t> m_via_list;
    std::list<sip_hdr_t> m_sip_hdr_list;
};


#endif // _SIP_MESSAGE_H_
