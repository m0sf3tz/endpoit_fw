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




void taskSample(void)
{
	initRcc32mhz();
	multiSectorSpiMemFill(TOTAL_BLOCKS_IN_SAMPLE ,FIRST_BLOCK_SPI);
	initRcc4mhz(); 
}


//multi block
//at 32Mhz this samples at 2.1Khz
//@param numOfBlocks  total number of sectors to sample for
//@param block				the first block to write to, will auto increment

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
	}
	
	spiMemFinalizeSequential();

	return 0;
}



bool streamAllSPiZigbee()
{
	ASSERT(0); //don't call me....
/*
	int i = 0;
	while(i!=MOTOR_EYE_SAMPLE_BLOCKS)
	{
		memToBuffer(i);
		zigbeeWrite( (const char*)txUartSector, SECTOR_DATA_SIZE);	
		
		i++;
	}
	return true;
*/
}	
