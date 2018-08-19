#include <stdint.h>
#pragma once


//********************************************************************************//
//								UPDATE US TOGETHER UNLESS YOU LIKE PAIN - ALSO UPDATE MENU IN printState
//********************************************************************************//

typedef enum 
{			//DON'T FORGET TO UPDATE TOTAL_AMOUNT_OF_STATES!!!! //ALSO UPDATE MENU IN printState
	STATE_SAMPLE,
	STATE_CREATE_TX_BUFFER,  	//copy blocks from SPI into RAM, create CRC, add start, end headers, and power quality.
	STATE_TRANSMIT,
}states_t;
//DID YOU UPDATE ME?! //ALSO UPDATE MENU IN printState
#define TOTAL_AMOUNT_OF_STATES 3
//********************************************************************************//
//								UPDATE US TOGETHER UNLESS YOU LIKE PAIN ALSO UPDATE MENU IN printState
//********************************************************************************//

typedef struct
{
	states_t currentState;
	uint16_t sequenceId;
	uint32_t capVoltage;
	uint16_t targetCapVoltage;
	bool 	   validSampleStored;
	bool 	   txBufferCreated;
	bool 	   txBufferDrained;
	uint32_t currentBlock;	
	uint32_t currentSector;	
	uint8_t  pgaGain;	
}currentContext_s;
	

void nextState(void);

void stateCreateTxBuffer(void);
void stateSample(void);
void stateTrasmit(void);

void initContext(void);
void kernal(void);
