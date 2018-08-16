#pragma once

#define NOT_INITIAL_SECTOR 0
#define INITIAL_SECTOR 1	

#define NOT_FINAL_SECTOR 0
#define FINAL_SECTOR 	   1

//used for settuping a sector before we zigbee it up
void sectorSetHeader(bool initial);
void sectorSetSequenceId(uint16_t sequence);
void sectorSetCapVoltage(uint16_t voltage);
void sectorSetEnergyQaulity(uint8_t energyQuality);
void sectorSetCRC(uint16_t crc);
void sectorSetTerminator(bool final);



bool fillBlockMenuShim(void);
bool fillBlock(uint16_t block);
bool memToBufferShim(void);
bool memToBuffer(uint16_t);


bool bufferToZigbeeShim(void);
bool bufferToZigbee(uint16_t block );


bool streamAllSPiZigbee(void);


