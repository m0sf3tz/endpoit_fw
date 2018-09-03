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
#include "menu.h" //used for debug-print functions
#include "globals.h"
#include "sectorLogic.h"
#include "pga.h"

currentContext_s currentContext;
void (*stateFnPtr[TOTAL_AMOUNT_OF_STATES])();	//function pointer that we will use to switch functions


static void initContext()
{
	memset(&currentContext,0,sizeof(currentContext_s));
	currentContext.targetCapVoltage = VCAP_TARGET_SAMPLE; // assume the first thing we will do is take a sample
}

static void initFncPtrs()
{
	stateFnPtr[STATE_SAMPLE] = stateSample;
	stateFnPtr[STATE_CREATE_TX_BUFFER] = stateCreateTxBuffer;
	stateFnPtr[STATE_TRANSMIT] = stateTrasmit;

}

void stateSample()
{
	pgaGainSwitch_e gainEncoded; //this is the encoded value, not the actual gain (ie, encoded gain of 3 == gain of 5)
	
	while(getCapVoltage() < VCAP_TARGET_SAMPLE)
	{
			sleepWFImultiplesOf10ms(5);
	}	
	
	//turn on pertinent rails, sample ADC, copy into SPI memory.
	//we also quart what gain the gain-select FW chose
	gainEncoded = taskSample();
	printGain(gainEncoded);
	currentContext.pgaGain = gainTranslateMatrix[gainEncoded];
	
	//come up with a random sequence ID using the ADC and a hash functin
	currentContext.sequenceId = hash16(getCapVoltage());

	//setup the next state
	currentContext.currentState = STATE_CREATE_TX_BUFFER;  				//next state
}


void stateCreateTxBuffer()
{
	while(getCapVoltage() < VCAP_TARGET_CREATE_TX_BUFF)
	{
			sleepWFImultiplesOf10ms(5);
	}	
	//create a TX buffer
  createTxSectorTask(currentContext.currentSector, currentContext.sequenceId, NULL, getCapVoltage(), currentContext.pgaGain);
	

	currentContext.currentState = STATE_TRANSMIT;  				//next state
}


void stateTrasmit()
{
	while(getCapVoltage() < VCAP_TARGET_TRANSMIT)
	{
			sleepWFImultiplesOf10ms(5);
	}	
	//zigbees up exiting uart-transmit buffer
	zigbeeTransmitTask();
	
	currentContext.currentSector++;
	
	//if we have finished sending up the current sample, get another sample,
	//otherwise fetch the next sector from SPI memory and send it up
	if(currentContext.currentSector == SECTORS_PER_SAMPLE)
	{
			currentContext.currentState = STATE_SAMPLE;  				//next state
		  currentContext.currentSector = 0;
	}
	else
	{
			currentContext.currentState = STATE_CREATE_TX_BUFFER;  	//next state
	}
}



//this is the brain of the design - once this is called it will never finish.
void kernal()
{
	clearScreen(); //zero-out screen if there is anything on there
	initContext(); //zero-out structure used to keep track of state
	initFncPtrs();
	while(true)
	{
		printState((int)currentContext.currentState, getCapVoltage());	
		//calls worker "thread"
		//updates the next thread to be called
		(*stateFnPtr[currentContext.currentState])();	
	}
		
		
		
}
