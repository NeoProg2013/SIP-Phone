#ifndef _DCHP_CLIENT_H_
#define _DCHP_CLIENT_H_
#include "project-base.hpp"


class dhcp_client_t {
public:
    dhcp_client_t();
    ~dhcp_client_t();

    bool init();
    void tick();
    
    bool is_ip_address_set() const;

protected:
    uint8_t m_buffer[512];
    uint32_t m_tick_counter             {0};
    bool m_is_ip_address_set            {false};
};


#endif // _DCHP_CLIENT_H_