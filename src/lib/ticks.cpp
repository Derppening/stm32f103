#include "ticks.h"

volatile uint32_t counter;

void ticks::init()
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	SysTick_Config (RCC_Clocks.HCLK_Frequency / 1000);
}

uint32_t ticks::getTicks()
{
	return counter;
}

void SysTick_Handler()
{
	counter++;
}
