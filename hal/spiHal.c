#include "stm32l0xx_hal_spi.h"
#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal.h"

#include "spiHal.h"

//handles
static SPI_HandleTypeDef    SpiHandleADC;
static SPI_HandleTypeDef    SpiHandleMem;

void initSpis()
{
		//bad name - inits GPIOs and CLOCKs
		initSpiGpios();

	
	
	//configure Memory SPI handle
	SpiHandleMem.Instance               = SPI2;

	SpiHandleMem.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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
		while(1){}
	}
	
	//__HAL_SPI_ENABLE(&SpiHandleADC); RIP
	__HAL_SPI_ENABLE(&SpiHandleMem);
	
}

static void initSpiGpios()
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

	//****************************************************************************
	//											init SPI 2
	//****************************************************************************

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  SPI2_SCK_GPIO_CLK_ENABLE();
  SPI2_MISO_GPIO_CLK_ENABLE();
  SPI2_MOSI_GPIO_CLK_ENABLE();
  /* Enable SPI clock */
  SPI2_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
	
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

void spiWrite(uint8_t * data, uint32_t num, spiChanel_e spi)
{
	if (spi == SPI_MEM)
	{
		
		HAL_SPI_Transmit(&SpiHandleMem, data, num, HAL_MAX_DELAY);
		
		
	}
	else
	{
		HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_RESET);

	  HAL_SPI_Transmit(&SpiHandleADC, data, num, HAL_MAX_DELAY);
		
		HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_SET);
	}
}

void spiPutByte(spiChanel_e chan, uint8_t data)
{
	if(chan == SPI_ADC)
	{
			HAL_SPI_Transmit(&SpiHandleADC, &data, 1, HAL_MAX_DELAY);
	}
	else
	{
			HAL_SPI_Transmit(&SpiHandleMem, &data, 1, HAL_MAX_DELAY);
	}
}

void spiPut(spiChanel_e chan, uint32_t len, uint8_t * data)
{
	if(chan == SPI_ADC)
	{
			HAL_SPI_Transmit(&SpiHandleADC, data, len, HAL_MAX_DELAY);
	}
	else
	{
			HAL_SPI_Transmit(&SpiHandleMem, data, len, HAL_MAX_DELAY);
		
	}
}

uint8_t spiGet(spiChanel_e chan)
{
	uint8_t retval;
	
	if(chan == SPI_ADC)
	{
			 HAL_SPI_Receive(&SpiHandleADC, &retval, 1, HAL_MAX_DELAY);
	}
	else
	{
			 HAL_SPI_Receive(&SpiHandleMem, &retval, 1, HAL_MAX_DELAY);
	}
	
	return retval;
}

void spiPutGet(spiChanel_e chan, uint8_t * wr, uint8_t * rd, uint32_t len)
{
	if(chan == SPI_ADC)
	{
			HAL_SPI_TransmitReceive(&SpiHandleADC, wr, rd, len, HAL_MAX_DELAY);
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
			while( !(SpiHandleADC.Instance->SR & SPI_SR_TXE) ) //while TX buffer is not empty...
			{
			}
			//TX buffer is empty! SEND SEND SEND =)
			SpiHandleADC.Instance->DR = dat;
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
		while( !(SpiHandleADC.Instance->SR & SPI_SR_RXNE) ) //while RX buffer is  empty...
		{
		}
		//RX buffer is not empty!
		return 	SpiHandleADC.Instance->DR;
	}
}


