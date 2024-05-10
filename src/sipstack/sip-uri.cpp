#include "sip-uri.hpp"

//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_uri_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return -1;
    }

    int idx = this->parse_protocol(data, data_size);
    if (idx == -1) {
        return -1;
    }
    int cur_idx = idx;

    idx = this->parse_user(data + cur_idx, data_size - cur_idx);
    if (idx > 0) {
        cur_idx += idx;
    }

    idx = this->parse_host(data + cur_idx, data_size - cur_idx);
    if (idx == -1) {
        return -1;
    }
    cur_idx += idx;

    while (cur_idx < data_size) {
        if (data[cur_idx] == '?') {
            ++cur_idx;
            break;
        }
        if (data[cur_idx] == ';' || data[cur_idx] == ' ' || data[cur_idx] == '\t') {
            ++cur_idx;
            continue;
        }

        idx = sip_param_t::single_param_parse(data + cur_idx, data_size - cur_idx, &m_uri_param_list);
        if (idx == -1) {
            return -1;
        }
        cur_idx += idx;
    }

    while (cur_idx < data_size) {
        if (data[cur_idx] == ' ' || data[cur_idx] == '\t' || data[cur_idx] == '&') {
            ++cur_idx;
            continue;
        }

        idx = sip_param_t::single_param_parse(data + cur_idx, data_size - cur_idx, &m_hdr_list);
        if (idx == -1) {
            return -1;
        }
        cur_idx += idx;
    }

    return cur_idx;
}
void sip_uri_t::clear() {
    m_port = 0;
    m_protocol.clear();
    m_user.clear();
    m_host.clear();
    m_uri_param_list.clear();
    m_hdr_list.clear();
}

//
// protected API. Only non-virtual methods
int sip_uri_t::parse_protocol(const char* data, int data_size) {
    for (int idx = 0; idx < data_size; ++idx) {
        if (data[idx] == ':') {
            m_protocol.append(data, idx);
            return idx + 1;
        }
    }
    return -1;
}
int sip_uri_t::parse_user(const char* data, int data_size) {
    for (int idx = 0; idx < data_size; ++idx) {
        if (data[idx] == '@') {
            m_user.append(data, idx);
            return idx + 1;
        }
    }
    return -1;
}
int sip_uri_t::parse_host(const char* data, int data_size) {
    int idx = -1;
    int port_idx = -1;

    if (data[0] == '[') {
        bool bIpFound = false;

        for (idx = 1; idx < data_size; ++idx) {
            if (!bIpFound) {
                if (data[idx] == ']') {
                    m_host.append(data + 1, idx - 1);
                    bIpFound = true;
                }
            } else if (data[idx] == ':') {
                port_idx = idx + 1;
            } else if (data[idx] == ';' || data[idx] == '?') {
                break;
            }
        }

        if (!bIpFound) {
            return -1;
        }
        if (port_idx != -1 && port_idx < idx) {
            std::string strTemp;

            strTemp.append(data + port_idx, idx - port_idx);
            m_port = atoi(strTemp.c_str());
        }
        return idx;
    } else {
        for (idx = 0; idx < data_size; ++idx) {
            if (data[idx] == ':') {
                m_host.append(data, idx);
                port_idx = idx + 1;
            } else if (data[idx] == ';' || data[idx] == '?') {
                break;
            }
        }

        if (port_idx == -1) {
            if (idx > 0) {
                m_host.append(data, idx);
                return idx;
            }
        } else {
            if (port_idx < idx) {
                // TODO: need replace this
                std::string strTemp;
                strTemp.append(data + port_idx, idx - port_idx);
                m_port = atoi(strTemp.c_str());
            }
            return idx;
        }
    }
    return -1;
}

//
// public static API. Only static methods

//
// protected static API. Only static methods
