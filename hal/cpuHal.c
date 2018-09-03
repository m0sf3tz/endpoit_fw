#include "stm32l0xx_hal_rcc.h"
#include "stm32l0xx_hal_flash.h"

#include "timerHal.h"
#include "projectDefines.h"

#include <stdint.h>


RCC_OscInitTypeDef  rccHandle;
RCC_ClkInitTypeDef RCC_ClkInitStruct;

void initRcc4mhz()
{
	/* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
	
	rccHandle.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
	rccHandle.MSIState            = RCC_MSI_ON;
	rccHandle.HSIState					  = RCC_HSI_OFF;
	rccHandle.PLL.PLLState			  = RCC_PLL_NONE;
	rccHandle.MSIClockRange  	    = RCC_ICSCR_MSIRANGE_6; /*!< MSI = 4.194 MHz   */
	//rccHandle.MSICalibrationValue = 0x2F;
	if(HAL_RCC_OscConfig(&rccHandle) != HAL_OK)
	{
		   ASSERT(0);
	}
	
	/* -3- Select the MSI as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
	
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    ASSERT(0);
  }

  __HAL_RCC_HSI_CONFIG(RCC_HSI_OFF);	
}

void initRcc32mhz()
{
	  /* Enable Power Control clock */
  __HAL_RCC_HSI_CONFIG(RCC_HSI_ON);	
	
	timerDelayUsDirty(50);
	
	
	/* -2- Enable HSE Oscillator, select it as PLL source and finally activate the PLL */
  rccHandle.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  rccHandle.HSIState = RCC_HSI_ON;
  rccHandle.PLL.PLLState = RCC_PLL_ON;
  rccHandle.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  rccHandle.PLL.PLLMUL = RCC_PLL_MUL4;
  rccHandle.PLL.PLLDIV = RCC_PLL_DIV2; 
  rccHandle.HSICalibrationValue = 0x10;

	if(HAL_RCC_OscConfig(&rccHandle) != HAL_OK)
  {
    ASSERT(0);
  }
	
	
	/* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
	
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    ASSERT(0);
  }

 	__HAL_RCC_PWR_CLK_DISABLE();

}



void initRcc65khz()
{
	rccHandle.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
	rccHandle.MSIState            = RCC_MSI_ON;
	rccHandle.MSIClockRange  	    = RCC_ICSCR_MSIRANGE_0; /*!< MSI = 65khz   */
	//rccHandle.MSICalibrationValue = 0x2F;
	HAL_RCC_OscConfig(&rccHandle);
}

void initSysTick(void)
{
	#if DEBUG_MODE
	  //SysTick_Config(4300000/100);      /* Generate interrupt each 1 ms  */
	#endif
}
