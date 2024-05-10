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



int sip_from_hdr_t::parse(const char* data, int data_size) {
    reset();

    int idx = -1;
    int display_name_pos = -1;
    int uri_start_pos = -1;
    int uri_end_pos = -1;

    for (idx = 0; idx < data_size; ++idx) {
        if (display_name_pos != -1) {
            if (data[idx] == '"') {
                m_strDisplayName.append( data + display_name_pos, idx - display_name_pos);
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
        m_clsUri.Parse(data + uri_start_pos, uri_end_pos - uri_start_pos);
    } else {
        m_clsUri.Parse(data, idx);
    }

    /*int idx2 = HeaderListParamParse(data + idx, data_size - idx);
    if (idx2 == -1) {
        return -1;
    }*/
    return idx + idx2;
}
void sip_from_hdr_t::reset() {
    m_display_name.clear();
}