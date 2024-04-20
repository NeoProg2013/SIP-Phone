#include "project-base.hpp"


SPI_HandleTypeDef hspi1 = {};


void delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}