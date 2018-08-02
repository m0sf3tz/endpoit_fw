#ifndef MEM_23A1024_HEADER
#define MEM_23A1024_HEADER

#include <stdint.h>
#include <stdbool.h>

#define MAXIMUM_MEMORY_ADRESS 0x1FFFF


typedef enum
{
	SPI_MODE_BYTE  = 0,
	SPI_MODE_PAGE  = 0x80,
	SPI_MODE_SQNC  = 0x40,
	SPI_MODE_RSVD  = 0xC0,
	SPI_MODE_RDMR  = 0x05,
	SPI_MODE_WRMR  = 0x01,
}SPI_MODE_e;


typedef enum
{
	SPI_MODE_READ  = 0x03,
	SPI_MODE_WRITE = 0x02,
}SPI_INSTRUCTION_SET_e;



#define DUMMYBTE 0xA5


void SRAM_CS_HIGH(void);
void SRAM_CS_LOW(void);

		 

void POLL_SSI_BUSY(uint32_t base);


uint8_t getChar(void);
void putChar(uint8_t data);


void setMode(SPI_MODE_e);
SPI_MODE_e getMode(void);
bool spiWriteBlockingByte(const uint8_t ui8Data,const uint32_t address);
void spiWriteDMASequentialInit(const uint32_t address);
void spiWriteDMASequentialFinalize(void);
void spiReadDMASequentialInit (const uint32_t address);
void drain(void);
void drainFifo(void);
bool spiReadBlockingByte(uint8_t * const ui8Data,const uint32_t address);


void prepareSpiChipDmaRx(uint32_t address,uint32_t ssiBaseAdress);
void prepareSpiChipDmaTx(uint32_t address,uint32_t ssiBaseAdress);

void writeByteSram(uint32_t,uint8_t);
uint8_t getByteSram(uint32_t);

void getByteBlock(uint8_t*,uint32_t);


uint32_t blockToAdressTranslate(uint32_t block);
void spiMemPrepSequentialWrite(uint16_t block);
void spiMemPrepSequentialRead(uint16_t block);
void spiMemFinalizeSequential(void);



void writeByteSramLld(uint8_t);
uint8_t readByteSramLld(void);

bool quickTestSequential(void);

#endif //MEM_23A1024_HEADER
