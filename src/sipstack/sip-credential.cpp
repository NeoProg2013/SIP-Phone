#include "sip-credential.hpp"

//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_credential_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return -1;
    }

    int idx = -1;
    for (idx = 0; idx < data_size; ++idx) {
        if (data[idx] == ' ' || data[idx] == '\t') {
            m_type.append(data, idx);
            ++idx;
            break;
        }
    }

    if (m_type.empty()) {
        return -1;
    }
    int cur_idx = idx;

    while (cur_idx < data_size) {
        if (data[cur_idx] == ' ' || data[cur_idx] == '\t' || data[cur_idx] == ',') {
            ++cur_idx;
            continue;
        }

        idx = parse_params(data + cur_idx, data_size - cur_idx);
        if (idx == -1) {
            return -1;
        }
        cur_idx += idx;
    }

    for (auto& param : m_param_list) {
        const char* name = param.get_name();
        const char* value = param.get_value();
        if (!strcmp(name, "username")) {
            m_user_name = dequote_string(value);
        } else if (!strcmp(name, "realm")) {
            m_realm = dequote_string(value);
        } else if (!strcmp(name, "nonce")) {
            m_nonce = dequote_string(value);
        } else if (!strcmp(name, "uri")) {
            m_uri = dequote_string(value);
        } else if (!strcmp(name, "response")) {
            m_response = dequote_string(value);
        } else if (!strcmp(name, "algorithm")) {
            m_algorithm = value;
        } else if (!strcmp(name, "cnonce")) {
            m_cnonce = dequote_string(value);
        } else if (!strcmp(name, "opaque")) {
            m_opaque = dequote_string(value);
        } else if (!strcmp(name, "qop")) {
            m_qop = value;
        } else if (!strcmp(name, "nc")) {
            m_nonce_count = value;
        }
    }
    return cur_idx;
}
void sip_credential_t::clear() {
    m_type.clear();
    m_user_name.clear();
    m_realm.clear();
    m_nonce.clear();
    m_uri.clear();
    m_response.clear();
    m_algorithm.clear();
    m_cnonce.clear();
    m_opaque.clear();
    m_qop.clear();
    m_nonce_count.clear();
    m_param_list.clear();
}

//
// protected API. Only non-virtual methods
int sip_credential_t::parse_params(const char* data, int data_size) {
    sip_param_t param;
    int idx = param.parse(data, data_size);
    if (idx == -1) {
        return -1;
    }
    m_param_list.push_back(param);
    return idx;
}
std::string sip_credential_t::dequote_string(const std::string& s) const {
    if (s.size() >= 2) {
        if (s.at(0) != '"' || s.at(s.size() - 1) != '"') {
            return s;
        }
        std::string tmp;
        tmp.append(s, 1, s.size() - 2);
    }
}

//
// public static API. Only static methods

//
// protected static API. Only static methods
