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

#define SECTOR_DATA_SIZE							  	   	256


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
#define FIRST_BLOCK_SPI           		  	    0


//********************************************************************************//
//								SECTOR TRANSMIT CONSTANTS									  
//********************************************************************************//

#define NEW_TRASMITION_HEADER_B0	0xBA
#define NEW_TRASMITION_HEADER_B1	0xDA
#define NEW_TRASMITION_HEADER_B2	0xAD
#define NEW_TRASMITION_HEADER_B3	0xBA
#define NEW_TRASMITION_HEADER_B4	0xDA


#define TRASMITION_HEADER_B0			0xF0
#define TRASMITION_HEADER_B1			0x0D
#define TRASMITION_HEADER_B2			0xD0
#define TRASMITION_HEADER_B3			0x00
#define TRASMITION_HEADER_B4			0x0F

#define STOP_SEQUENCE_B0					0xD0
#define STOP_SEQUENCE_B1					0x0D
#define STOP_SEQUENCE_B2					0xD0
#define STOP_SEQUENCE_B3					0x0D
#define STOP_SEQUENCE_B4					0xD0


#define FINAL_STOP_SEQUENCE_B0    0xDE
#define FINAL_STOP_SEQUENCE_B1    0xAD
#define FINAL_STOP_SEQUENCE_B2    0xDE
#define FINAL_STOP_SEQUENCE_B3    0xAD
#define FINAL_STOP_SEQUENCE_B4    0xDE


#define TRASMIT_BLOCK_SIZE        (TRASMITION_HEADER_SIZE + SEQUENCE_ID_SIZE + CAP_VOLTAGE_SIZE + ESTIMATED_ENERGY_QUALITY_SIZE + DATA_SIZE + CRC_SIZE + STOP_SEQUENCE_SIZE)

//********************************************************************************//
//								SECTOR TRANSMIT INDEX									  
//********************************************************************************//

#define NEW_TRASMITION_HEADER_B0_INDEX		 0
#define NEW_TRASMITION_HEADER_B1_INDEX		 (NEW_TRASMITION_HEADER_B0_INDEX  + 1)
#define NEW_TRASMITION_HEADER_B2_INDEX		 (NEW_TRASMITION_HEADER_B1_INDEX  + 1)
#define NEW_TRASMITION_HEADER_B3_INDEX		 (NEW_TRASMITION_HEADER_B2_INDEX  + 1)
#define NEW_TRASMITION_HEADER_B4_INDEX		 (NEW_TRASMITION_HEADER_B3_INDEX  + 1)



#define TRASMITION_HEADER_B0_INDEX		 	   0
#define TRASMITION_HEADER_B1_INDEX		 	   (TRASMITION_HEADER_B0_INDEX      + 1)
#define TRASMITION_HEADER_B2_INDEX		 	   (TRASMITION_HEADER_B1_INDEX      + 1)
#define TRASMITION_HEADER_B3_INDEX		 	   (TRASMITION_HEADER_B2_INDEX      + 1)
#define TRASMITION_HEADER_B4_INDEX		 	   (TRASMITION_HEADER_B3_INDEX      + 1)



#define SEQUENCE_ID_B0_INDEX					     (NEW_TRASMITION_HEADER_B0_INDEX + NEW_TRASMITION_HEADER_SIZE)
#define SEQUENCE_ID_B1_INDEX					     (SEQUENCE_ID_B0_INDEX +1)

#define CAP_VOLTAGE_B0_INDEX						   (SEQUENCE_ID_B0_INDEX + SEQUENCE_ID_SIZE)
#define CAP_VOLTAGE_B1_INDEX						   (CAP_VOLTAGE_B0_INDEX + 1)

#define ESTIMATED_ENERGY_QUALITY_INDEX	   (CAP_VOLTAGE_B0_INDEX + CAP_VOLTAGE_SIZE)

#define DATA_0_INDEX											 (ESTIMATED_ENERGY_QUALITY_INDEX + ESTIMATED_ENERGY_QUALITY_SIZE)

#define CRC_B0_INDEX										   (DATA_0_INDEX + DATA_SIZE)
#define CRC_B1_INDEX										   (CRC_B0_INDEX + 1)

#define STOP_SEQUENCE_B0_INDEX			 		   (CRC_B0_INDEX + CRC_SIZE)
#define STOP_SEQUENCE_B1_INDEX			 		   (STOP_SEQUENCE_B0_INDEX + 1)
#define STOP_SEQUENCE_B2_INDEX			 		   (STOP_SEQUENCE_B1_INDEX + 1)
#define STOP_SEQUENCE_B3_INDEX			 		   (STOP_SEQUENCE_B2_INDEX + 1)
#define STOP_SEQUENCE_B4_INDEX			 		   (STOP_SEQUENCE_B3_INDEX + 1)


#define FINAL_STOP_SEQUENCE_B0_INDEX       (CRC_B0_INDEX + CRC_SIZE)
#define FINAL_STOP_SEQUENCE_B1_INDEX       (FINAL_STOP_SEQUENCE_B0_INDEX + 1)
#define FINAL_STOP_SEQUENCE_B2_INDEX       (FINAL_STOP_SEQUENCE_B1_INDEX + 1)
#define FINAL_STOP_SEQUENCE_B3_INDEX       (FINAL_STOP_SEQUENCE_B2_INDEX + 1)
#define FINAL_STOP_SEQUENCE_B4_INDEX       (FINAL_STOP_SEQUENCE_B3_INDEX + 1)



//********************************************************************************//
//								SECTOR TRANSMIT SIZE									  
//********************************************************************************//

#define NEW_TRASMITION_HEADER_SIZE   		5

#define TRASMITION_HEADER_SIZE		 	    5

#define SEQUENCE_ID_SIZE						   	2

#define CAP_VOLTAGE_SIZE							  2

#define ESTIMATED_ENERGY_QUALITY_SIZE		1

#define DATA_SIZE												2048

#define CRC_SIZE											  2

#define STOP_SEQUENCE_SIZE	   			 		5

#define FINAL_STOP_SEQUENCE_SIZE	      5

//********************************************************************************//
//								build swithces									  
//********************************************************************************//

#define DEBUG_MODE					(1) 		//includes the halUnit test, creates buffer mmoery of them etc

#endif /* PROJECTDEFINES_H_ */
