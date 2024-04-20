#include "sipstack.hpp"



sipstack_t::sipstack_t() {

}
sipstack_t::~sipstack_t() {
    close(global_env::SIP_SOCKET);
}

bool sipstack_t::init() {
    if (socket(global_env::SIP_SOCKET, Sn_MR_UDP, global_env::SIP_PORT, 0x00) < 0) {
        return false;
    }
    return true;
}
void sipstack_t::tick() {
    uint8_t buffer[1024] = {0};
    uint8_t addr[4] = {0};
    uint16_t port = 0;
    int length = recvfrom(global_env::SIP_SOCKET, buffer, 1024, addr, &port);
    if (length > 0) {
        sip_message_t sip_message;
        sip_message.parse(buffer, length);
        asm("nop");
    }
    asm("nop");
}