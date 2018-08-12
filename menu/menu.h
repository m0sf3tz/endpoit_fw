#include <stdbool.h>
#include <stdint.h>

#pragma once


typedef struct{
	const char * menuOptions[10];
	int size;  // = 
	bool (*nextMenuPointer[10])( void );
}menuOption;


bool zigbeeMenu_f(void);
bool mainMenu_f(void);
bool timerMenu_f(void);
bool adcMenu_f(void);
bool coreTask_f(void);
bool powerTasks_f(void);
bool pgaTasks_f(void);


void uartPutMenuAutoCount(const char *pt);
void clearScrean(void);
void printMenu(menuOption  *);
static void printStars(void);


static void printHeading(uint8_t number, char * pt);
static uint8_t getLen(const char * pt);
void printNewLine(void);
static uint8_t menuSelect(void);

void UlToStr(char *s, uint32_t, unsigned char n);
void blockForInput(void);


