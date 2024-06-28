#include "global-env.hpp"
#include "sip-hdr.hpp"


//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_hdr_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return -1;
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
                    return -1;
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
                return -1;
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
    return idx;
}
std::string sip_hdr_t::to_string() const {
    return m_name + ": " + m_value;
}
void sip_hdr_t::clear() {
    m_name.clear();
    m_value.clear();
}

//
// protected API. Only non-virtual methods

//
// public static API. Only static methods

//
// protected static API. Only static methods
