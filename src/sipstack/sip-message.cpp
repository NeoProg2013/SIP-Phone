#include "sip-message.hpp"


bool sip_message_t::parse(const char* data, uint16_t data_size) {
    if (data_size <= 4) {
        return false;
    }

    int cur_pos = 0;
    if (!strncmp(data, "SIP/", 4)) {
        cur_pos = parse_status_line(data, data_size);
    } else {
        cur_pos = parse_request_line(data, data_size);
    }
    if (cur_pos == -1) {
        return false;
    }

    while (cur_pos < data_size) {
        sip_hdr_t sip_hdr;
        int idx = sip_hdr.parse(data + cur_pos, data_size - cur_pos);
        if (idx == -1) {
            return false;
        }
        cur_pos += idx;

        if (sip_hdr.get_name().empty()) {
            break;
        }

        const char* const hdr_name = sip_hdr.get_name().c_str();
        const char* const hdr_value = sip_hdr.get_value().c_str();
        int hdr_value_size = sip_hdr.get_value().size();


        if (!strcasecmp(hdr_name, "Via")) {
            /*if (ParseSipVia(m_clsViaList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Max-Forwards")) {
            m_max_forwards = atoi(hdr_value);
        } else if (!strcasecmp(hdr_name, "From")) {
            /*if (m_clsFrom.Parse(hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "To")) {
            /*if (m_clsTo.Parse(hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "CSeq")) {
            /*if (m_clsCSeq.Parse(hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Call-ID")) {
            /*if (m_clsCallId.Parse(hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Contact")) {
            /*if (ParseSipFrom(m_clsContactList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Record-Route")) {
            /*if (ParseSipFrom(m_clsRecordRouteList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Route")) {
            /*if (ParseSipFrom(m_clsRouteList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Authorization")) {
            /*if (ParseSipCredential(m_clsAuthorizationList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "WWW-Authenticate")) {
            /*if (ParseSipChallenge(m_clsWwwAuthenticateList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Proxy-Authorization")) {
            /*if (ParseSipCredential(m_clsProxyAuthorizationList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Proxy-Authenticate")) {
            /*if (ParseSipChallenge(m_clsProxyAuthenticateList, hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Content-Type")) {
            /*if (m_clsContentType.Parse(hdr_value, hdr_value_size) == -1) {
                return false;
            }*/
        } else if (!strcasecmp(hdr_name, "Content-data_size")) {
            m_content_data_size = atoi(hdr_value);
        } else if (!strcasecmp(hdr_name, "Expires")) {
            m_expires = atoi(hdr_value);
        } else if (!strcasecmp(hdr_name, "User-Agent")) {
            m_user_agent = hdr_value;
        } else {
            m_sip_hdr_list.push_back(sip_hdr);
        }
    }

    if (m_content_data_size > 0) {
        if (m_content_data_size > (data_size - cur_pos)) {
            return false;
        }
        m_body.append(data + cur_pos, m_content_data_size);
        return data_size;
    }
    return cur_pos;
}
int sip_message_t::parse_status_line(const char* data, int data_size) {
    char type = 0;
    for (int idx = 0, start_idx = -1; idx < data_size; ++idx) {
        if (type != 2) {
            if (data[idx] == ' ') {
                switch (type) {
                    case 0:
                        m_sip_version.append(data, idx);
                        break;
                    case 1: {
                        std::string s;
                        s.append(data + start_idx, idx - start_idx);
                        m_status_code = atoi(s.c_str());
                        break;
                    }
                }
                start_idx = idx + 1;
                ++type;
            }
        } else {
            if (data[idx] == '\r') {
                if (idx + 1 >= data_size || data[idx + 1] != '\n') {
                    return -1;
                }
                m_reason_phrase.append(data + start_idx, idx - start_idx);
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
                        /*if (m_clsReqUri.Parse(data + start_idx, idx - start_idx) == -1) {
                            return -1;
                        }*/
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
                m_sip_version.append(data + start_idx, idx - start_idx);
                return idx + 2;
            }
        }
    }
    return -1;
}
