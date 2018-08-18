#pragma once
#include <stdbool.h>
typedef enum
{
	GAIN_PGA_1,
	GAIN_PGA_2,
	GAIN_PGA_4,
	GAIN_PGA_5,
	GAIN_PGA_8,
	GAIN_PGA_10,
	GAIN_PGA_16,
	GAIN_PGA_32
}pgaGainSwitch_e;


void setPgaGain(pgaGainSwitch_e gain);

//used in the menu - 
bool setGainGpa1(void);
bool setGainGpa2(void);
bool setGainGpa10(void);
bool setGainGpa16(void);
bool setGainGpa32(void);
