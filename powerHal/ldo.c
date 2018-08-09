#include <stdbool.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_gpio.h"
#include "zigbee.h"

#include "ldo.h"
#include "spiHal.h"
#include "uartHal.h"

/* Definition for USARTx Pins */
#define USART_DOZE_PIN    	                  GPIO_PIN_8
#define USART_DOZE_PORT                       GPIOB

bool enableSamplingSupply()
{
	 HAL_GPIO_WritePin(SAMPLNG_SUPPLY_PORT, SAMPLNG_SUPPLY_PIN, GPIO_PIN_SET); 
	 //initUartClocksAndPins();
	 return true;
}

bool disableSamplingSupply()
{
	 HAL_GPIO_WritePin(SAMPLNG_SUPPLY_PORT, SAMPLNG_SUPPLY_PIN, GPIO_PIN_RESET); 
   //deinitUartPins();
	 return true;
}

void iniLdoClocksAndPins()
{
	LDO_CLK_ENABLE();

	GPIO_InitTypeDef  GPIO_InitStructGpio;

  GPIO_InitStructGpio.Pin   = SAMPLNG_SUPPLY_PIN;
  GPIO_InitStructGpio.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructGpio.Pull  = GPIO_NOPULL;
  GPIO_InitStructGpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(SAMPLNG_SUPPLY_PORT, &GPIO_InitStructGpio);
  HAL_GPIO_WritePin(SAMPLNG_SUPPLY_PORT, SAMPLNG_SUPPLY_PIN, GPIO_PIN_RESET); 
		
}
