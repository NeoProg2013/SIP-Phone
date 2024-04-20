#ifndef _DCHP_H_
#define _DCHP_H_


class dhcp_client_t {
public:
    dhcp_client_t();
    ~dhcp_client_t();

    bool init();
    void tick();

protected:
    bool m_is_ip_address_set      {false};
};


#endif // _DCHP_H_