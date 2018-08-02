#include "timerHal.h"
#include "stm32l0xx_hal_rcc.h"
#include "stm32l0xx_hal_cortex.h"
#include "stm32l0xx_hal_tim.h"
#include <stdbool.h>

static RCC_OscInitTypeDef rccHandle;
static TIM_HandleTypeDef  timerHandle;
static TIM_HandleTypeDef  timerHandle21;

static volatile bool generalTimerDone;


//general timer (wait and sleep)
void TIM2_IRQHandler(void)
{
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
	timerHandle.Instance->CR1  = (timerHandle.Instance->CR1 & ~(1<<TIM_CR1_CEN_Pos)); 	  	//disable timer
	timerHandle.Instance->SR   = (timerHandle.Instance->SR  & ~(1<<TIM_SR_UIF_Pos)); 	    	//clear interrupt bit
	generalTimerDone = true;
}


//not set up...
void SysTick_Handler()
{
	//while(1);
}

/*
*  set up MSI clock to 4.194Mhz.
*/
void initTimerRcc()
{
	rccHandle.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	rccHandle.MSIState       = RCC_MSI_ON;
	rccHandle.MSIClockRange  = RCC_ICSCR_MSIRANGE_6; /*!< MSI = 4.194 MHz   */
	HAL_RCC_OscConfig(&rccHandle);
}

//tim2
void timerInit()
{
  /* TIMx Peripheral clock enable */
  __HAL_RCC_TIM2_CLK_ENABLE();
  
  /* Set the TIM2 priority */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  
  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
    
	timerHandle.Instance = TIM2; //SUPER IMPORTANT
	
}

void timerInitTim21()
{
	  __HAL_RCC_TIM21_CLK_ENABLE();
		timerHandle21.Instance = TIM21; 
}


void sleepWFImultiplesOf10ms(uint16_t multiplesOf10ms)
{
	if(multiplesOf10ms > 15)
		while(1)
	
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn); 
	timerHandle.Instance->SR   = (timerHandle.Instance->SR  & ~(1<<TIM_SR_UIF_Pos)); 		//clear interrupt bit

		
	timerHandle.Instance->CNT  = 0; //zero out timer.
	timerHandle.Instance->PSC  = 10;																						    //prescaler = 0
	timerHandle.Instance->ARR  = 0x1000 * multiplesOf10ms; 											  //auto reload
	timerHandle.Instance->EGR  = (timerHandle.Instance->EGR | TIM_EGR_UG); 	  	//generate update event - "resets timer - requierd to reload PSC"

	timerHandle.Instance->DIER = (timerHandle.Instance->DIER | TIM_DIER_UIE);   //enable interrupt
	timerHandle.Instance->CR1  = (timerHandle.Instance->CR1 | TIM_CR1_CEN); 		//enable timer
	
	generalTimerDone = false;
	
		
	while(!generalTimerDone)
	{
		__WFI();
	}
}




void sleepWFImultiplesOf100ms(uint16_t multiplesOf100ms)
{
	if(multiplesOf100ms > 15)
		while(1)
	
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn); 
	timerHandle.Instance->SR   = (timerHandle.Instance->SR  & ~(1<<TIM_SR_UIF_Pos)); 		//clear interrupt bit

		
	timerHandle.Instance->CNT  = 0; //zero out timer.
	timerHandle.Instance->PSC  = 100;																						    //prescaler = 0
	timerHandle.Instance->ARR  = 0x1000 * multiplesOf100ms;												//auto reload
	timerHandle.Instance->EGR  = (timerHandle.Instance->EGR | TIM_EGR_UG); 		//generate update event - "resets timer - requierd to reload PSC"

	timerHandle.Instance->DIER = (timerHandle.Instance->DIER | TIM_DIER_UIE);   //enable interrupt
	timerHandle.Instance->CR1  = (timerHandle.Instance->CR1 | TIM_CR1_CEN); 		//enable timer
	
	generalTimerDone = false;
	
		
	while(!generalTimerDone)
	{
		__WFI();
	}
		
}




void sleepWFImultiplesOf1000ms(uint16_t multiplesOf1000ms)
{
	if(multiplesOf1000ms > 15)
		while(1)
	
		
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn); 


	timerHandle.Instance->CNT  = 0; //zero out timer.
	timerHandle.Instance->PSC  = 1000;																						    //prescaler = 0
	timerHandle.Instance->ARR  = 0x1000 * multiplesOf1000ms; 											  //auto reload
	timerHandle.Instance->EGR  = (timerHandle.Instance->EGR | TIM_EGR_UG); 		//generate update event - "resets timer - requierd to reload PSC"

	timerHandle.Instance->DIER = (timerHandle.Instance->DIER | TIM_DIER_UIE);   //enable interrupt
	timerHandle.Instance->CR1  = (timerHandle.Instance->CR1 | TIM_CR1_CEN); 		//enable timer

	generalTimerDone = false;
	
		
	while(!generalTimerDone)
	{
		__WFI();
	}

		
}


void timerBusyLoop(uint32_t loops)
{
	while(loops)
	{
		loops--;
	}
}

//assumes we are using one the onboard RC oscillator - uses tim21
void timerDelayUs(uint16_t us)
{	
	
	uint32_t sysClock = HAL_RCC_GetSysClockFreq();
	uint32_t ticksPerUs = sysClock / 1000000;
	
	if(us*ticksPerUs > 0xFFFF)
	{
		while(1)
		{
			//whoop - can't support this feature...
		}
	}
	
	if (us < 50)
	{
		while(1)
		{
			//whoop - too small..
		}
	}
	
	if ( 	rccHandle.MSIClockRange != RCC_ICSCR_MSIRANGE_6)
	{
		while(1)
		{
			//need to calibrate for other ranges..
		}
	}
	
	us = us - 30; //correct for some overhead and offset... adjusted at 4.2MHz...
	
	timerHandle21.Instance->CNT  = 0; //zero out timer.
	timerHandle21.Instance->PSC  = 0;																						    //prescaler = 0
	timerHandle21.Instance->CR1  = (timerHandle21.Instance->CR1 | TIM_CR1_CEN); 		//enable timer

	
	while(timerHandle21.Instance->CNT <= us*ticksPerUs)
	{
		//chill...
	}
		timerHandle21.Instance->CR1  = (0); 																					//disable timer

}

void timerDelayUsDirty(delayConstants_e delay)
{
	if ( 	rccHandle.MSIClockRange == RCC_ICSCR_MSIRANGE_6)
	{
		if (delay == US_DELAY_10US)
		{
			int x = 1;
			while(x--)
			{
			}		
		}
	}
	else
	{
		while(1)
		{
			//need to calibrate...
		}
	}
}
	


