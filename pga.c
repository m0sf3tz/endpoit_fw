#include "pga.h"
#include "spiHal.h"
#include "stm32l0xx_hal_gpio.h"


void setPgaGain(pgaGainSwitch_e gain)
{
	//byte0 = 0b010_0000_0 //0x40
	//byte1 = gain
	uint16_t val = (0x40 << 8 | gain);
	
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_RESET);

	spiWrite((uint8_t*)&val, 1, SPI_ANALOG);

	HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_SET);

}
