#include "pga.h"
#include "spiHal.h"
#include "stm32l0xx_hal_gpio.h"
#include "adc.h"
#include "timerHal.h"
#include "cpuHal.h"
#include "projectDefines.h"


//we need to use this  to translate between the gain index and actuall gain
uint8_t gainTranslateMatrix[8] = 
{
	1,
	2,
	4,
	5,
	5,
	10,
	16,
	32
};

static pgaGainSwitch_e helperGetNextGain(pgaGainSwitch_e currentGain)
{
	if(currentGain == GAIN_PGA_1)
		return GAIN_PGA_2;
	else if(currentGain == GAIN_PGA_2)
				return GAIN_PGA_4;
	else if(currentGain == GAIN_PGA_4)
				return GAIN_PGA_5;
	else if(currentGain == GAIN_PGA_5)
				return GAIN_PGA_8;
	else if(currentGain == GAIN_PGA_8)
				return GAIN_PGA_10;
	else if(currentGain == GAIN_PGA_10)
				return GAIN_PGA_16;
	else if(currentGain == GAIN_PGA_16)
				return GAIN_PGA_32;
  else{
		  ASSERT(0);
	}
}

void setPgaGain(pgaGainSwitch_e gain)
{
	//byte0 = 0b010_0000_0 //0x40
	//byte1 = gain
	uint16_t val = (0x40 << 8 | gain);
	
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_RESET);

	spiWrite((uint8_t*)&val, 1, SPI_ANALOG);

	HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_SET);
}


bool setGainGpa1(void)
{
	setPgaGain(GAIN_PGA_1);
	return 1;
}

bool setGainGpa2(void)
{
	setPgaGain(GAIN_PGA_2);
	return 1;
}

bool setGainGpa10(void)
{
	setPgaGain(GAIN_PGA_10);
	return 1;
}

bool setGainGpa16(void)
{
	setPgaGain(GAIN_PGA_16);
	return 1;
}

bool setGainGpa32(void)
{
	setPgaGain(GAIN_PGA_32);
	return 1;
}

//this function needs to be redone once we don't have a 
//retarted internal ADC... 
pgaGainSwitch_e autoGainSelect()
{

	//retGain = last known non-saturating gain (if we are saturating at x1 gain then we have other problems - we can see this in software someplace upstream
	//reqrues hardware fix and nothing FW can do about it..
	//testGain is the gain which we will test to see if we have a saturation event. if we saturate at some gain, we will roll back to the last known
	//working gain, otherwise, we will increment retGain
	 
	pgaGainSwitch_e retGain = GAIN_PGA_1;
	uint16_t min, max, tmp;
	bool exceeded = false;
	
	while(!exceeded)
	{
		int totalSamples = 100; //current sampling rate
		pgaGainSwitch_e testGain = helperGetNextGain(retGain);
		setPgaGain(testGain);
	
		max = 0;
		min = 0x7FFE;
		
		while(totalSamples--)
		{
			tmp = getAdcSample();
			if(tmp > max)
		  {
				max = tmp;
			}
			if(tmp < min)
			{
				min = tmp;
			}
		}
		if ( (max >= 0x7F00) | (min == 0) )
		{
			exceeded = true;
			setPgaGain(retGain); //roll back to last known-good configuration
		}
		else
		{
			if(retGain == GAIN_PGA_16)
			{
				return GAIN_PGA_32; //can't go any higher thant this (above test is done with gain++, can't go higher than x32)
			}
			else
			{
				retGain = testGain; //make retGain = the gain we tested at, since it did not saturate.
			}
		}
	}
	return retGain; 
}



