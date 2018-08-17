#include <stdint.h>
#include "projectDefines.h"
#include "MC23A1024.h"
#include "adc.h"
#include "timerHal.h"
#include "spiHal.h"
#include "sampler.h"
#include "zigbee.h"
#include "cpuHal.h"
#include "gpioHal.h"
#include "sectorLogic.h"

static uint16_t 			    adcSamples   [ADC_SAMPLES_PER_BLOCK];
volatile static char      txUartSector [TRASMIT_BLOCK_SIZE   ];

static const int spiBlock = 50;	//random value - whatever - as long as it's not zero...

void sectorSetHeader(bool initial)
{
		if(initial)
		{
			txUartSector[NEW_TRASMITION_HEADER_B0_INDEX] = NEW_TRASMITION_HEADER_B0;
			txUartSector[NEW_TRASMITION_HEADER_B1_INDEX] = NEW_TRASMITION_HEADER_B1;
			txUartSector[NEW_TRASMITION_HEADER_B2_INDEX] = NEW_TRASMITION_HEADER_B2;
			txUartSector[NEW_TRASMITION_HEADER_B3_INDEX] = NEW_TRASMITION_HEADER_B3;
			txUartSector[NEW_TRASMITION_HEADER_B4_INDEX] = NEW_TRASMITION_HEADER_B4;
		}
		else
		{
			txUartSector[TRASMITION_HEADER_B0_INDEX]  = TRASMITION_HEADER_B0;
			txUartSector[TRASMITION_HEADER_B1_INDEX]  = TRASMITION_HEADER_B1;
			txUartSector[TRASMITION_HEADER_B2_INDEX]  = TRASMITION_HEADER_B2;
			txUartSector[TRASMITION_HEADER_B3_INDEX]  = TRASMITION_HEADER_B3;
			txUartSector[TRASMITION_HEADER_B4_INDEX]  = TRASMITION_HEADER_B4;
		}
}

void sectorSetSequenceId(uint16_t sequence)
{
		txUartSector[SEQUENCE_ID_B0_INDEX] = (sequence & 0xFF);
		txUartSector[SEQUENCE_ID_B1_INDEX] = ((sequence >> 8) & 0xFF);
}

void sectorSetCapVoltage(uint16_t voltage)
{
		txUartSector[CAP_VOLTAGE_B0_INDEX] = (voltage & 0xFF);
		txUartSector[CAP_VOLTAGE_B1_INDEX] = ((voltage >> 8) & 0xFF);
}

void sectorSetEnergyQaulity(uint8_t energyQuality)
{
		txUartSector[ESTIMATED_ENERGY_QUALITY_INDEX] = energyQuality;
}

void sectorSetCRC(uint16_t crc)
{
		txUartSector[CRC_B0_INDEX] = (crc & 0xFF);
		txUartSector[CRC_B1_INDEX] = ((crc >> 8) & 0xFF);
}


void sectorSetTerminator(bool final)
{
		if(final)
		{
			txUartSector[FINAL_STOP_SEQUENCE_B0_INDEX] = FINAL_STOP_SEQUENCE_B0;
			txUartSector[FINAL_STOP_SEQUENCE_B1_INDEX] = FINAL_STOP_SEQUENCE_B1;
  		txUartSector[FINAL_STOP_SEQUENCE_B2_INDEX] = FINAL_STOP_SEQUENCE_B2;
			txUartSector[FINAL_STOP_SEQUENCE_B3_INDEX] = FINAL_STOP_SEQUENCE_B3;
			txUartSector[FINAL_STOP_SEQUENCE_B4_INDEX] = FINAL_STOP_SEQUENCE_B4;

		}
		else
		{
			txUartSector[STOP_SEQUENCE_B0_INDEX] = STOP_SEQUENCE_B0;
			txUartSector[STOP_SEQUENCE_B1_INDEX] = STOP_SEQUENCE_B1;
			txUartSector[STOP_SEQUENCE_B2_INDEX] = STOP_SEQUENCE_B2;
			txUartSector[STOP_SEQUENCE_B3_INDEX] = STOP_SEQUENCE_B3;
			txUartSector[STOP_SEQUENCE_B4_INDEX] = STOP_SEQUENCE_B4;
		}
}


bool memToBuffer(uint16_t block )
{
	initRcc32mhz();
	
	if( (block) >= (SPI_TOTAL_SRAM_TOTAL_BLOCKS) )
	{
		ASSERT(0);
	}
		
	spiMemPrepSequentialRead(block);
	uint32_t byteOffset = DATA_0_INDEX;
	
	while(byteOffset!=DATA_0_INDEX+DATA_SIZE)
	{
		txUartSector[byteOffset] = readByteSpiLld(SPI_MEM);
		byteOffset++;
	}
	
	spiMemFinalizeSequential();
	
	initRcc4mhz();

	return true;
}	


bool fillBlockMenuShim()
{
	fillBlock(spiBlock);
	return true;
}

//single block
bool fillBlock(uint16_t block)
{
	uint16_t tmpVal,i;
	spiMemPrepSequentialWrite(block);
	
	i =0;
	while(i!=ADC_SAMPLES_PER_BLOCK)
	{
		tmpVal = getAdcSample();
		
		writeByteSpiLld(SPI_MEM,tmpVal);
		writeByteSpiLld(SPI_MEM,tmpVal>>8);
		
		adcSamples[i] = tmpVal; //just used for debug
				
		timerDelayUsDirty(US_DELAY_10US);
		i++;
	}
	
	spiMemFinalizeSequential();

	return true;
}


//menu only accepts functions with no parements 
bool memToBufferShim()
{
	memToBuffer(spiBlock);
	return true;
}


bool bufferToZigbeeShim()
{
	bufferToZigbee(spiBlock);
	return true;
}

bool bufferToZigbee(uint16_t block )
{
	//deprecated
	memToBuffer(block);
	zigbeeWrite( (const char*)adcSamples, SECTOR_DATA_SIZE);	
	return true;
}	

//reads block 0-8 into the data region of a tx-buffer and zigbees it up **
bool sectorBufToZigbee()
{
  	memToBuffer(0);
	  zigbeeWrite( (const char*)txUartSector, TRASMIT_BLOCK_SIZE);		
	  return true;
}


bool multiSectorSpiMemFillShim()
{
	 taskSample();
   return 0;
}
