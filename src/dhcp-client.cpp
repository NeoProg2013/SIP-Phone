#include "dhcp-client.hpp"
#include "dhcp.h"


uint8_t dhcp_data_buffer[512];
wiz_NetInfo net_info = { 
    .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},
    .ip  = {0, 0, 0, 0},
    .sn  = {0, 0, 0, 0},
    .gw  = {0, 0, 0, 0},
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_DHCP 
};

void dhcp_ip_assing_callback() {
    DHCP_get_ip(net_info.ip);
    DHCP_get_gateway_ip(net_info.gw);
    DHCP_get_subnet_mask(net_info.sn);
    DHCP_get_dns_ip(net_info.dns);
    net_info.dhcp = NETINFO_DHCP;
    int32_t time = DHCP_get_lease_time();

    setSIPR(net_info.ip);
    setSUBR(net_info.sn);
    setGAR (net_info.gw);
    asm("nop");
}
void dhcp_ip_update_callback() {
    asm("nop");
}
void dhcp_ip_conflict_callback() {
    asm("nop");
}



dhcp_client_t::dhcp_client_t() {

}
dhcp_client_t::~dhcp_client_t() {
    close(global_env::SIP_SOCKET);
}

bool dhcp_client_t::init() {
    DHCP_init(global_env::DHCP_SOCKET, dhcp_data_buffer, dhcp_ip_assing_callback, dhcp_ip_update_callback, dhcp_ip_conflict_callback);
    return true;
}
void dhcp_client_t::tick() {
    if (!m_is_ip_address_set) {
        static uint32_t tick = 0;
        if (tick == 0) {
            tick = HAL_GetTick();
        }
        if (HAL_GetTick() - tick > 1000) {
            DHCP_time_handler();
        }
        switch (DHCP_run()) {
            case DHCP_IP_ASSIGN:
                break;
            case DHCP_IP_CHANGED:
                break;
            case DHCP_IP_LEASED:
                m_is_ip_address_set = true;
                break;
            case DHCP_FAILED:
                DHCP_stop();
                DHCP_init(1, dhcp_data_buffer, dhcp_ip_assing_callback, dhcp_ip_update_callback, dhcp_ip_conflict_callback);
                break;
        }
    }
}
bool dhcp_client_t::is_ip_address_set() const {
    return m_is_ip_address_set;
}