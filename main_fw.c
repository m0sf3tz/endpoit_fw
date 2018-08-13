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
#include "zigbee.h"
#include "cpuhal.h"
#include "pga.h"

//@major TODOS that will BREAK YOUR BOARD - DE-INIT ADC SPI to be comleted


int main()
{
	initRcc4mhz();
	
	timerInit();
	//initSysTick();
	
	/****************************************/
	//		WILL BREAK UUART 									
  //****************************************/
	/****************************************/
	//		WILL BREAK UUART 									
  //****************************************/
  //initDebugGpio();
	/****************************************/
	//		WILL BREAK UUART 									
  //****************************************/
	/****************************************/
	//		WILL BREAK UUART 									
  //****************************************/


	initUart();
  timerInitTim21();
	initSpis();
	initZigbeeGpioPins();
	iniLdoClocksAndPins();
	enableSamplingSupply();
	initAdc();
	mainMenu_f();
	
}

