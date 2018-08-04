#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_cortex.h"

#include "led.h"
#include "spiHal.h"
#include "timerHal.h"
#include "gpioHal.h"
#include "uartHal.h"
#include "menu.h"
#include "MC23A1024.h"
#include "adc.h"
#include "ldo.h"

int main()
{
	initTimerRcc();
	//timerInit();
	//initLeds();		//fights with UART SCK....
	initUart();
  //timerInitTim21();
	initSpis();
	
	/*
	iniLdoClocksAndPins();
	initAdc();
	getAdcSample();
	*/
	
	enableSamplingSupply();
	

	mainMenu_f();
}

