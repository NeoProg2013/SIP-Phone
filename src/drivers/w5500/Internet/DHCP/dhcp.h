#ifndef _DHCP_H_
#define _DHCP_H_

#ifdef __cplusplus
extern "C" {
#endif


enum {
    DHCP_FAILED = 0,  ///< Processing Fail
    DHCP_RUNNING,     ///< Processing DHCP protocol
    DHCP_IP_ASSIGN,   ///< First Occupy IP from DHPC server      (if cbfunc == null, act as default default_ip_assign)
    DHCP_IP_CHANGED,  ///< Change IP address by new ip from DHCP (if cbfunc == null, act as default default_ip_update)
    DHCP_IP_LEASED,   ///< Stand by
    DHCP_STOPPED      ///< Stop processing DHCP protocol
};

/*
 * @brief DHCP client initialization (outside of the main loop)
 * @param s   - socket number
 * @param buf - buffer for processing DHCP message
 * @param ip_assign   - callback func when IP is assigned from DHCP server first
 * @param ip_update   - callback func when IP is changed
 * @param ip_conflict - callback func when the assigned IP is conflict with others.
 */
void DHCP_init(uint8_t s, uint8_t* buf, void(*ip_assign)(void), void(*ip_update)(void), void(*ip_conflict)(void));

/*
 * @brief DHCP 1s Tick Timer handler
 * @note SHOULD BE register to your system 1s Tick timer handler 
 */
void DHCP_time_handler(void);

/*
 * @brief DHCP client in the main loop
 * @return    The value is as the follow \n
 *            @ref DHCP_FAILED     \n
 *            @ref DHCP_RUNNING    \n
 *            @ref DHCP_IP_ASSIGN  \n
 *            @ref DHCP_IP_CHANGED \n
 * 			  @ref DHCP_IP_LEASED  \n
 *            @ref DHCP_STOPPED    \n
 * @note This function is always called by you main task.
 */
uint8_t DHCP_run(void);

/*
 * @brief Stop DHCP processing
 * @note If you want to restart. call DHCP_init() and DHCP_run()
 */
void DHCP_stop(void);

/* Get Network information assigned from DHCP server */
/*
 * @brief Get IP address
 * @param ip  - IP address to be returned
 */
void DHCP_get_ip(uint8_t* ip);

/*
 * @brief Get Gateway address
 * @param ip  - Gateway address to be returned
 */
void DHCP_get_gateway_ip(uint8_t* ip);

/*
 * @brief Get Subnet mask value
 * @param ip  - Subnet mask to be returned
 */
void DHCP_get_subnet_mask(uint8_t* ip);

/*
 * @brief Get DNS address
 * @param ip  - DNS address to be returned
 */
void DHCP_get_dns_ip(uint8_t* ip);

/*
 * @brief Get the leased time by DHCP sever
 * @return unit 1s
 */
uint32_t DHCP_get_lease_time(void);

#ifdef __cplusplus
}
#endif

#endif    /* _DHCP_H_ */
