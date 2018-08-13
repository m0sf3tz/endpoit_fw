#include "adc.h"
#include "spiHal.h"
#include "gpioHal.h"
#include "timerHal.h"
#include "stm32l0xx_hal_adc.h"
#include "projectDefines.h"
#include "globals.h"
#include "menu.h"
#include "uartHal.h"

static ADC_HandleTypeDef    		     AdcHandle;
static ADC_ChannelConfTypeDef        sConfig;

adcRead_s temp;

//vcap = 9.35*(DAC_READ_OUT/0xFFF)*2.5
//vadc = (DAC_READ_OUT/0xFFF)*2.5

void initAdc()
{
	  GPIO_InitTypeDef                 GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO clock ****************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /* ADC1 Periph clock enable */
  __HAL_RCC_ADC1_CLK_ENABLE();
  
  /*##- 2- Configure peripheral GPIO #########################################*/
  /* ADC3 Channel8 GPIO pin configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//this one is for the ADC attached to the cap
	GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	
	AdcHandle.Instance = ADC1;
  
  AdcHandle.Init.OversamplingMode         = ENABLE;
  AdcHandle.Init.Oversample.Ratio         = ADC_OVERSAMPLING_RATIO_32;
  AdcHandle.Init.Oversample.RightBitShift = ADC_RIGHTBITSHIFT_2;
  AdcHandle.Init.Oversample.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;
  AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;
  AdcHandle.Init.LowPowerFrequencyMode = ENABLE;
  AdcHandle.Init.LowPowerAutoWait      = DISABLE;
    
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
  AdcHandle.Init.SamplingTime          = ADC_SAMPLETIME_1CYCLE_5;
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ContinuousConvMode    = DISABLE;
  AdcHandle.Init.DiscontinuousConvMode = ENABLE;
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
 
  /* Initialize ADC peripheral according to the passed parameters */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    ASSERT(0);
  }
  
  
  //### - 2 - Start calibration ############################################ */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_SINGLE_ENDED) != HAL_OK)
  {
    while(1){}
  }
  
  /* ### - 3 - Channel configuration ######################################## */
	

	//vSignal
  sConfig.Channel = ADC_CHANNEL_6;    
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    ASSERT(0);
  }

	//vCap
  sConfig.Channel = ADC_CHANNEL_0;    
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    ASSERT(0);
  }
}

//unfortuantly since the ADC needs to watch 2 different channels everytime we need a sample we need to read both channels
uint16_t getAdcSample()
{
	HAL_ADC_Start(&AdcHandle);
	HAL_ADC_PollForConversion(&AdcHandle, 1000000);
	temp.adc =  HAL_ADC_GetValue(&AdcHandle);
	
	HAL_ADC_Start(&AdcHandle);
	HAL_ADC_PollForConversion(&AdcHandle, 1000000);
	temp.capVoltage =  HAL_ADC_GetValue(&AdcHandle);
	 
	return temp.capVoltage;
}


uint16_t getCapVoltage()
{
	sConfig.Channel = ADC_CHANNEL_0;    
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    ASSERT(0);
  }

	HAL_ADC_PollForConversion(&AdcHandle, 1000000);
	uint16_t retval =  HAL_ADC_GetValue(&AdcHandle);

	sConfig.Channel = ADC_CHANNEL_6;    
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    ASSERT(0);
  }
	return retval;
}

bool adcUnitTestOnDie()
{
	getAdcSample();
	
	uint16_t val =  temp.adc;

	clearScreen();
	printStars();
	printNewLine();
	
	char valString [4];
	
	UlToStr(valString, val, 4);
	
	char tmp[] = "ADC read a value of: ";
		
	uartPutMenu(tmp, sizeof(tmp));
	uartPutMenu(valString, 4);
	
	uartGetMenu(tmp,1);
	
	return true;

}
