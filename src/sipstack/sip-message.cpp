#include "global-env.hpp"
#include "sip-message.hpp"


//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
bool sip_message_t::parse(const char* data, uint16_t data_size) {
    if (!data || data_size <= 4) {
        return false;
    }

	int cur_pos = strncmp(data, "SIP/", 4) ? parse_request_line(data, data_size) : parse_status_line(data, data_size);
    if (cur_pos == -1) {
        return false;
    }

	int content_data_size = 0;
    while (cur_pos < data_size) {
        sip_hdr_t sip_hdr;
        int idx = sip_hdr.parse(data + cur_pos, data_size - cur_pos);
        if (idx == -1) {
            return false;
        }
        cur_pos += idx;

		printf("process hdr: %s, cur_pos=%d\r\n", sip_hdr.to_string().c_str(), cur_pos);
        if (sip_hdr.get_name().empty()) {
            break;
        }


        const char* const hdr_name = sip_hdr.get_name().c_str();
        const char* const hdr_value = sip_hdr.get_value().c_str();
        int hdr_value_size = sip_hdr.get_value().size();

        if (!global_env::strcasecmp(hdr_name, "Via")) {
            if (parse_via(hdr_value, hdr_value_size) == -1) {
                return false;
            }
        } else if (!global_env::strcasecmp(hdr_name, "Max-Forwards")) {
            m_max_forwards = sip_hdr;
        } else if (!global_env::strcasecmp(hdr_name, "Call-ID")) {
			m_call_id = sip_hdr;
		} else if (!global_env::strcasecmp(hdr_name, "From")) {
            if (!m_from_hdr.parse(hdr_value, hdr_value_size)) {
                return false;
            }
        } else if (!global_env::strcasecmp(hdr_name, "To")) {
            if (!m_to_hdr.parse(hdr_value, hdr_value_size)) {
                return false;
            }
        } else if (!global_env::strcasecmp(hdr_name, "CSeq")) {
            if (!m_cseq_hdr.parse(hdr_value, hdr_value_size)) {
                return false;
            }
        } else if (!global_env::strcasecmp(hdr_name, "Contact")) {
            if (parse_contacts(hdr_value, hdr_value_size) == -1) {
                return false;
            }
        } else if (!global_env::strcasecmp(hdr_name, "Authorization")) {
            if (parse_credentials(hdr_value, hdr_value_size) == -1) {
                return false;
            }
        } else if (!global_env::strcasecmp(hdr_name, "Content-Length")) {
            content_data_size = atoi(hdr_value);
        } else {
            m_sip_hdr_list.push_back(sip_hdr);
        }
    }

    if (content_data_size > 0) {
        if (content_data_size > data_size - cur_pos) {
            return false;
        }
        m_content_data.append(data + cur_pos, content_data_size);
    }
    return true;
}
std::string sip_message_t::to_string() const {
    std::string s;

    // Request line
    if (m_status_code > 0) {
        if (m_reason.empty()) {
            s += std::string(SIP_VERSION) + " " + std::to_string(m_status_code) + " " + get_reason_phrase(m_status_code);
        } else {
            s += std::string(SIP_VERSION) + " " + std::to_string(m_status_code) + " " + m_reason;
        }
    } else {
        s += m_sip_method + " " + m_req_uri.to_string() + " " + SIP_VERSION;
    }
    s += "\r\n";


    for (const auto& via : m_via_list) {
        s += "Via: " + via.to_string() + "\r\n";
    }
    s += "From: " + m_from_hdr.to_string() + "\r\n";
    s += "To: " + m_to_hdr.to_string() + "\r\n";
    s += "CSeq: " + m_cseq_hdr.to_string() + "\r\n";
	s += m_call_id.to_string() + "\r\n";

    // Max-Forwards
    if (!m_max_forwards.empty()) {
        s += "Max-Forwards: " + m_max_forwards.to_string() + "\r\n";
    }

    // Content-Type
    /*if (!m_content_data.empty()) {
        s += "Content-Type: application/sdp\r\n";
		

    }*/
    /*   if (m_clsContentType.Empty() == false)
       {
           iLen += snprintf(pszText + iLen, iTextSize - iLen, (m_bUseCompact ? "c: " : "Content-Type: "));
           n = m_clsContentType.ToString(pszText + iLen, iTextSize - iLen);
           if (n == -1) return -1;
           iLen += n;
           iLen += snprintf(pszText + iLen, iTextSize - iLen, "\r\n");
       }

       iLen += snprintf(pszText + iLen, iTextSize - iLen, "%s: %d\r\n", (m_bUseCompact ? "l" : "Content-Length"), m_iContentLength);
   */
    return s;
}
void sip_message_t::clear() {
    m_sip_method.clear();
	m_via_list.clear();
    m_call_id.clear();
    m_content_data.clear();
    m_max_forwards.clear();
    m_from_hdr.clear();
    m_to_hdr.clear();
    m_cseq_hdr.clear();
    m_contact_hdr_list.clear();
    m_credential_hdr_list.clear();
    m_sip_hdr_list.clear();
}

void sip_message_t::add_header(const std::string& name, const std::string& value) {
    m_sip_hdr_list.push_back(sip_hdr_t(name, value));
}

//
// protected API. Only non-virtual methods
int sip_message_t::parse_status_line(const char* data, int data_size) {
    char type = 0;
    for (int idx = 0, start_idx = -1; idx < data_size; ++idx) {
        if (type != 2) {
            if (data[idx] == ' ') {
                switch (type) {
                case 0:
                    //m_sip_version.append(data, idx);
                    break;
                case 1:
                    m_status_code = atoi(std::string(data + start_idx, idx - start_idx).c_str());
                    break;
                }
                start_idx = idx + 1;
                ++type;
            }
        } else {
            if (data[idx] == '\r') {
                if (idx + 1 >= data_size || data[idx + 1] != '\n') {
                    return -1;
                }
                m_reason = std::string(data + start_idx, idx - start_idx);
                return idx + 2;
            }
        }
    }
    return -1;
}
int sip_message_t::parse_request_line(const char* data, int data_size) {
    char type = 0;
    for (int idx = 0, start_idx = -1; idx < data_size; ++idx) {
        if (type != 2) {
            if (data[idx] == ' ') {
                switch (type) {
                case 0:
                    m_sip_method.append(data, idx);
                    break;
                case 1:
                    if (m_req_uri.parse(data + start_idx, idx - start_idx) == -1) {
                        return -1;
                    }
                    break;
                }

                start_idx = idx + 1;
                ++type;
            }
        } else {
            if (data[idx] == '\r') {
                if (idx + 1 >= data_size || data[idx + 1] != '\n') {
                    return -1;
                }
                //m_sip_version.append(data + start_idx, idx - start_idx);
                return idx + 2;
            }
        }
    }
    return -1;
}
int sip_message_t::parse_contacts(const char* data, int data_size) {
    int cur_idx = 0;
    while (cur_idx < data_size) {
        if (data[cur_idx] == ' ' || data[cur_idx] == '\t' || data[cur_idx] == ',') {
            ++cur_idx;
            continue;
        }

		sip_contact_hdr_t hdr;;
        int idx = hdr.parse(data + cur_idx, data_size - cur_idx);
        if (idx == -1) {
            return -1;
        }
        cur_idx += idx;

        m_contact_hdr_list.push_back(hdr);
    }
    return cur_idx;
}
int sip_message_t::parse_credentials(const char* data, int data_size) {
	sip_credential_hdr_t hdr;
    int idx = hdr.parse(data, data_size);
    if (idx == -1) {
        return -1;
    }
    m_credential_hdr_list.push_back(hdr);
    return idx;
}
int sip_message_t::parse_via(const char* data, int data_size) {
    sip_via_hdr_t hdr;
    int idx = hdr.parse(data, data_size);
    if (idx == -1) {
        return -1;
    }
    m_via_list.push_back(hdr);
    return idx;
}

//
// public static API. Only static methods

//
// protected static API. Only static methods
