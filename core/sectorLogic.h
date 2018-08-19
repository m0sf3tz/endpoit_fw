#pragma once

#define NOT_INITIAL_SECTOR 0
#define INITIAL_SECTOR 1	

#define NOT_FINAL_SECTOR 0
#define FINAL_SECTOR 	   1

//used for settuping a sector before we zigbee it up
void sectorSetHeader(bool initial);
void sectorTransmitSector(uint8_t sector);
void sectorSetSequenceId(uint16_t sequence);
void sectorSetCapVoltage(uint16_t voltage);
void sectorSetEnergyQaulity(uint8_t energyQuality);
void sectorSetPgaGain(uint8_t pgaGain);
void sectorSetFree(void);
void sectorSetCRC(uint16_t crc);
void sectorSetTerminator(bool final);

bool fillBlockMenuShim(void);
bool fillBlock(uint16_t block);
bool memToBufferShim(void);
bool memToBuffer(uint16_t);

bool bufferToZigbeeShim(void);
bool bufferToZigbee(uint16_t block );

bool streamAllSPiZigbee(void);

//sector stuff (the real deal)
bool zigbeeTransmitTask(void);
void createTxSectorTask(uint8_t sector, uint16_t sequenceId, uint8_t powerQuality, uint16_t capVoltage,uint8_t gain);
	 


