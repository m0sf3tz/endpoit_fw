#include "stm32l0xx_hal_uart.h"
#include <stdint.h>

void initUart(void);

void initUartPinsZigbee(void);
void initUartPinsMenu(void);

void deinitUartPinsZigbee(void);

void serialSpam(uint8_t *pt, uint32_t len);
void uartPutMenu(const  char * pt, int len);
void uartGetMenu(const  char * pt, int len);
void uartPut(const char *pt, int len);
bool zigbeeTestSendIncrementing(void);

