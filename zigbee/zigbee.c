#include "zigbee.h"
#include "spiHal.h"
#include "gpioHal.h"
#include "timerHal.h"
#include "uartHal.h"
#include "ldo.h"
#include "pga.h"

#define USART_DOZE_PIN    	                  GPIO_PIN_8
#define USART_DOZE_PORT                       GPIOB
#define USART_DOZE_GPIO_CLK_ENABLE()       	  __HAL_RCC_GPIOA_CLK_ENABLE() 
//these two are bools just to we don't need a shim for the menue (otherwise.. the "test" would fail"

bool initZigbeeGpioPins()
{
	USART_DOZE_GPIO_CLK_ENABLE();         	
	
	GPIO_InitTypeDef  GPIO_InitStructGpio;

  GPIO_InitStructGpio.Pin   = USART_DOZE_PIN;
  GPIO_InitStructGpio.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructGpio.Pull  = GPIO_NOPULL;
  GPIO_InitStructGpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(USART_DOZE_PORT, &GPIO_InitStructGpio);
  HAL_GPIO_WritePin(USART_DOZE_PORT, USART_DOZE_PIN, GPIO_PIN_SET); 
	
	return true;
}

bool ZIGBEE_DOZE()
{
	gpioSetReset(USART_DOZE_PORT,USART_DOZE_PIN, GPIO_PIN_SET);
	return true;
}


bool ZIGBEE_WAKE()
{
	gpioSetReset(USART_DOZE_PORT,USART_DOZE_PIN, GPIO_PIN_RESET);
	return true;
}



void zigbeeWrite(const char * dat, int len)
{
	ZIGBEE_WAKE();
	
	timerDelayUs(15000);
	uartPut(dat,len);
	
	ZIGBEE_DOZE();
}

bool zigbeeSleep()
{
	//put the doze pin as an inpup
	GPIO_InitTypeDef  GPIO_InitStructGpio;
  GPIO_InitStructGpio.Pin   = USART_DOZE_PIN;
  GPIO_InitStructGpio.Mode  = GPIO_MODE_INPUT;
  HAL_GPIO_Init(USART_DOZE_PORT, &GPIO_InitStructGpio);
	
	deinitUartPinsZigbee();
	
	return true;
}

bool zigbeeWake()
{
	//put the doze pin as an output again
	GPIO_InitTypeDef  GPIO_InitStructGpio;
  GPIO_InitStructGpio.Pin   = USART_DOZE_PIN;
  GPIO_InitStructGpio.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructGpio.Pull  = GPIO_NOPULL;
  GPIO_InitStructGpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(USART_DOZE_PORT, &GPIO_InitStructGpio);
  HAL_GPIO_WritePin(USART_DOZE_PORT, USART_DOZE_PIN, GPIO_PIN_SET); 
	
	initUartPinsZigbee();
	
	return true;
}



bool zigbeeTestSendIncrementing()
{
	
	char testBuff[256];
	int i;
	for(i = 0; i < 256; i++)
	{
		testBuff[i] = i;
	}
	/*
	enableSamplingSupply();
	
	timerDelayUs(200);

	ZIGBEE_WAKE();
	*/
	
	timerDelayUs(14000);
	
	uartPut(testBuff,256);

/*
	ZIGBEE_DOZE();
	
	disableSamplingSupply();
	*/
	return true;
	
}
