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
#include "sectorLogic.h"
#include "rtos.h"

#define MENU_ENABLE 1

//@major TODOS that will BREAK YOUR BOARD - DE-INIT ADC SPI to be comleted
//PGA gain selector needs to be revamped once we start using a real ADC
//seens like the sample rail is taking a bit too long to stabilize (?)
int main()
{
	initRcc4mhz();
	
	timerInit();
	initUart();
  timerInitTim21();
	initSpis();
	initZigbeeGpioPins();
	iniLdoClocksAndPins();
	disableSamplingSupply();
	initAdc();
	
#if MENU_ENABLE
	mainMenu_f();
#else
	kernal();
#endif
}

