#include <stdint.h>
#pragma once

typedef enum 
{
	STATE_CHARGE_CAP,
	STATE_TRANSMIT,
	STATE_CALC_CRC,
	STATE_SAMPLE
}states_t;

typedef struct
{
	states_t currentState;
	uint16_t sequenceId;

	uint32_t capVolate;
	
	bool 	   validSampleStored;
	bool     currentlySampling;
	
	uint32_t blocksRemianing;
}currentContext_s;
	
	
states_t nextState(void);
