/*
 * unitTest.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Sam2
 */
 
#pragma once

uint32_t hash(uint32_t x);
void static fillBuff(void);
bool spiWalkTest(void);
bool spiWalkTestRegisterSequentialMode(void);
bool spiMemoryVerifyDestSrc(void);
bool randomSectorFillTest(void);
bool fillSpiSawTooth(void);
