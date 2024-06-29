#include "global-env.hpp"
#include "sip-param.hpp"


//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_param_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return -1;
    }

    int idx = -1;
    int value_idx = -1;
    bool is_start_quote = false;

    for (idx = 0; idx < data_size; ++idx) {
        if (data[idx] == '"') {
            is_start_quote = !is_start_quote;
        } else if (data[idx] == '=') {
            if (is_start_quote) {
                continue;
            }
            m_name.append(data, idx);
            value_idx = idx + 1;
        } else if (data[idx] == ',' || data[idx] == ';' || data[idx] == '&' || data[idx] == '?') {
            if (is_start_quote) {
                continue;
            }
            break;
        } else if (data[idx] == '\r') {
            break;
        }
    }

    if (idx > 0) {
        if (value_idx != -1) {
            m_value.append(data + value_idx, idx - value_idx);
        } else {
            m_name.append(data, idx);
        }
        return idx;
    }
    return -1;
}
std::string sip_param_t::to_string() const {
	if (m_value.empty()) {
		return m_name;
	}
	return m_name + "=" + m_value; 
}
void sip_param_t::clear() {
    m_name.clear();
    m_value.clear();
}

//
// protected API. Only non-virtual methods

//
// public static API. Only static methods
int sip_param_t::list_parse(const char* data, int data_size, std::list<sip_param_t>* param_list) {
    return sip_param_t::list_parse(data, data_size, param_list, [](char _a, int* _pos) -> int {
        if (_a == ' ' || _a == '\t' || _a == ';') {
            ++(*_pos);
            return 1; // continue
        } else if (_a == ',') {
            return -1; // break
        }
        return 0; // parsing
	});
}
int sip_param_t::list_parse(const char* data, int data_size, std::list<sip_param_t>* param_list, std::function<int(char, int*)> f) {
    int cur_idx = 0;
    while (cur_idx < data_size) {
        int idx = f(data[cur_idx], &cur_idx);
        if (idx == -1) break;
        if (idx ==  1) continue;

        sip_param_t param;
        idx = param.parse(data + cur_idx, data_size - cur_idx);
        if (idx == -1) {
            return -1;
        }
        param_list->push_back(param);
        cur_idx += idx;
    }
    return cur_idx;
}
std::string sip_param_t::list_to_string(const std::list<sip_param_t>& param_list, char first_sep, char sep) {
    std::string s;
    for (auto& p : param_list) {
        if (s.empty()) {
            s += first_sep;
        } else {
            s += sep;
        }
        s += p.to_string();
    }
	return s;
}

//
// protected static API. Only static methods
