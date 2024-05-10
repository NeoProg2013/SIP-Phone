#include "dhcp-client.hpp"
#include "dhcp.h"


static wiz_NetInfo net_info = { 
    .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},
    .ip  = {0, 0, 0, 0},
    .sn  = {0, 0, 0, 0},
    .gw  = {0, 0, 0, 0},
    .dns = {0, 0, 0, 0},
    .dhcp = NETINFO_DHCP 
};
static void dhcp_ip_assing_callback() {
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
static void dhcp_ip_update_callback() {
    asm("nop");
}
static void dhcp_ip_conflict_callback() {
    asm("nop");
}



dhcp_client_t::dhcp_client_t() {

}
dhcp_client_t::~dhcp_client_t() {
    close(global_env::SIP_SOCKET);
}

bool dhcp_client_t::init() {
    DHCP_stop();
    DHCP_init(global_env::DHCP_SOCKET, m_buffer, dhcp_ip_assing_callback, dhcp_ip_update_callback, dhcp_ip_conflict_callback);
    m_tick_counter = HAL_GetTick();
    return true;
}
void dhcp_client_t::tick() {
    if (!m_is_ip_address_set) {
        if (HAL_GetTick() - m_tick_counter > 1000) {
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
                init();
                break;
        }
    }
}
bool dhcp_client_t::is_ip_address_set() const {
    return m_is_ip_address_set;
}