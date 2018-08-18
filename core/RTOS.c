#include <stdint.h>
#include <string.h>

#include "projectDefines.h"
#include "adc.h"
#include "timerHal.h"
#include "spiHal.h"
#include "sampler.h"
#include "zigbee.h"
#include "RTOS.h"
#include "adc.h"

currentContext_s currentContext;

void (*stateFnPtr[TOTAL_AMOUNT_OF_STATES])();	//function pointer that we will use to switch functions

static void initContext()
{
	memset(&currentContext,0,sizeof(currentContext_s));
}

static void initFncPtrs()
{
	stateFnPtr[STATE_CHARGE_CAP] = stateChargeCap;
}



states_t nextState(void)
{
	
}	

void stateChargeCap()
{
	while(getCapVoltage() < VCAP_TARGET_SAMPLE)
	{
			sleepWFImultiplesOf10ms(5);
	}	
}

//this is the brain of the design - once this is called it will never finish.
void kernal()
{
		initContext(); //zero-out structure used to keep track of state
		initFncPtrs();
	  (*stateFnPtr[0])();
}
