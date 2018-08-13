/*
 * projectDefines.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Sam2
 */

#ifndef PROJECTDEFINES_H_
#define PROJECTDEFINES_H_

#define ASSERT(x) do{ \
	if(!x){while(1){}} \
	}while(0)

//********************************************************************************//
//								SPI/ADC DEFINES									  
//********************************************************************************//
#define BLOCK_SPI_MEM_BYTE   							    256
#define ADC_SAMPLES_PER_BLOCK							    128

#define BLOCK_UART_ZIGBEE							  	   	256


#define SPI_MEMORY_SRAM_SIZE_BYTES					  0x1FFFF
#define SPI_TOTAL_SRAM_TOTAL_BLOCKS					  SPI_MEMORY_SRAM_SIZE_BYTES/BLOCK_SPI_MEM_BYTE

#define SPI_MEMORY_BIT_RATE 					       	200000
#define SPI_MEMORY_ADDRESS_SIZE     			  	8

#define ADC_BIT_RATE 							 	 			  	180000
#define ADC_BITS_PER_SAMPLE		    				  	16


#define SPI_SRAM_SSI_BASE_INTERRUPT_BASE			INT_SSI0//INT_SSI0
#define SPI_SRAM_SSI_BASE											0x40008000//SSI0_BASE
#define SPI_ANALOG_SSI_BASE										0x40009000//SSI1_BASE


#define MAXIMUM_MEMORY_ADRESS 								0x1FFFF //max range for 

#define MOTOR_EYE_SAMPLE_BLOCKS							  20
#define FIRST_SECTOR_SPI							  	    0


//********************************************************************************//
//								build swithces									  
//********************************************************************************//

#define DEBUG_MODE					(1) 		//includes the halUnit test, creates buffer mmoery of them etc

#endif /* PROJECTDEFINES_H_ */
