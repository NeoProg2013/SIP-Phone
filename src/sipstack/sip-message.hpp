#ifndef _SIP_MESSAGE_H_
#define _SIP_MESSAGE_H_
#include "project-base.hpp"


class sip_message_t {
public:
    sip_message_t();
    ~sip_message_t();

    bool parse(const uint8_t* data, uint16_t length);
};


#endif // _SIP_MESSAGE_H_