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
		}
		else
		{
			txUartSector[TRASMITION_HEADER_B0_INDEX]  = TRASMITION_HEADER_B0;
			txUartSector[TRASMITION_HEADER_B1_INDEX]  = TRASMITION_HEADER_B1;
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
		}
		else
		{
			txUartSector[STOP_SEQUENCE_B0_INDEX] = STOP_SEQUENCE_B0;
			txUartSector[STOP_SEQUENCE_B1_INDEX] = STOP_SEQUENCE_B1;
		}
}


bool memToBuffer(uint16_t block )
{
	
	if( (block) >= (SPI_TOTAL_SRAM_TOTAL_BLOCKS) )
	{
		ASSERT(0);
	}
		
	spiMemPrepSequentialRead(block);
	uint32_t byteOffset = DATA_0_INDEX;
	
	while(byteOffset!=SECTOR_DATA_SIZE)
	{
		txUartSector[byteOffset] = readByteSpiLld(SPI_MEM);
		byteOffset++;
	}
	
	spiMemFinalizeSequential();
	
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
	memToBuffer(block);
	zigbeeWrite( (const char*)adcSamples, SECTOR_DATA_SIZE);	
	return true;
}	


bool multiSectorSpiMemFillShim()
{
	 taskSample();
   return 0;
}
