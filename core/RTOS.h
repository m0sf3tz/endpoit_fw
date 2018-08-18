#include <stdint.h>
#pragma once


//********************************************************************************//
//								UPDATE US TOGETHER UNLESS YOU LIKE PAIN
//********************************************************************************//

typedef enum 
{			//DON'T FORGET TO UPDATE TOTAL_AMOUNT_OF_STATES!!!!
	STATE_CHARGE_CAP,
	STATE_TRANSMIT,
	STATE_CALC_CRC,
	STATE_SAMPLE
}states_t;
//DID YOU UPDATE ME?!
#define TOTAL_AMOUNT_OF_STATES 4
//********************************************************************************//
//								UPDATE US TOGETHER UNLESS YOU LIKE PAIN
//********************************************************************************//

typedef struct
{
	states_t currentState;
	uint16_t sequenceId;

	uint32_t capVoltage;
	
	bool 	   validSampleStored;
	bool     currentlySampling;
	
	uint32_t currentBlock;	
	
}currentContext_s;
	
	
states_t nextState(void);
void stateChargeCap(void);
void initContext(void);
void kernal(void);
