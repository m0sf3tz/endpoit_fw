#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_dma.h"
#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal_uart.h"
#include <stdbool.h>

#include "uartHal.h"
#include "projectDefines.h"

static UART_HandleTypeDef   UartHandleZigbee;
static UART_HandleTypeDef   UartHandleMenu;


/* Definition for USARTx clock resources */
                          
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE() 
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USART_ZIGBEE_TX_PIN               GPIO_PIN_6
#define USART_ZIGBEE_TX_GPIO_PORT         GPIOB
#define USART_ZIGBEE_TX_AF                GPIO_AF0_USART1
#define USART_ZIGBEE_RX_PIN               GPIO_PIN_7
#define USART_ZIGBEE_RX_GPIO_PORT         GPIOB 
#define USART_ZIGBEE_RX_AF                GPIO_AF0_USART1

/* Definition for USARTx's DMA */
#define USARTx_TX_DMA_CHANNEL             DMA1_Channel2
#define USARTx_TX_DMA_REQUEST             DMA_REQUEST_3
#define USARTx_RX_DMA_CHANNEL             DMA1_Channel3
#define USARTx_RX_DMA_REQUEST             DMA_REQUEST_3

/* Definition for USARTx's NVIC */
#define USARTx_DMA_TX_IRQn                DMA1_Channel2_3_IRQn
#define USARTx_DMA_RX_IRQn                DMA1_Channel2_3_IRQn
#define USARTx_DMA_TX_IRQHandler          DMA1_Channel2_3_IRQHandler
#define USARTx_DMA_RX_IRQHandler          DMA1_Channel2_3_IRQHandler

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                       USART1_IRQn
#define USARTx_IRQHandler                 USART1_IRQHandler


////////////////uart for menue /////////////////////////////

#define USART_MENU_CLK_ENABLE()         	__HAL_RCC_USART2_CLK_ENABLE()
#define USART_MENU_RX_GPIO_CLK_ENABLE() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define USART_MENU_TX_GPIO_CLK_ENABLE() 	__HAL_RCC_GPIOA_CLK_ENABLE() 



/* Definition for USARTx Pins */
#define USART_MENU_TX_PIN                    GPIO_PIN_2
#define USART_MENU_TX_GPIO_PORT              GPIOA
#define USART_MENU_TX_AF                     GPIO_AF4_USART2
#define USART_MENU_RX_PIN                    GPIO_PIN_3
#define USART_MENU_RX_GPIO_PORT              GPIOA 
#define USART_MENU_RX_AF                     GPIO_AF4_USART2

/* Definition for USARTx Pins */
#define USART_DOZE_PIN    	                  GPIO_PIN_8
#define USART_DOZE_PORT                       GPIOB


#include "stm32l0xx_hal_uart.h"



void initUart(void)
{
  //Enable GPIO TX/RX clock for zigbee 
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();
  USARTx_CLK_ENABLE(); 
	
  // Enable GPIO TX/RX clock  for menue
	USART_MENU_CLK_ENABLE();         	
	USART_MENU_RX_GPIO_CLK_ENABLE(); 	
	USART_MENU_TX_GPIO_CLK_ENABLE();

	UartHandleMenu.Instance        = USART2;
  UartHandleMenu.Init.BaudRate   = 57600;
  UartHandleMenu.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandleMenu.Init.StopBits   = UART_STOPBITS_1;
  UartHandleMenu.Init.Parity     = UART_PARITY_NONE;
  UartHandleMenu.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandleMenu.Init.Mode       = UART_MODE_TX_RX;
  
	initUartPinsMenu();
  if(HAL_UART_Init(&UartHandleMenu) != HAL_OK)
  {
		ASSERT(0);
  }
	__HAL_UART_ENABLE(&UartHandleMenu);
	
	
	

	UartHandleZigbee.Instance        = USART1;
  UartHandleZigbee.Init.BaudRate   = 57600;
  UartHandleZigbee.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandleZigbee.Init.StopBits   = UART_STOPBITS_1;
  UartHandleZigbee.Init.Parity     = UART_PARITY_NONE;
  UartHandleZigbee.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandleZigbee.Init.Mode       = UART_MODE_TX_RX;
  

  if(HAL_UART_Init(&UartHandleZigbee) != HAL_OK)
  {
		ASSERT(0);
	}
  initUartPinsZigbee();
	__HAL_UART_ENABLE(&UartHandleZigbee);
}



void initUartPinsMenu()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_InitStruct.Pin 		  = USART_MENU_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH  ;
	GPIO_InitStruct.Alternate = USART_MENU_TX_AF;
	HAL_GPIO_Init(USART_MENU_TX_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin 		  = USART_MENU_RX_PIN;
	GPIO_InitStruct.Alternate = USART_MENU_RX_AF;
	HAL_GPIO_Init(USART_MENU_RX_GPIO_PORT, &GPIO_InitStruct);
}

void initUartPinsZigbee()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USART_ZIGBEE_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH  ;
  GPIO_InitStruct.Alternate = USART_ZIGBEE_TX_AF;
  HAL_GPIO_Init(USART_ZIGBEE_RX_GPIO_PORT, &GPIO_InitStruct);
    
  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USART_ZIGBEE_RX_PIN;
  GPIO_InitStruct.Alternate = USART_ZIGBEE_RX_AF;
  HAL_GPIO_Init(USART_ZIGBEE_RX_GPIO_PORT, &GPIO_InitStruct);
}


//turns eveything off for UART (not the menue)
void deinitUartPinsZigbee()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USART_ZIGBEE_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
  HAL_GPIO_Init(USART_ZIGBEE_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USART_ZIGBEE_RX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
  HAL_GPIO_Init(USART_ZIGBEE_RX_GPIO_PORT, &GPIO_InitStruct);
}
	


void serialSpam(uint8_t *pt, uint32_t len)
{
	(HAL_UART_Transmit(&UartHandleZigbee, (uint8_t*)pt, len,HAL_MAX_DELAY));
	(HAL_UART_Transmit(&UartHandleMenu,   (uint8_t*)pt, len,HAL_MAX_DELAY));
}

void uartPutMenu(const char *pt, int len)
{
		HAL_UART_Transmit(&UartHandleMenu, (uint8_t*)pt,len,HAL_MAX_DELAY);
}

void uartGetMenu(const char * pt, int len)
{
#if SHARE_UART
	HAL_UART_Receive(&UartHandleZigbee, (uint8_t*)pt,len,HAL_MAX_DELAY);
#else
	HAL_UART_Receive(&UartHandleMenu, (uint8_t*)pt,len,HAL_MAX_DELAY);
#endif
}

void uartPut(const char *pt, int len)
{
	HAL_UART_Transmit(&UartHandleZigbee, (uint8_t*)pt,len,HAL_MAX_DELAY);
}



