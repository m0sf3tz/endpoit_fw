#pragma once
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
	uint16_t capVoltage;
	uint16_t adc;
}adcRead_s;

void ADC_CS_HIGH(void);
void ADC_CS_LOW(void);

uint16_t getAdcSample(void);
uint16_t getCapVoltage(void);

void initAdc(void);

bool adcUnitTestOnDie(void);

