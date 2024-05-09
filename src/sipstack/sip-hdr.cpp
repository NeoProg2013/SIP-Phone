#include "sip-hdr.hpp"


int sip_hdr_t::parse(const char* data, int data_size) {
    reset();
    
    if (data_size <= 0) {
        return false;
    }

    // Parse header name & skip prefix space of header value
    int idx = 0;
    char type = 0;
    for (idx = 0; idx < data_size; ++idx) {
        if (type == 0) {
            if (data[idx] == ':' || data[idx] == ' ' || data[idx] == '\t') {
                m_name.append(data, idx);
                ++type;
            } else if (data[idx] == '\r') {
                if (idx + 1 >= data_size || data[idx + 1] != '\n') {
                    return false;
                }
                return idx + 2;
            }
        } else if (data[idx] == ':' || data[idx] == ' ' || data[idx] == '\t') {
            continue;
        } else {
            break;
        }
    }

    // Parse header value
    int value_idx = idx;
    for (; idx < data_size; ++idx) {
        if (type == 10) {
            if (data[idx] != ' ' && data[idx] != '\t') {
                type = 11;
                --idx;
                value_idx = idx;
            }
        } else if (data[idx] == '\r') {
            if (value_idx != -1) {
                m_value.append(data + value_idx, idx - value_idx);
                value_idx = -1;
            }

            ++idx;
            if (idx == data_size || data[idx] != '\n') {
                return false;
            }

            ++idx;
            if (idx == data_size) {
                break;
            }

            if (data[idx] == ' ' || data[idx] == '\t') {
                type = 10;
                m_value.append(" ");
            } else {
                break;
            }
        }
    }
    return true;
}
void sip_hdr_t::reset() {
    m_name.clear();
    m_value.clear();
}