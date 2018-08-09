#include "stm32l0xx_hal_rcc.h"
#include <stdint.h>


RCC_OscInitTypeDef rccHandle;

void initRcc4mhz()
{
	rccHandle.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
	rccHandle.MSIState            = RCC_MSI_ON;
	rccHandle.MSIClockRange  	    = RCC_ICSCR_MSIRANGE_6; /*!< MSI = 4.194 MHz   */
	//rccHandle.MSICalibrationValue = 0x2F;
	HAL_RCC_OscConfig(&rccHandle);
}

void initRcc65khz()
{
	rccHandle.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
	rccHandle.MSIState            = RCC_MSI_ON;
	rccHandle.MSIClockRange  	    = RCC_ICSCR_MSIRANGE_0; /*!< MSI = 65khz   */
	//rccHandle.MSICalibrationValue = 0x2F;
	HAL_RCC_OscConfig(&rccHandle);
}
