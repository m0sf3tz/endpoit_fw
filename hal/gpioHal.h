#include <stdbool.h>
#include "stm32l0xx_hal_gpio.h"

#pragma once

void initDebugGpio(void);
void debugGpio(void);

void setGreenLed(bool);
void gpioSetReset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, bool value);
