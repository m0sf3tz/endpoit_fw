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

static uint16_t 			    adcSamples [ADC_SAMPLES_PER_BLOCK];
volatile static char      txUartBlock[BLOCK_UART_ZIGBEE];

static const int spiBlock = 50;	//random value - whatever - as long as it's not zero...

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

bool memToBuffer(uint16_t block )
{
	
	if( (block) >= (SPI_TOTAL_SRAM_TOTAL_BLOCKS) )
	{
		ASSERT(0);
	}
		
	spiMemPrepSequentialRead(block);
	uint32_t byteCount = 0;
	
	while(byteCount!=BLOCK_UART_ZIGBEE)
	{
		txUartBlock[byteCount] = readByteSpiLld(SPI_MEM);
		byteCount++;
	}
	
	spiMemFinalizeSequential();
	
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
	zigbeeWrite( (const char*)adcSamples, BLOCK_UART_ZIGBEE);	
	return true;
}	


bool multiSectorSpiMemFillShim()
{
	 taskSample();
   return 0;
}


void taskSample(void)
{
	initRcc32mhz();
	multiSectorSpiMemFill(MOTOR_EYE_SAMPLE_BLOCKS,FIRST_SECTOR_SPI);
	initRcc4mhz(); 
}


//multi block
//at 32Mhz this samples at 2.1Khz
bool multiSectorSpiMemFill(uint16_t numOfBlocks, uint16_t block)
{

	uint16_t tmpVal, i;
	spiMemPrepSequentialWrite(block);
	
	i =0;
	while(i!=ADC_SAMPLES_PER_BLOCK*numOfBlocks)
	{
		tmpVal = getAdcSample();
		
		writeByteSpiLld(SPI_MEM,tmpVal);
		writeByteSpiLld(SPI_MEM,tmpVal>>8);
					
		i++;
		debugGpio();
	}
	
	spiMemFinalizeSequential();

	return 0;
}

bool streamAllSPiZigbee()
{
	int i = 0;
	while(i!=MOTOR_EYE_SAMPLE_BLOCKS)
	{
		memToBuffer(i);
		zigbeeWrite( (const char*)txUartBlock, BLOCK_UART_ZIGBEE);	
		
		i++;
	}
	return true;
}	
