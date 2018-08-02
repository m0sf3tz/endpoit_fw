#include <stdbool.h>
#include "stm32l0xx_hal_gpio.h"

#pragma once

void initLeds(void);
void toggleGreenLed(void);
void setGreenLed(bool);
void gpioSetReset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, bool value);
