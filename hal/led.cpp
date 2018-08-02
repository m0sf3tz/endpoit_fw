#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal.h"


#define LED_GREEN_PIN                       		    GPIO_PIN_5
#define LED_GREEN_PIN_GPIO_PORT                     GPIOA
#define LED_GREEN_PIN_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()  
#define LED_GREEN_PIN_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()  



void initLeds()
{
	
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  //enable clocks to GPIO units 
	LED_GREEN_PIN_GPIO_CLK_ENABLE();

  //setup green LED
  GPIO_InitStruct.Pin   = LED_GREEN_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(LED_GREEN_PIN_GPIO_PORT, &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_GREEN_PIN_GPIO_PORT, LED_GREEN_PIN, GPIO_PIN_RESET); 

}


void toggleGreenLed()
{
	HAL_GPIO_TogglePin(LED_GREEN_PIN_GPIO_PORT, LED_GREEN_PIN);
}


void setGreenLed(bool status)
{
	if(status == true)
	{
		HAL_GPIO_WritePin(LED_GREEN_PIN_GPIO_PORT, LED_GREEN_PIN, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_GREEN_PIN_GPIO_PORT, LED_GREEN_PIN, GPIO_PIN_RESET); 
	}
}
