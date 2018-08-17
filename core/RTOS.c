#include <stdint.h>
#include <string.h>

#include "projectDefines.h"
#include "adc.h"
#include "timerHal.h"
#include "spiHal.h"
#include "sampler.h"
#include "zigbee.h"

#include "RTOS.h"

currentContext_s currentContext;


void initContext()
{
	memset(&currentContext,0,sizeof(currentContext_s));
}



states_t nextState(void)
{
	
}	

//this is the brain of the design - once this is called it will never finish.
void kernal()
{
		initContext(); //zero-out structure used to keep track of state
	
}
