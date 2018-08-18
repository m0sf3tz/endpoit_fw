#pragma once

extern RCC_OscInitTypeDef rccHandle;

void initRcc65khz(void);
void initRcc4mhz(void);
void initRcc32mhz(void);

void initSysTick(void);

