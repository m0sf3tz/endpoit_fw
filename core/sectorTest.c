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

static char strSample[] = " Starting to sample ADC";
static char strCreatingAndSendingSector[] = " Starting to send create and send off the first sector";
static char strDoneAndSendingSector[] = " Finished sending off the final sector";
static char strPressAnyKeyToContinue[] = " Press Any Key to continue";


//this guy is inteded to be used with the menu, it will send all the samples up at once
//will loop through SPI memory, grab blocks, create sectors + CRC + etc then zigbeen them up
bool sendAllSectors()
{
	printNewLine();
	uartPutMenuAutoCount(strSample);
	printNewLine();

	stateSample();

	printNewLine();
	uartPutMenuAutoCount(strCreatingAndSendingSector);
	printNewLine();

	
	int sector = 0;
 	for(sector = 0;sector < SECTORS_PER_SAMPLE; sector++)
	{
   		stateCreateTxBuffer();
	  	stateTrasmit();
	}
	
	printNewLine();
	uartPutMenuAutoCount(strDoneAndSendingSector);
	printNewLine();
	
	printNewLine();
	uartPutMenuAutoCount(strPressAnyKeyToContinue);
	printNewLine();

	//give a chance to the user too see above output...
	blockForInput();

	return true;
}

//this guy is inteded to be used with the menu, it will send all the samples up at once
//the difference between this and sendAllSectors is that we will not actaully sample,
//so whatever is in the SPI will be sent up , it's good for debuggablity
//you can use spi menu to init the SPI as you wish
bool sendAllSectorsDontSample()
{
	printNewLine();
	uartPutMenuAutoCount(strCreatingAndSendingSector);
	printNewLine();

	
	int sector = 0;
 	for(sector = 0;sector < SECTORS_PER_SAMPLE; sector++)
	{
   		stateCreateTxBuffer();
	  	stateTrasmit();
	}
	
	printNewLine();
	uartPutMenuAutoCount(strDoneAndSendingSector);
	printNewLine();
	
	printNewLine();
	uartPutMenuAutoCount(strPressAnyKeyToContinue);
	printNewLine();

	//give a chance to the user too see above output...
	blockForInput();

	return true;
}






