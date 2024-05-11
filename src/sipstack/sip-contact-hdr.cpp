#include "sip-contact-hdr.hpp"


//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_contact_hdr_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return -1;
    }

    int idx = -1;
    int display_name_pos = -1;
    int uri_start_pos = -1;
    int uri_end_pos = -1;
    for (idx = 0; idx < data_size; ++idx) {
        if (display_name_pos != -1) {
            if (data[idx] == '"') {
                m_display_name.append(data + display_name_pos, idx - display_name_pos);
                display_name_pos = -1;
            }
        } else if (uri_start_pos != -1) {
            if (data[idx] == '>') {
                uri_end_pos = idx;
                ++idx;
                break;
            }
        } else if (data[idx] == '"') {
            display_name_pos = idx + 1;
        } else if (data[idx] == '<') {
            uri_start_pos = idx + 1;
            if (m_display_name.empty() && idx > 0) {
                for (int i = idx - 1; i >= 0; --i) {
                    if (data[i] != ' ' && data[i] != '\t') {
                        m_display_name.append(data, i + 1);
                        break;
                    }
                }
            }
        } else if (data[idx] == ';' || data[idx] == ',') {
            break;
        }
    }

    if (uri_start_pos != -1 && uri_end_pos != -1) {
        m_uri.parse(data + uri_start_pos, uri_end_pos - uri_start_pos);
    } else {
        m_uri.parse(data, idx);
    }

    int idx2 = sip_param_t::list_param_parse(data + idx, data_size - idx, &m_param_list);
    if (idx2 == -1) {
        return -1;
    }
    idx += idx2;

	return idx;
}
void sip_contact_hdr_t::clear() {
    m_display_name.clear();
    m_uri.clear();
    m_param_list.clear();
}
void sip_contact_hdr_t::add_param(const std::string& n, const std::string& v) {
    m_param_list.push_back(sip_param_t(n, v));
}

//
// protected API. Only non-virtual methods

//
// public static API. Only static methods

//
// protected static API. Only static methods

