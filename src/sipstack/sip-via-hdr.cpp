#include "global-env.hpp"
#include "sip-via-hdr.hpp"

//
// public virtual API. Only virtual methods and ctors
sip_via_hdr_t::sip_via_hdr_t(const std::string& host, uint16_t port, const std::string& branch)
	: m_host(host), m_port(port) {

	m_param_list.push_back(sip_param_t("branch", branch));
}

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_via_hdr_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return -1;
    }

    int cur_idx = 0;

    int idx = parse_protocol(data, data_size);
    if (idx == -1) {
        return -1;
    }
    cur_idx = idx;

    idx = parse_by(data + cur_idx, data_size - cur_idx);
    if (idx == -1) {
        return -1;
    }
    cur_idx += idx;

    idx = sip_param_t::list_parse(data + cur_idx, data_size - cur_idx, &m_param_list);
    if (idx == -1) {
        return -1;
    }
    cur_idx += idx;

    return cur_idx;
}

std::string sip_via_hdr_t::to_string() const {
    std::string s = "SIP/2.0/UDP " + m_host;
    if (m_port > 0) {
        s += ":" + std::to_string(m_port);
    }
    return s + sip_param_t::list_to_string(m_param_list);
}

void sip_via_hdr_t::clear() {
    m_port = 0;
    m_host.clear();
    m_param_list.clear();
}

//
// protected API. Only non-virtual methods
int sip_via_hdr_t::parse_protocol(const char* data, int data_size) {
    char part = 0; // [0/1/2] == [SIP/2.0/UDP]
    for (int idx = 0, prev_idx = -1; idx < data_size; ++idx) {
        if (data[idx] == '/') {
            switch (part) {
            case 0: // Protocol part
                //m_protocol_name.append(data, idx);
                prev_idx = idx + 1;
                break;
            case 1: // Version part
                //m_protocol_version.append(data + prev_idx, idx - prev_idx);
                prev_idx = idx + 1;
                break;
            default:
                return -1;
            }
            ++part;
        } else if (data[idx] == ' ') {
            if (part == 2) { // Transport part
                //m_transport.append(data + prev_idx, idx - prev_idx);
                return idx + 1;
            } else {
                return -1;
            }
        }
    }
    return -1;
}

int sip_via_hdr_t::parse_by(const char* data, int data_size) {
    int idx = -1;
    int port_idx = -1;

    if (data[0] == '[') {
        bool is_ip_found = false;

        for (idx = 1; idx < data_size; ++idx) {
            if (is_ip_found == false) {
                if (data[idx] == ']') {
                    m_host.append(data + 1, idx - 1);
                    is_ip_found = true;
                }
            } else if (data[idx] == ':') {
                port_idx = idx + 1;
            } else if (data[idx] == ' ' || data[idx] == ';' || data[idx] == ',') {
                break;
            }
        }

        if (is_ip_found == false) {
            return -1;
        }
        if (port_idx != -1 && port_idx < idx) {
            m_port = std::stoi(std::string(data + port_idx, idx - port_idx));
        }
        return idx;
    } else {
        for (idx = 0; idx < data_size; ++idx) {
            if (data[idx] == ':') {
                m_host.append(data, idx);
                port_idx = idx + 1;
            } else if (data[idx] == ' ' || data[idx] == ';' || data[idx] == ',') {
                break;
            }
        }

        if (m_host.empty()) {
            m_host.append(data, idx);
        } else {
            m_port = std::stoi(std::string(data + port_idx, idx - port_idx));
        }
    }
    return idx;
}

//
// public static API. Only static methods

//
// protected static API. Only static methods
