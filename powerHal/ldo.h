#include <stdbool.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_gpio.h"


#define LDO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SAMPLNG_SUPPLY_PIN    GPIO_PIN_11
#define SAMPLNG_SUPPLY_PORT   GPIOA


bool enableSamplingSupply( void );
bool disableSamplingSupply( void );
void iniLdoClocksAndPins( void );
