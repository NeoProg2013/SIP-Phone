#include "global-env.hpp"
#include "sip-credential-hdr.hpp"

//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_credential_hdr_t::parse(const char* data, int data_size) {
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

    // Parsing params
    idx = sip_param_t::list_parse(data + cur_idx, data_size - cur_idx, &m_param_list, [](char _a, int* _pos) -> int {
        if (_a == ' ' || _a == '\t' || _a == ',') {
            ++(*_pos);
            return 1; // continue
        }
        return 0; // parsing
    });
    if (idx == -1) {
        return -1;
    }
    cur_idx += idx;

    // Get params from param list
    for (auto& param : m_param_list) {
        const char* name = param.get_name().c_str();
        const std::string& value = param.get_value();
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
            m_qop = dequote_string(value);
        } else if (!strcmp(name, "nc")) {
            m_nc = value;
        }
    }
    return cur_idx;
}
std::string sip_credential_hdr_t::to_string() const {
	std::string s(m_type);
	s += " opaque=\"" + m_opaque + "\"";

	if (!m_qop.empty())       s += ", qop=\"" + m_qop + "\"";
	if (!m_user_name.empty()) s += ", username=\"" + m_user_name + "\"";
	if (!m_realm.empty())     s += ", realm=\"" + m_realm + "\"";
	if (!m_nonce.empty())     s += ", nonce=\"" + m_nonce + "\"";
	if (!m_uri.empty())       s += ", uri=\"" + m_uri + "\"";
	if (!m_response.empty())  s += ", response=\"" + m_response + "\"";
	if (!m_algorithm.empty()) s += ", algorithm=" + m_algorithm;
	if (!m_cnonce.empty())    s += ", cnonce=\"" + m_cnonce + "\"";
	if (!m_nc.empty())        s += ", nc=" + m_nc;

	return s;
}
void sip_credential_hdr_t::clear() {
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
    m_nc.clear();
    m_param_list.clear();
}

//
// protected API. Only non-virtual methods
int sip_credential_hdr_t::parse_params(const char* data, int data_size) {
    sip_param_t param;
    int idx = param.parse(data, data_size);
    if (idx == -1) {
        return -1;
    }
    m_param_list.push_back(param);
    return idx;
}
std::string sip_credential_hdr_t::dequote_string(const std::string& s) const {
    if (s.size() >= 2) {
        if (s.at(0) != '"' || s.at(s.size() - 1) != '"') {
            return s;
        }
        std::string tmp;
        tmp.append(s, 1, s.size() - 2);
		return tmp;
    }
	return s;
}

//
// public static API. Only static methods

//
// protected static API. Only static methods
