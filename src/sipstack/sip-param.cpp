#include "sip-param.hpp"


int sip_param_t::parse(const char* data, int data_size) {
    reset();

    if (data == NULL || data_size <= 0) {
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
void sip_param_t::reset() {
    m_name.clear();
    m_value.clear();
}


int sip_param_list_t::param_list_parse(const char* data, int data_size) {
    int cur_pos = 0;
    while (cur_pos < data_size) {
        if (data[cur_pos] == ' ' || data[cur_pos] == '\t' || data[cur_pos] == ';') {
            ++cur_pos;
            continue;
        } else if (data[cur_pos] == ',') {
            break;
        }

        int idx = this->param_parse(data + cur_pos, data_size - cur_pos);
        if (idx == -1) {
            return -1;
        }
        cur_pos += idx;
    }
    return cur_pos;
}

int sip_param_list_t::param_parse(const char* data, int data_size) {
    sip_param_t* sip_param = new sip_param_t();
    if (!sip_param) {
        return -1;
    }

    int idx = sip_param->parse(data, data_size);
    if (idx == -1) {
        delete sip_param;
        return -1;
    }
    m_param_list.push_back(sip_param);
    return idx;
}