#include <stdint.h>
#include <stdbool.h>

#define SPI2_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define SPI2_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_NSS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()

#define SPI2_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPI2_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPI2_SCK_PIN                     GPIO_PIN_13
#define SPI2_SCK_GPIO_PORT               GPIOB
#define SPI2_SCK_AF                      GPIO_AF0_SPI2

#define SPI2_MISO_PIN                    GPIO_PIN_14
#define SPI2_MISO_GPIO_PORT              GPIOB
#define SPI2_MISO_AF                     GPIO_AF0_SPI2

#define SPI2_MOSI_PIN                    GPIO_PIN_15
#define SPI2_MOSI_GPIO_PORT              GPIOB
#define SPI2_MOSI_AF                     GPIO_AF0_SPI2

#define SPI2_NSS_PIN                     GPIO_PIN_12
#define SPI2_NSS_GPIO_PORT               GPIOB



#define SPI1_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPI1_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_NSS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()

#define SPI1_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SPI1_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPI1_SCK_PIN                     GPIO_PIN_5
#define SPI1_SCK_GPIO_PORT               GPIOA
#define SPI1_SCK_AF                      GPIO_AF0_SPI1

#define SPI1_MISO_PIN                    GPIO_PIN_6
#define SPI1_MISO_GPIO_PORT              GPIOA
#define SPI1_MISO_AF                     GPIO_AF0_SPI1

#define SPI1_MOSI_PIN                    GPIO_PIN_7
#define SPI1_MOSI_GPIO_PORT              GPIOA
#define SPI1_MOSI_AF                     GPIO_AF0_SPI1  

#define SPI1_NSS_PIN                     GPIO_PIN_9
#define SPI1_NSS_GPIO_PORT               GPIOA


#define DUMMY_BYTE 											 0xA5


typedef enum
{
	SPI_MEM,
	SPI_ANALOG,
}spiChanel_e;

void initSpis(void);
void initSpiGpios(void);
bool deinitSpiGpios(void);
void spiWrite(uint8_t * data, uint32_t num, spiChanel_e spi);
void spiPutByte(spiChanel_e chan, uint8_t data);
void spiPut(spiChanel_e chan, uint32_t len, uint8_t * data);
uint8_t spiGet(spiChanel_e chan);
void spiPutGet(spiChanel_e chan, uint8_t * wr, uint8_t * rd, uint32_t len);


void writeByteSpiLld(spiChanel_e chan, uint8_t dat);
uint16_t readByteSpiLld(spiChanel_e chan);


