#include "project-base.hpp"
#include "dhcp-client.hpp"
#include "sipstack.hpp"

static void system_init(void);
static void fault_loop();



extern "C" void HardFault_Handler() {
    fault_loop();
}
extern "C" void SysTick_Handler(void) {
    HAL_IncTick();
}



#define CS_PIN    (GPIO_PIN_4)
#define RST_PIN   (GPIO_PIN_3)

uint8_t source_mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};


void w5500_cs_select() {
    HAL_GPIO_WritePin(GPIOA, CS_PIN, GPIO_PIN_RESET);
}
void w5500_cs_deselect() {
    HAL_GPIO_WritePin(GPIOA, CS_PIN, GPIO_PIN_SET);
}
uint8_t w5500_spi_read_byte() {
    uint8_t byte = 0;
    if (HAL_SPI_Receive(&hspi1, &byte, 1, 1000) != HAL_OK) {
        fault_loop();
    }
    return byte;
}
void w5500_spi_write_byte(uint8_t byte) {
    if (HAL_SPI_Transmit(&hspi1, &byte, 1, 1000) != HAL_OK) {
        fault_loop();
    }
}
void w5500_spi_read(uint8_t* buffer, uint16_t size) {
    if (HAL_SPI_Receive(&hspi1, buffer, size, 1000) != HAL_OK) {
        fault_loop();
    }
}
void w5500_spi_write(uint8_t* data, uint16_t size) {
    if (HAL_SPI_Transmit(&hspi1, data, size, 1000) != HAL_OK) {
        fault_loop();
    }
}


//  ***************************************************************************
/// @brief  Program entry point
//  ***************************************************************************
int main() {
    system_init();
    
    uint32_t clock = HAL_RCC_GetSysClockFreq();
    
    GPIO_InitTypeDef led = {0};
    led.Pin = GPIO_PIN_13;
    led.Mode = GPIO_MODE_OUTPUT_PP;
    led.Pull = GPIO_NOPULL;
    led.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOC, &led);
    
    GPIO_InitTypeDef hspi1_rst = {0};
    hspi1_rst.Pin = GPIO_PIN_3;
    hspi1_rst.Mode = GPIO_MODE_OUTPUT_PP;
    hspi1_rst.Pull = GPIO_NOPULL;
    hspi1_rst.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOA, &hspi1_rst);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    
    GPIO_InitTypeDef hspi1_cs = {0};
    hspi1_cs.Pin = GPIO_PIN_4;
    hspi1_cs.Mode = GPIO_MODE_OUTPUT_PP;
    hspi1_cs.Pull = GPIO_NOPULL;
    hspi1_cs.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOA, &hspi1_cs);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    
    GPIO_InitTypeDef hspi1_sck = {0};
    hspi1_sck.Pin = GPIO_PIN_5;
    hspi1_sck.Mode = GPIO_MODE_AF_PP;
    hspi1_sck.Pull = GPIO_NOPULL;
    hspi1_sck.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOA, &hspi1_sck);
    
    GPIO_InitTypeDef hspi1_miso = {0};
    hspi1_miso.Pin = GPIO_PIN_6;
    hspi1_miso.Mode = GPIO_MODE_AF_INPUT;
    hspi1_miso.Pull = GPIO_NOPULL;
    hspi1_miso.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOA, &hspi1_miso);
    
    GPIO_InitTypeDef hspi1_mosi = {0};
    hspi1_mosi.Pin = GPIO_PIN_7;
    hspi1_mosi.Mode = GPIO_MODE_AF_PP;
    hspi1_mosi.Pull = GPIO_NOPULL;
    hspi1_mosi.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOA, &hspi1_mosi);
    
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        fault_loop();
    }
    
    // Reset W5500 chip
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, RST_PIN, GPIO_PIN_SET);
    HAL_Delay(100);
    
    reg_wizchip_cs_cbfunc(w5500_cs_select, w5500_cs_deselect);
	reg_wizchip_spi_cbfunc(w5500_spi_read_byte, w5500_spi_write_byte);
    reg_wizchip_spiburst_cbfunc(w5500_spi_read, w5500_spi_write);
    
    uint8_t memsize[2][8] = { { 2, 2, 2, 2, 2, 2, 2, 2 }, { 2, 2, 2, 2, 2, 2, 2, 2 } };
	if (ctlwizchip(CW_INIT_WIZCHIP, (void*)memsize) == -1) {
		fault_loop();
	}
    
    uint8_t data = 0;
    if (ctlwizchip(CW_GET_PHYLINK, (void*)&data) == -1) {
        fault_loop();
    }
    if (data == PHY_LINK_OFF) {
        asm("nop");
    }
    
   
    dhcp_client_t dhcp_client;
    dhcp_client.init();

    sipstack_t sipstack;
    sipstack.init();
 
    while (true) {
        HAL_Delay(1000);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        dhcp_client.tick();
        sipstack.tick();
    }
}

//  ***************************************************************************
/// @brief  System initialization
//  ***************************************************************************
static void system_init(void) {
    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();
    
    HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}
static void fault_loop() {
    while(1) {
        asm("nop");
    }
}
