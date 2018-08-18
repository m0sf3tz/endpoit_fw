#include <stdint.h>
#include "globals.h"

volatile uint32_t simVoltage;

uint8_t hash(uint32_t x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x)						  ;
    
	  return (x & 0xFF);
}

uint16_t hash16(uint32_t x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x)						  ;
    
	  return (x & 0xFFFF);
}
