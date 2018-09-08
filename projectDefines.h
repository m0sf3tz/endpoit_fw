/*
 * projectDefines.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Sam2
 */

#pragma once

#define ASSERT(x) do{ \
  if(!x){while(1){}} \
  }while(0)

//********************************************************************************//
//                SPI/ADC DEFINES
//********************************************************************************//
#define BLOCK_SPI_MEM_BYTE                     256
#define ADC_SAMPLES_PER_BLOCK                  128

#define SPI_MEMORY_SRAM_SIZE_BYTES             0x1FFFF
#define SPI_TOTAL_SRAM_TOTAL_BLOCKS            SPI_MEMORY_SRAM_SIZE_BYTES/BLOCK_SPI_MEM_BYTE

#define SPI_MEMORY_BIT_RATE                    200000
#define SPI_MEMORY_ADDRESS_SIZE                8

#define ADC_BIT_RATE                           180000
#define ADC_BITS_PER_SAMPLE                    16


#define SPI_SRAM_SSI_BASE_INTERRUPT_BASE       INT_SSI0//INT_SSI0
#define SPI_SRAM_SSI_BASE                      0x40008000//SSI0_BASE
#define SPI_ANALOG_SSI_BASE                    0x40009000//SSI1_BASE


#define MAXIMUM_MEMORY_ADRESS                 0x1FFFF //max range for

#define FIRST_BLOCK_SPI                       0


//********************************************************************************//
//                SECTOR TRANSMIT CONSTANTS
//********************************************************************************//

#define NEW_TRASMITION_HEADER_B0  0xA0
#define NEW_TRASMITION_HEADER_B1  0x0B
#define NEW_TRASMITION_HEADER_B2  0xC0
#define NEW_TRASMITION_HEADER_B3  0x1D

#define TRASMITION_HEADER_B0      0x0B
#define TRASMITION_HEADER_B1      0xB1
#define TRASMITION_HEADER_B2      0x1B
#define TRASMITION_HEADER_B3      0xB2

#define STOP_SEQUENCE_B0          0xC1
#define STOP_SEQUENCE_B1          0x2C
#define STOP_SEQUENCE_B2          0xC2
#define STOP_SEQUENCE_B3          0x2C
#define STOP_SEQUENCE_B4          0xC3


#define FINAL_STOP_SEQUENCE_B0    0xD2
#define FINAL_STOP_SEQUENCE_B1    0x3D
#define FINAL_STOP_SEQUENCE_B2    0xD3
#define FINAL_STOP_SEQUENCE_B3    0x3D
#define FINAL_STOP_SEQUENCE_B4    0xD4


#define TRASMIT_BLOCK_SIZE          (TRASMITION_HEADER_SIZE + TRASMIT_SECTOR_SIZE + SEQUENCE_ID_SIZE + CAP_VOLTAGE_SIZE + ESTIMATED_ENERGY_QUALITY_SIZE + DATA_SIZE + PGA_GAIN_SIZE + FREE_SIZE + CRC_SIZE + STOP_SEQUENCE_SIZE)

//these guys are used in C programs upstreams - not used in endpoint FW
#define NEW_TRANSMIT_HEADER_32_BITS  (0xA00BC01D)

#define TRANSMIT_HEADER_32_BITS      (0x1BB11BB1)
#define STOP_SEQUENCE_64_BITS        (0xC22CC22CC2ull)

#define FINAL_STOP_SEQUENCE_64_BITS  (0xD23DD33DD4ull)


//********************************************************************************//
//                SECTOR TRANSMIT INDEX
//********************************************************************************//

#define NEW_TRASMITION_HEADER_B0_INDEX     0
#define NEW_TRASMITION_HEADER_B1_INDEX     (NEW_TRASMITION_HEADER_B0_INDEX  + 1)
#define NEW_TRASMITION_HEADER_B2_INDEX     (NEW_TRASMITION_HEADER_B1_INDEX  + 1)
#define NEW_TRASMITION_HEADER_B3_INDEX     (NEW_TRASMITION_HEADER_B2_INDEX  + 1)


#define TRASMITION_HEADER_B0_INDEX         0
#define TRASMITION_HEADER_B1_INDEX         (TRASMITION_HEADER_B0_INDEX      + 1)
#define TRASMITION_HEADER_B2_INDEX         (TRASMITION_HEADER_B1_INDEX      + 1)
#define TRASMITION_HEADER_B3_INDEX         (TRASMITION_HEADER_B2_INDEX      + 1)


#define TRASMIT_SECTOR_B0_INDEX            (NEW_TRASMITION_HEADER_B0_INDEX + NEW_TRASMITION_HEADER_SIZE)


#define SEQUENCE_ID_B0_INDEX               (TRASMIT_SECTOR_B0_INDEX + TRASMIT_SECTOR_SIZE)
#define SEQUENCE_ID_B1_INDEX               (SEQUENCE_ID_B0_INDEX +1)

#define CAP_VOLTAGE_B0_INDEX               (SEQUENCE_ID_B0_INDEX + SEQUENCE_ID_SIZE)
#define CAP_VOLTAGE_B1_INDEX               (CAP_VOLTAGE_B0_INDEX + 1)

#define ESTIMATED_ENERGY_QUALITY_INDEX     (CAP_VOLTAGE_B0_INDEX + CAP_VOLTAGE_SIZE)

#define DATA_0_INDEX                       (ESTIMATED_ENERGY_QUALITY_INDEX + ESTIMATED_ENERGY_QUALITY_SIZE)

#define PGA_GAIN_INDEX                     (DATA_0_INDEX + DATA_SIZE)

#define FREE_B0_INDEX                      (PGA_GAIN_INDEX + PGA_GAIN_SIZE)
#define FREE_B1_INDEX                      (FREE_B0_INDEX + 1)
#define FREE_B2_INDEX                      (FREE_B1_INDEX + 1)
#define FREE_B3_INDEX                      (FREE_B2_INDEX + 1)

#define CRC_B0_INDEX                       (FREE_B0_INDEX + FREE_SIZE)
#define CRC_B1_INDEX                       (CRC_B0_INDEX + 1)

#define STOP_SEQUENCE_B0_INDEX             (CRC_B0_INDEX + CRC_SIZE)
#define STOP_SEQUENCE_B1_INDEX             (STOP_SEQUENCE_B0_INDEX + 1)
#define STOP_SEQUENCE_B2_INDEX             (STOP_SEQUENCE_B1_INDEX + 1)
#define STOP_SEQUENCE_B3_INDEX             (STOP_SEQUENCE_B2_INDEX + 1)
#define STOP_SEQUENCE_B4_INDEX             (STOP_SEQUENCE_B3_INDEX + 1)


#define FINAL_STOP_SEQUENCE_B0_INDEX       (CRC_B0_INDEX + CRC_SIZE)
#define FINAL_STOP_SEQUENCE_B1_INDEX       (FINAL_STOP_SEQUENCE_B0_INDEX + 1)
#define FINAL_STOP_SEQUENCE_B2_INDEX       (FINAL_STOP_SEQUENCE_B1_INDEX + 1)
#define FINAL_STOP_SEQUENCE_B3_INDEX       (FINAL_STOP_SEQUENCE_B2_INDEX + 1)
#define FINAL_STOP_SEQUENCE_B4_INDEX       (FINAL_STOP_SEQUENCE_B3_INDEX + 1)



//********************************************************************************//
//                SECTOR TRANSMIT SIZE
//********************************************************************************//

#define NEW_TRASMITION_HEADER_SIZE       4

#define TRASMITION_HEADER_SIZE           4

#define TRASMIT_SECTOR_SIZE              1

#define SEQUENCE_ID_SIZE                 2

#define CAP_VOLTAGE_SIZE                 2

#define ESTIMATED_ENERGY_QUALITY_SIZE    1

#define DATA_SIZE                        2048

#define PGA_GAIN_SIZE                    1

#define FREE_SIZE                        4

#define CRC_SIZE                         2

#define STOP_SEQUENCE_SIZE               5

#define FINAL_STOP_SEQUENCE_SIZE         5

#define CRC_PROTECED_SIZE                (TRASMIT_SECTOR_SIZE + SEQUENCE_ID_SIZE + CAP_VOLTAGE_SIZE + ESTIMATED_ENERGY_QUALITY_SIZE + DATA_SIZE + PGA_GAIN_SIZE + FREE_SIZE) // size of data protected by CRC, starting at SEQUENCE_ID_B0_INDEX

//********************************************************************************//
//                blocks <---> sector logic
//********************************************************************************//
//currently there are 8 blocks per sector (2048/256)

#define SECTORS_PER_SAMPLE       (3)
#define BLOCKS_PER_SECTOR        (DATA_SIZE/BLOCK_SPI_MEM_BYTE) //8
#define TOTAL_BLOCKS_IN_SAMPLE   (SECTORS_PER_SAMPLE*BLOCKS_PER_SECTOR)

#define FIRST_TRASMIT_SECTOR      (0)
#define LAST_TRANSMIT_SECTOR      (SECTORS_PER_SAMPLE - 1)

#define TOTAL_BYTES_IN_SECTOR     (TRASMIT_BLOCK_SIZE*SECTORS_PER_SAMPLE)
//we need to take one away to account for byte - to index offset
#define FINAL_INDEX_SAMPLE        (TOTAL_BYTES_IN_SECTOR - 1)  
//********************************************************************************//
//                VCAP targets before we kick off tasks(see notes.h)
//********************************************************************************//

#define VCAP_TARGET_SAMPLE          (0x164F)
#define VCAP_TARGET_CREATE_TX_BUFF  (0x164F)
#define VCAP_TARGET_TRANSMIT        (0x1EAD)


//********************************************************************************//
//                build swithces
//********************************************************************************//




#define DEBUG_MODE          (1)     //includes the halUnit test, creates buffer mmoery of them etc

