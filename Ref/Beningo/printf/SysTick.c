#include "SysTick.h"
#include "stm32l053xx.h"
#include <stdint.h>

static uint32_t volatile Tick = 0;

void SysTick_Handler(void)
{
	Tick++;	
}

uint32_t SysTick_Get(void)
{
	return Tick;
}

void SysTick_Init(void)
{
	SysTick_Config(SystemCoreClock/100);
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 2);
}
