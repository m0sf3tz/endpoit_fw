#include "stm32l0xx_hal_rcc.h"
#include <stdint.h>


typedef enum 
{
	US_DELAY_10US
}delayConstants_e;

void initTimerRcc(void);
void timerInit(void);
void timerInitTim21(void);

void TIM2_IRQHandler(void);
void timerBusyLoop(uint32_t);

void sleepWFImultiplesOf10ms(uint16_t);
void sleepWFImultiplesOf100ms(uint16_t);
void sleepWFImultiplesOf1000ms(uint16_t);

/*
 * use this to have accurate delays... uses TIM21.
*/


void timerDelayUs(uint16_t);
void timerDelayUsDirty(delayConstants_e);
