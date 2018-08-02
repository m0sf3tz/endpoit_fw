/*
 * SPI_23A1024.c
 *
 *  Created on: Jan 16, 2017
 *      Author: Sam2
 */

#include "MC23A1024.h"
#include "spiHal.h"
#include "gpioHal.h"
#include "projectDefines.h"
#include "timerHal.h"
#include "stm32l0xx_hal_gpio.h"

void SRAM_CS_HIGH()
{
	gpioSetReset(SPI2_NSS_GPIO_PORT,SPI2_NSS_PIN, GPIO_PIN_SET);
}


void SRAM_CS_LOW()
{
	gpioSetReset(SPI2_NSS_GPIO_PORT,SPI2_NSS_PIN, GPIO_PIN_RESET);
}


uint8_t getChar()
{
	return spiGet(SPI_MEM);
}

void drainFifo()
{
	int x = 30;
	while(x--)
	{
		spiGet(SPI_MEM);
	}
}
void putChar(uint8_t data)
{
	spiPutByte(SPI_MEM, data);
}


void setMode(SPI_MODE_e mode)
{
	SRAM_CS_LOW();
	putChar(SPI_MODE_WRMR);
	putChar(mode);
	SRAM_CS_HIGH();
}

SPI_MODE_e getMode()
{
	SRAM_CS_LOW();
	
	putChar(SPI_MODE_RDMR);
	uint8_t data = getChar();
	SRAM_CS_HIGH();

	return (SPI_MODE_e)data;
}


void writeByteSram(uint32_t address, uint8_t dat)
{
	SRAM_CS_LOW();
	
	uint8_t wr[1+3+1];

	wr[0] = SPI_MODE_WRITE;


	wr[1] = (address >> 16 ) & 0xFF;
	wr[2] = (address >> 8  ) & 0xFF;
	wr[3] = (address >> 0  ) & 0xFF;
	wr[4] = dat;

	spiPut(SPI_MEM,5,wr);
	
	SRAM_CS_HIGH();
}

uint8_t getByteSram(uint32_t address) 
{	
	SRAM_CS_LOW();
	
	uint8_t wr[1+3+1];
	uint8_t rd[1+3+1];

	wr[0] = SPI_MODE_READ;


	wr[1] = (address >> 16 ) & 0xFF;
	wr[2] = (address >> 8  ) & 0xFF;
	wr[3] = (address >> 0  ) & 0xFF;
	wr[4] = 0xA5; //dummy byte

	spiPutGet(SPI_MEM,wr,rd,5);
	
	SRAM_CS_HIGH();

	return rd[4];
}


void putByteBlock(uint8_t * pt, uint32_t block)
{
	setMode(SPI_MODE_BYTE);
	
	uint32_t offset = block*BLOCK_SPI_MEM_BYTE;
	int i = 0;
	volatile uint8_t val;
	for(;i < BLOCK_SPI_MEM_BYTE;i++)
	{
		writeByteSram(offset+i,*pt);
		pt++;
	}
}

void getByteBlock(uint8_t * pt, uint32_t block)
{
	setMode(SPI_MODE_BYTE);
	
	uint32_t offset = block*BLOCK_SPI_MEM_BYTE;
	int i = 0;
	volatile uint8_t val;
	for(;i < BLOCK_SPI_MEM_BYTE;i++)
	{
		val =  getByteSram(offset+i);
		*pt = val;
		pt++;
	}
}

uint32_t blockToAdressTranslate(uint32_t block)
{
	if(block >= SPI_TOTAL_SRAM_TOTAL_BLOCKS)
	{
		while(1){}
	}
		
	return block*BLOCK_SPI_MEM_BYTE;
}



void spiWriteDMASequentialFinalize()
{
	SRAM_CS_HIGH();
}


void spiMemPrepSequentialWrite(uint16_t block)
{
	setMode(SPI_MODE_SQNC);
	spiWriteDMASequentialInit(blockToAdressTranslate(block));
}

void spiWriteDMASequentialInit(const uint32_t address)
{
	SRAM_CS_LOW();
	putChar( SPI_MODE_WRITE);
	putChar( (address >> 16)  & 0xFF);
	putChar( (address >> 8)   & 0xFF);
	putChar( (address >> 0)   & 0xFF);
}

void spiReadDMASequentialInit(const uint32_t address)
{
	SRAM_CS_LOW();
	putChar( SPI_MODE_READ);
	putChar( (address >> 16)    & 0xFF);
	putChar( (address >> 8)     & 0xFF);
	putChar( (address >> 0)     & 0xFF);
}


void spiMemFinalizeSequential()
{
	spiWriteDMASequentialFinalize();
}

void spiMemPrepSequentialRead(uint16_t block)
{
	setMode(SPI_MODE_SQNC);
	spiReadDMASequentialInit(blockToAdressTranslate(block));
	//drainFifo();
}

bool quickTestSequential()
{
	spiMemPrepSequentialWrite(0);
	int x = 0;
	
	for(; x < 100; x++)
	{
		writeByteSpiLld(SPI_MEM, x);	
	}
	spiMemFinalizeSequential();
	
		
	spiMemPrepSequentialRead(0);
	volatile int c;
	for(x = 0; x < 100; x++)
	{
		if (  x!= readByteSpiLld(SPI_MEM))
		{
			while(1){}
		}
	}
	return true;
}
	
	
	
