#ifndef _SIP_STACK_H_
#define _SIP_STACK_H_
#include "project-base.hpp"
#include "sip-message.hpp"


class sipstack_t {
public:
    sipstack_t();
    ~sipstack_t();

    bool init();
    void tick();
};


#endif // _SIP_STACK_H_