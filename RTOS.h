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
	
	uint32_t capVolate;
	
	bool 	   validSampleStored;
	bool     currentlySampling;
	
	uint32_t totalBytesSampeld;
	uint32_t bytesRemaning;
}currentContext_s;
	
	
states_t nextState(void);
