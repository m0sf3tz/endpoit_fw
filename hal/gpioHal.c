#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal.h"
#include <stdbool.h>

#define DEBUG_PIN                       		        GPIO_PIN_5
#define DEBUG_PIN_GPIO_PORT                 	      GPIOB
#define DEBUG_PIN_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOB_CLK_ENABLE()  



void initDebugGpio()
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  //enable clocks to GPIO units 
	DEBUG_PIN_GPIO_CLK_ENABLE();

  //setup green LED
  GPIO_InitStruct.Pin   = DEBUG_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init    (DEBUG_PIN_GPIO_PORT, &GPIO_InitStruct);
  HAL_GPIO_WritePin(DEBUG_PIN_GPIO_PORT, DEBUG_PIN, GPIO_PIN_RESET); 
}


void debugGpio()
{
	HAL_GPIO_TogglePin(DEBUG_PIN_GPIO_PORT, DEBUG_PIN);
}


void gpioSetReset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, bool value)
{
	if(value == GPIO_PIN_SET)
	{
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}
	else
	{		
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	}
}

		
