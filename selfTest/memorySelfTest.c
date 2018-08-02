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


uint8_t hash(uint32_t x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x)						  ;
    
	  return (x & 0xFF);
}




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

	uint32_t locationPointer = 0;
	spiMemPrepSequentialWrite(0);
	
	while(locationPointer!=SPI_MEMORY_SRAM_SIZE_BYTES)
	{
		
		uint8_t hashedValue = hash(locationPointer);
		
		writeByteSpiLld(SPI_MEM,hashedValue);
		
		locationPointer++;
		
	}
	
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
			uartPutMenuAutoCount("test FAILED!");
			blockForInput();
			return 0;
		}
			
		locationPointer++;

	}
	
	spiMemFinalizeSequential();
	printNewLine();
	uartPutMenuAutoCount("test PASSED: Press any key to continue!");
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


