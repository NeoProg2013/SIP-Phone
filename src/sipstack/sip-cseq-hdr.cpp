#include "global-env.hpp"
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
        if (m_cseq == -1) {
            if (data[idx] == ' ') {
                std::string tmp;
                tmp.append(data, idx);
                m_cseq = atoi(tmp.c_str());
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
std::string sip_cseq_hdr_t::to_string() const {
    return std::to_string(m_cseq) + " " + m_method;
}
void sip_cseq_hdr_t::clear() {
    m_cseq = -1;
    m_method.clear();
}

//
// protected API. Only non-virtual methods

//
// public static API. Only static methods

//
// protected static API. Only static methods

