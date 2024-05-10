#include "sip-cseq-hdr.hpp"


//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
int sip_cseq_hdr_t::parse(const char* data, int data_size) {
    clear();
    if (!data || data_size <= 0) {
        return false;
    }

    int idx = -1;
    for (idx = 0; idx < data_size; ++idx) {
        if (m_seq == -1) {
            if (data[idx] == ' ') {
                std::string tmp;
                tmp.append(data, idx);
                m_seq = atoi(tmp.c_str());
            }
        } else if (data[idx] == ' ' || data[idx] == '\t') {
            continue;
        } else {
            m_method.append(data + idx);
            break;
        }
    }
    return idx;
}
void sip_cseq_hdr_t::clear() {
    m_seq = -1;
    m_method.clear();
}

//
// protected API. Only non-virtual methods

//
// public static API. Only static methods

//
// protected static API. Only static methods

