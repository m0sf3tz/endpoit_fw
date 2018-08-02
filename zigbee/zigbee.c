#include "zigbee.h"
#include "spiHal.h"
#include "gpioHal.h"
#include "timerHal.h"
#include "uartHal.h"


#define USART_DOZE_PIN    	                  GPIO_PIN_8
#define USART_DOZE_PORT                       GPIOB

void ZIGBEE_DOZE()
{
	gpioSetReset(USART_DOZE_PORT,USART_DOZE_PIN, GPIO_PIN_SET);
}


void ZIGBEE_WAKE()
{
	gpioSetReset(USART_DOZE_PORT,USART_DOZE_PIN, GPIO_PIN_RESET);
}



void zigbeeWrite(const char * dat, int len)
{
	ZIGBEE_WAKE();
	
	timerDelayUs(14000);
	uartPut(dat,len);
	
	ZIGBEE_DOZE();
}
