#pragma once
#include "stm32l0xx_nucleo.h"


#define SAMPLNG_SUPPLY_PIN    11
#define SAMPLNG_SUPPLY_PORT   GPIOA
 


/* Definition for SPIx Pins */

#define SPI_CS_PGA_PIN	      9
#define SAMPLNG_SUPPLY_PORT   GPIOA

#define SPI1_SCK_PIN                     GPIO_PIN_5
#define SPI1_SCK_GPIO_PORT               GPIOA
#define SPI1_SCK_AF                      GPIO_AF0_SPI1

#define SPI1_MISO_PIN                    GPIO_PIN_6
#define SPI1_MISO_GPIO_PORT              GPIOA
#define SPIx_MISO_AF                     GPIO_AF0_SPI1

#define SPI1_MOSI_PIN                    GPIO_PIN_7
#define SPI1_MOSI_GPIO_PORT              GPIOA
#define SPI1_MOSI_AF                     GPIO_AF0_SPI1
