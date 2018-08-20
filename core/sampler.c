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
#include "ldo.h"
#include "pga.h"
 
extern volatile  char      txUartSector [TRASMIT_BLOCK_SIZE];


//@returns - the gain the auto-gain FW selected
pgaGainSwitch_e taskSample(void)
{
	pgaGainSwitch_e gainEncoded;
	enableSamplingSupply();
	sleepWFImultiplesOf100ms(1);	//wait for supply to stabilize
	initRcc32mhz();
	gainEncoded = autoGainSelect();	//this function selected the correct gain to sample at 
	
	multiSectorSpiMemFill(TOTAL_BLOCKS_IN_SAMPLE ,FIRST_BLOCK_SPI);
	initRcc4mhz(); 
	disableSamplingSupply();
	return gainEncoded;
}


//multi block
//at 32Mhz this samples at 2.1Khz
//@param numOfBlocks  total number of sectors to sample for
//@param block				the first block to write to, will auto increment

bool multiSectorSpiMemFill(uint16_t numOfBlocks, uint16_t block)
{

	uint32_t tmpVal, i;
	spiMemPrepSequentialWrite(block);
	
	i =0;
	while(i!=ADC_SAMPLES_PER_BLOCK*numOfBlocks)
	{
		tmpVal = getAdcSample();
		
		writeByteSpiLld(SPI_MEM,tmpVal);
		writeByteSpiLld(SPI_MEM,tmpVal>>8);
					
		i++;
	}
	
	timerDelayUsDirty(100); //let the buffer drain
	
	spiMemFinalizeSequential();

	return 0;
}


//only for debug
//@deprecated - delete
bool streamAllSPiZigbee()
{
	return true;
}	
