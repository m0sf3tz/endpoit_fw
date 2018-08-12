#include "stm32l0xx_hal_spi.h"
#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal.h"
#include "projectDefines.h"

#include <stdbool.h>
#include "spiHal.h"

//handles
static SPI_HandleTypeDef    SpiHandleAnalog;
static SPI_HandleTypeDef    SpiHandleMem;

void initSpis()
{
	//bad name - inits GPIOs and CLOCKs
	initSpiGpiosDigital();
	initSpiGpiosAnalog();
	
	
	//configure Memory SPI handle
	SpiHandleMem.Instance               = SPI2;

	SpiHandleMem.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	SpiHandleMem.Init.Direction         = SPI_DIRECTION_2LINES;
	SpiHandleMem.Init.CLKPhase          = SPI_PHASE_1EDGE;
	SpiHandleMem.Init.CLKPolarity       = SPI_POLARITY_LOW;
	SpiHandleMem.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	SpiHandleMem.Init.CRCPolynomial     = 7;
	SpiHandleMem.Init.DataSize          = SPI_DATASIZE_8BIT;
	SpiHandleMem.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SpiHandleMem.Init.NSS               = SPI_NSS_SOFT;
	SpiHandleMem.Init.TIMode            = SPI_TIMODE_DISABLE;
	SpiHandleMem.Init.Mode = SPI_MODE_MASTER;
	
	if(HAL_SPI_Init(&SpiHandleMem) != HAL_OK)
	{
		ASSERT(0);
	}
	
	//configure ADC SPI handle
	SpiHandleAnalog.Instance               = SPI1;

	SpiHandleAnalog.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	SpiHandleAnalog.Init.Direction         = SPI_DIRECTION_2LINES;
	SpiHandleAnalog.Init.CLKPhase          = SPI_PHASE_1EDGE;
	SpiHandleAnalog.Init.CLKPolarity       = SPI_POLARITY_LOW;
	SpiHandleAnalog.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	SpiHandleAnalog.Init.CRCPolynomial     = 7;
	SpiHandleAnalog.Init.DataSize          = SPI_DATASIZE_16BIT;
	SpiHandleAnalog.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SpiHandleAnalog.Init.NSS               = SPI_NSS_SOFT;
	SpiHandleAnalog.Init.TIMode            = SPI_TIMODE_DISABLE;
	SpiHandleAnalog.Init.Mode 						 = SPI_MODE_MASTER;

	
	if(HAL_SPI_Init(&SpiHandleAnalog) != HAL_OK)
	{
		ASSERT(0);
	}

	__HAL_SPI_ENABLE(&SpiHandleAnalog);
	__HAL_SPI_ENABLE(&SpiHandleMem);
	
}


void initSpiGpiosDigital()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	//****************************************************************************
	//											init SPI 2 (MEMORY)
	//****************************************************************************

  SPI2_SCK_GPIO_CLK_ENABLE();
  SPI2_MISO_GPIO_CLK_ENABLE();
  SPI2_MOSI_GPIO_CLK_ENABLE();
  SPI2_CLK_ENABLE(); 
  
	
  /* SPI SCK GPIO pin configuration  */
  GPIO_InitStruct.Pin       = SPI2_SCK_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH  ;
  GPIO_InitStruct.Alternate = SPI2_SCK_AF;
  HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);
    		
  /* SPI MISO GPIO pin configuration  */
  GPIO_InitStruct.Pin = SPI2_MISO_PIN;
  GPIO_InitStruct.Alternate = SPI2_MISO_AF;
  
  HAL_GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);
  
  /* SPI MOSI GPIO pin configuration  */
  GPIO_InitStruct.Pin = SPI2_MOSI_PIN;
  GPIO_InitStruct.Alternate = SPI2_MOSI_AF;
    
  HAL_GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);  

  /* SPI CS GPIO pin configuration  */
  GPIO_InitStruct.Pin = SPI2_NSS_PIN;  
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(SPI2_NSS_GPIO_PORT, &GPIO_InitStruct);  
	HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_SET);
}

void initSpiGpiosAnalog()
{

	//****************************************************************************
	//											init SPI 1 (ADC+PGA)
	//****************************************************************************
  SPI1_SCK_GPIO_CLK_ENABLE();
  SPI1_MISO_GPIO_CLK_ENABLE();
  SPI1_MOSI_GPIO_CLK_ENABLE();
  SPI1_CLK_ENABLE(); 
  	
	GPIO_InitTypeDef  GPIO_InitStruct;

	
  /* SPI SCK GPIO pin configuration  */
  GPIO_InitStruct.Pin       = SPI1_SCK_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH  ;
  GPIO_InitStruct.Alternate = SPI1_SCK_AF;
  
  HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);
    		
  /* SPI MISO GPIO pin configuration  */
  GPIO_InitStruct.Pin = SPI1_MISO_PIN;
  GPIO_InitStruct.Alternate = SPI1_MISO_AF;
  
  HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);
  
  /* SPI MOSI GPIO pin configuration  */
  GPIO_InitStruct.Pin = SPI1_MOSI_PIN;
  GPIO_InitStruct.Alternate = SPI1_MOSI_AF;
    
  HAL_GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);    
	
	/* SPI CS GPIO pin configuration  */
  GPIO_InitStruct.Pin   = SPI1_NSS_PIN;  
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	
  HAL_GPIO_Init(SPI1_NSS_GPIO_PORT, &GPIO_InitStruct);  
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_SET);
}

//puts pins to sleep.
bool deinitSpiGpiosAnalog()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	
	/* SPI SCK GPIO pin configuration  */
  GPIO_InitStruct.Pin       = SPI1_SCK_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_INPUT; 
  HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);
    		
  /* SPI MISO GPIO pin configuration  */
  GPIO_InitStruct.Pin  = SPI1_MISO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 
  HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);
  
  /* SPI MOSI GPIO pin configuration  */
  GPIO_InitStruct.Pin = SPI1_MOSI_PIN;
  GPIO_InitStruct.Alternate = GPIO_MODE_INPUT;
  HAL_GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);    

	/* SPI CS GPIO pin configuration  */
  GPIO_InitStruct.Pin   = SPI1_NSS_PIN;  
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  HAL_GPIO_Init(SPI1_NSS_GPIO_PORT, &GPIO_InitStruct);  

	return true;
}

void spiWrite(uint8_t * data, uint32_t num, spiChanel_e spi)
{
	if (spi == SPI_MEM)
	{
		
		HAL_SPI_Transmit(&SpiHandleMem, data, num, HAL_MAX_DELAY);
		
		
	}
	else
	{
		HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_RESET);

	  HAL_SPI_Transmit(&SpiHandleAnalog, data, num, HAL_MAX_DELAY);
		
		HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_SET);
	}
}

void spiPutByte(spiChanel_e chan, uint8_t data)
{
	if(chan == SPI_ANALOG)
	{
			HAL_SPI_Transmit(&SpiHandleAnalog, &data, 1, HAL_MAX_DELAY);
	}
	else
	{
			HAL_SPI_Transmit(&SpiHandleMem, &data, 1, HAL_MAX_DELAY);
	}
}

void spiPut(spiChanel_e chan, uint32_t len, uint8_t * data)
{
	if(chan == SPI_ANALOG)
	{
			HAL_SPI_Transmit(&SpiHandleAnalog, data, len, HAL_MAX_DELAY);
	}
	else
	{
			HAL_SPI_Transmit(&SpiHandleMem, data, len, HAL_MAX_DELAY);
		
	}
}

uint8_t spiGet(spiChanel_e chan)
{
	uint8_t retval;
	
	if(chan == SPI_ANALOG)
	{
			 HAL_SPI_Receive(&SpiHandleAnalog, &retval, 1, HAL_MAX_DELAY);
	}
	else
	{
			 HAL_SPI_Receive(&SpiHandleMem, &retval, 1, HAL_MAX_DELAY);
	}
	
	return retval;
}

void spiPutGet(spiChanel_e chan, uint8_t * wr, uint8_t * rd, uint32_t len)
{
	if(chan == SPI_ANALOG)
	{
			HAL_SPI_TransmitReceive(&SpiHandleAnalog, wr, rd, len, HAL_MAX_DELAY);
	}
	else
	{
			HAL_SPI_TransmitReceive(&SpiHandleMem, wr, rd, len, HAL_MAX_DELAY);
	}
}


void writeByteSpiLld(spiChanel_e chan, uint8_t dat)
{
		if(chan == SPI_MEM)
		{
			while( !(SpiHandleMem.Instance->SR & SPI_SR_TXE) ) //while TX buffer is not empty...
			{
			}
			//TX buffer is empty! SEND SEND SEND =)
			SpiHandleMem.Instance->DR = dat;
		}
		else
		{
			while( !(SpiHandleAnalog.Instance->SR & SPI_SR_TXE) ) //while TX buffer is not empty...
			{
			}
			//TX buffer is empty! SEND SEND SEND =)
			SpiHandleAnalog.Instance->DR = dat;
		}
}

uint16_t readByteSpiLld(spiChanel_e chan)
{
	writeByteSpiLld(chan, DUMMY_BYTE);			
			
	if(chan == SPI_MEM)
	{
		while( !(SpiHandleMem.Instance->SR & SPI_SR_RXNE) ) //while RX buffer is  empty...
		{
		}
		//RX buffer is not empty!
		return 	SpiHandleMem.Instance->DR;
	}
	else
	{
		while( !(SpiHandleAnalog.Instance->SR & SPI_SR_RXNE) ) //while RX buffer is  empty...
		{
		}
		//RX buffer is not empty!
		return 	SpiHandleAnalog.Instance->DR;
	}
}


