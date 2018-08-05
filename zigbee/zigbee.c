#include "zigbee.h"
#include "spiHal.h"
#include "gpioHal.h"
#include "timerHal.h"
#include "uartHal.h"
#include "ldo.h"

#define USART_DOZE_PIN    	                  GPIO_PIN_8
#define USART_DOZE_PORT                       GPIOB

//these two are bools just to we don't need a shim for the menue (otherwise.. the "test" would fail"
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
	
	timerDelayUs(14000);
	uartPut(dat,len);
	
	ZIGBEE_DOZE();
}

bool zigbeeTestSendIncrementing()
{
	
	char testBuff[256];
	int i;
	for(i = 0; i < 256; i++)
	{
		testBuff[i] = i;
	}
	enableSamplingSupply();
	
	timerDelayUs(200);

	ZIGBEE_WAKE();
	
	timerDelayUs(14000);
	
	//make a test buffer;
	
	uartPut(testBuff,256);
	
	ZIGBEE_DOZE();
	
	disableSamplingSupply();

	
	return true;
	
}
