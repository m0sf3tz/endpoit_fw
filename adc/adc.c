#include "adc.h"
#include "spiHal.h"
#include "gpioHal.h"
#include "timerHal.h"


void adcSelect()
{
	gpioSetReset(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); 
}

void adcDeSelect()
{
	gpioSetReset(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); 
}

uint16_t getAdcSample()
{
	 adcSelect();
	 timerDelayUsDirty(US_DELAY_10US);
	 adcDeSelect();
	 timerDelayUsDirty(US_DELAY_10US);

	 return readByteSpiLld(SPI_ADC);
}

