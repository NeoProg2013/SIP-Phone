#ifndef _PROJECT_BASE_H_
#define _PROJECT_BASE_H_
#include "stm32f1xx_hal.h"
#include "wizchip_conf.h"
#include "socket.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <map>
#include <list>

namespace global_env {
    static const uint8_t DHCP_SOCKET = 1;
    static const uint8_t SIP_SOCKET = 2;

    static const uint16_t SIP_PORT = 5060;
}




extern SPI_HandleTypeDef hspi1;


extern void delay_ms(uint32_t ms);


#endif // _PROJECT_BASE_H_
