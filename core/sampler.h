#pragma once
#include "pga.h"

bool fillBlockMenuShim(void);
bool fillBlock(uint16_t block);
bool memToBufferShim(void);
bool memToBuffer(uint16_t);


bool bufferToZigbeeShim(void);
bool bufferToZigbee(uint16_t block );

pgaGainSwitch_e taskSample(void);
bool multiSectorSpiMemFillShim(void);
bool multiSectorSpiMemFill(uint16_t numOfBlocks, uint16_t block);

bool streamAllSPiZigbee(void);
