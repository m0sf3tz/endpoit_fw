#include "menu.h"
#include "stm32l0xx_hal_uart.h"
#include "uartHal.h"
#include "memorySelfTest.h"
#include "sampler.h"
#include "zigbee.h"
#include "ldo.h"
#include "pga.h"
#include "adc.h"
#include "sectorLogic.h"

const char newLine						  	= 12;	//line feed in assci
const char RESQUEST_RESPONSE[]    = "please select an option from above: ";
const char NUMBER_OFFSET_ANSCII   = 49;

bool placeholder()
{
	return 1;
}


bool adcMenu_f()
{

		static menuOption adcMenu = 
		{
			
			{
				" Grab on die ADC value",			//1
			},
			
			1,
				
			{	
				adcUnitTestOnDie,
			}
		};
		
		printMenu(&adcMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected < (adcMenu.size))
				(*adcMenu.nextMenuPointer[selected])();
		else
			return 0;

		return 0;
}




bool timerMenu_f()
{
/*
		static volatile menuOption timerMenu = 
		{
			
			{
				" Basic Timer Unit Test"			//1
			},
			
			1,
				
			{	
				timerUnitTest
			}
		};
		
		printMenu(&timerMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected >= 0 && selected < (timerMenu.size))
				(*timerMenu.nextMenuPointer[selected])();
		else
			return 0;
*/return 0;

}

bool spiMem_f()
{

	static  menuOption genericMenu = 
		{
			
			{
				" Full test -  ST drivers",				//1
				" Full test -  LLD drivers",			  //2
				" N/A",									//3
				" Fill entire array with sawTooth pattern (0-255)"													//4
			},
			
			4,
				
			{	
				spiWalkTest,
				spiWalkTestRegisterSequentialMode,
				spiWalkTest, //ignore
				fillSpiSawTooth
			}
		};

		
		printMenu(&genericMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected < (genericMenu.size))
			return (*genericMenu.nextMenuPointer[selected])();
		else
			return 0;
}


bool coreTask_f()
{
	static  menuOption coreMen = 
		{
			
			{
				" Read first sector into a uart sendBuffer (not maintined)",				//1
				" Fill a buffer, fill it with MEM, and Zigbee it up (not maintined)", 
				" Fill   up 20 blocks of memory from the on-die ADC",
				" Zigbee up 20 sectors up",
				" Zigbee up one sector (multiple blocks) + CRC + other stuff"
			},
			
			5,
				
			{	
				fillBlockMenuShim,
				bufferToZigbeeShim,
				multiSectorSpiMemFillShim,
				streamAllSPiZigbee,
				sectorBufToZigbee
			}
		};

		
		printMenu(&coreMen);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if( selected < (coreMen.size))
				(*coreMen.nextMenuPointer[selected])();
		else
			return 0;
	  return true;
}


bool sampleLoop_f()
{
/*	
	static volatile menuOption genericMenu = 
		{
			
			{
				" Grab 16 samples of external ADC value using interrupts", //1
				" Grab 25 blocks of ADC value and store starting from block 0" //2
				
			},
			
			2,
				
			{	
				multipleSampleExternalAdcTest,
				multipleSampleExternalAdcTestStoreInSram_m,
			}
		};
		
		printMenu(&genericMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected >= 0 && selected < (genericMenu.size))
				(*genericMenu.nextMenuPointer[selected])();
		else
			return 0;
*/return 0;

}





bool zigbeeMenu_f()
{
		static menuOption zigBeeMenu = 
		{
			
			{
				" Send 256 chunks of incrementing data",			//1
				" ZIGBEE_WAKE ",														  //2
				" ZIGBEE_DOZE ",															//3
			},
			
			3,
				
			{	
				zigbeeTestSendIncrementing,
				ZIGBEE_WAKE,
				ZIGBEE_DOZE,
			}
		};

		
		printMenu(&zigBeeMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected < (zigBeeMenu.size))
				(*zigBeeMenu.nextMenuPointer[selected])();
		else
			return 0;
		return true;
}

bool powerTasks_f()
{
		static menuOption powerMenu = 
		{
			
			{
				" Enable samlping Supply",			//1
				" Disable samlping Supply",			//1

			},
			
			2,
				
			{	
				enableSamplingSupply,
				disableSamplingSupply,
			}
		};

		
		printMenu(&powerMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected < (powerMenu.size))
				(*powerMenu.nextMenuPointer[selected])();
		else
			return 0;
		return true;
}


bool pgaTasks_f()
{
		static menuOption powerMenu = 
		{
			
			{
				" Set Gain 1",			//1
				" Set Gain 2",			//2
				" Set Gain 10",			//3
				" Set Gain 16" 			//4

			},
			
			4,
				
			{	
				setGainGpa1,
				setGainGpa2,
				setGainGpa10,
				setGainGpa16
			}
		};

		
		printMenu(&powerMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if(selected < (powerMenu.size))
				(*powerMenu.nextMenuPointer[selected])();
		else
			return 0;
		return true;
}


	

bool mainMenu_f()
{
	for(;;)
	{
		static  menuOption mainMenu = 
		{
			{
				" ZigBee",
				" Timer" ,
				" adc(s)",
				" SRAM spi memory", //4
				" sampleLoop",
				" coreTasks",
				" power menue",
	      " PGA menue"

			},
			
			8,
			
			{	
				zigbeeMenu_f,
				timerMenu_f,
				adcMenu_f,
				spiMem_f,
				sampleLoop_f,
				coreTask_f,
				powerTasks_f,
				pgaTasks_f
			}
		};

		
		printMenu(&mainMenu);
		
		printNewLine();
		uint8_t selected = menuSelect();
		
		if( selected < mainMenu.size)
		{
			(*mainMenu.nextMenuPointer[selected])();
		}
	}
}
		
			



void uartPutMenuAutoCount(const char *pt)
{
	uint8_t len = getLen(pt);
	uartPutMenu(pt,len);
}


void clearScreen()
{	
	char cs[] = "\033[2J";
	char mh[] = "\033[H";
  char cs2[] = "G"; 	//screen is eating one letter after reset?

	uartPutMenu(cs,7);
	uartPutMenu(mh,6);
	uartPutMenu(cs2,1);	
	
}

void printMenu( menuOption * menu )
{
	clearScreen();
	printStars();
	printNewLine();
	int items = 0;
	
	
	while(items != menu->size)
	{
			int len = getLen(menu->menuOptions[items]);
			char selection = items + NUMBER_OFFSET_ANSCII; //difference between 0 and "0"
			uartPutMenu(&selection,1);	//put selection numebr

  		uartPutMenu(menu->menuOptions[items],len);
			printNewLine();
	
	  	items++;
	}
	
}

void printStars()
{
	const char prettyStar[] = "*******************************************************************************";
	int size = (sizeof (prettyStar) / sizeof (const char));
	uartPutMenu(prettyStar,size);	
}



static uint8_t getLen(const char * pt)
{
	uint8_t count = 0;
	
	while(*pt++ != 0)	//null
	{
		count++;
	}
	return count;
}


void printNewLine()
{
	
	const char left = 0xd;
	const char NL   = 0xa;
	
	uartPutMenu(&NL,1);	
	uartPutMenu(&left,1);
}


static uint8_t menuSelect()
{
	printNewLine();
	uint8_t len = getLen(RESQUEST_RESPONSE);
	uartPutMenu(RESQUEST_RESPONSE,len);	

	char selected;
	
	uartGetMenu(&selected, 1);
	uartPutMenu(&selected, 1);

	selected = selected - NUMBER_OFFSET_ANSCII;

	return selected;
}


void UlToStr(char *s, uint32_t bin, unsigned char n)
{
    s += n;
    *s = '\0';

    while (n--)
    {
        *--s = (bin % 10) + '0';
        bin /= 10;
    }
}


void blockForInput()
{
	char null;
	uartGetMenu(&null,1);
}
