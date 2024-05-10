#include "sip-param.hpp"


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
void sip_param_t::clear() {
    m_name.clear();
    m_value.clear();
}



int sip_param_t::list_param_parse(const char* data, int data_size, std::list<sip_param_t>* param_list) {
    return sip_param_t::list_param_parse(data, data_size, param_list, [](char a, int* cur_pos) -> int {
        if (a == ' ' || a == '\t' || a == ';') {
            ++(*cur_pos);
            return 1; // continue
        } else if (a == ',') {
            return -1; // break
        }
        return 0; // parsing
	});
}
int sip_param_t::list_param_parse(const char* data, int data_size, std::list<sip_param_t>* param_list, std::function<int(char, int*)> f) {
    int cur_pos = 0;
    while (cur_pos < data_size) {
        int idx = f(data[cur_pos], &cur_pos);
        if (idx == -1) break;
        if (idx ==  1) continue;

        sip_param_t param;
        idx = param.parse(data + cur_pos, data_size - cur_pos);
        if (idx == -1) {
            return -1;
        }
        param_list->push_back(param);
        cur_pos += idx;
    }
    return cur_pos;
}
