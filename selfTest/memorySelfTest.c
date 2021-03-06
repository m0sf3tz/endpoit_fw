/*
 * SPI_23A1024.c
 *
 *  Created on: Jan 16, 2017
 *      Author: Sam2
 */

#include "MC23A1024.h"
#include "projectDefines.h"
#include "uartHal.h"
#include "timerHal.h"
#include "spiHal.h"
#include "menu.h"
#include "adc.h"
#include "cpuHal.h"
#include "globals.h"






bool spiMemoryVerifyDestSrc(int blockUnderTest)
{
		 return true;

}

bool spiMemoryWalkTest()
{
		 return true;

}


bool spiSramToUartUnitTest()
{
	 return true;
}

bool spiWalkTest()
{
	
	
	printNewLine();
  uartPutMenuAutoCount("testing spi memory using byte by byte reads....  this will take a while");

	uint32_t locationPointer = 0;
	
	while(locationPointer!=SPI_MEMORY_SRAM_SIZE_BYTES)
	{
		
		uint8_t hashedValue = hash(locationPointer);
		
		writeByteSram(locationPointer, hashedValue);
		
		locationPointer++;
		
	}
	
	locationPointer = 0;
	
	while(locationPointer!=0x1FFFF)
	{

		uint8_t hashedValue 		  = hash(locationPointer);
		uint8_t hashedValueStored = getByteSram(locationPointer);
	
		if(hashedValueStored!=hashedValue)
		{
			printNewLine();
			uartPutMenuAutoCount("test FAILED!");
			sleepWFImultiplesOf1000ms(5);

			return 0;
		}
			
		locationPointer++;

	}
	
		printNewLine();
		uartPutMenuAutoCount("test PASSED: Press any key to continue!");
		blockForInput();
		return 1;

}

//set SPI SRAM mode to sequetional...
//use quicker register level access to fill up SPI
//read using normal read method
bool spiWalkTestRegisterSequentialMode()
{
	
	printNewLine();
	uartPutMenuAutoCount("testing spi memory using sequential mode....  this will take a while");
	printNewLine();
	uartPutMenuAutoCount("Entering Trubo Mode! VROOM 32Mhz");

	initRcc32mhz(); //VROOM TURBO MOODE
	
	uint32_t locationPointer = 0;
	spiMemPrepSequentialWrite(0);
	
	while(locationPointer!=SPI_MEMORY_SRAM_SIZE_BYTES)
	{
		
		uint8_t hashedValue = hash(locationPointer);
		
		writeByteSpiLld(SPI_MEM,hashedValue);
		
		locationPointer++;
		
	}
	timerDelayUsDirty(200); //lets make sure the buffer is empty before we 
													//pull the CS up high
	
	spiMemFinalizeSequential();

	
	spiMemPrepSequentialRead(0);
	locationPointer = 0;
	
	while(locationPointer!=SPI_MEMORY_SRAM_SIZE_BYTES)
	{

		uint8_t hashedValue 		  = hash(locationPointer);
		uint8_t hashedValueStored = readByteSpiLld(SPI_MEM);
	
		if(hashedValueStored!=hashedValue)
		{

			printNewLine();
	  	initRcc4mhz(); //AM I TURTLE
			uartPutMenuAutoCount("Leaving TURBO mode!");
			printNewLine();
			uartPutMenuAutoCount("test FAILED!");
			blockForInput();
			return 0;
		}
			
		locationPointer++;

	}
	
	spiMemFinalizeSequential();
	initRcc4mhz(); //AM I TURTLE
	printNewLine();
	uartPutMenuAutoCount("Leaving TURBO mode!");
	printNewLine();
	uartPutMenuAutoCount("test PASSED: Press any key to continue!");
	blockForInput();
	return 1;
}


bool spiFillPattern()
{

	printNewLine();
  uartPutMenuAutoCount("filling entire SPI memory array with incrementing values, per sector");
	printNewLine();
  
	uint32_t locationPointer =0 ;
	uint32_t sector =1 ;

	spiMemPrepSequentialWrite( 0 );	//prepare for writting to first bytes

	while(sector!=5)
	{
		while(locationPointer!=SPI_MEMORY_SRAM_SIZE_BYTES)
		{
			writeByteSpiLld(SPI_MEM,sector);
			locationPointer++;
		}
	  sector++;
	}
	spiMemFinalizeSequential();
	
	printNewLine();
	uartPutMenuAutoCount("done filling array with 0x55!");
	blockForInput();
	return 1;
}

bool fillSpiSawTooth()
{
	
	
	printNewLine();
  uartPutMenuAutoCount("filling entire SPI memory array with incrementing value");
	printNewLine();
  
	uint8_t sawTooth = 0;
	
	uint32_t locationPointer;
	
	spiMemPrepSequentialWrite( 0 );	//prepare for writting to first bytes

	
	while(locationPointer!=SPI_MEMORY_SRAM_SIZE_BYTES)
	{
		writeByteSpiLld(SPI_MEM,sawTooth++);
		locationPointer++;
	}
	
	spiMemFinalizeSequential();
	
	printNewLine();
	uartPutMenuAutoCount("test PASSED: Press any key to continue!");
	blockForInput();
	return 1;

	
}


