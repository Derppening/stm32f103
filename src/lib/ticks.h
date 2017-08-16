#ifndef _TICKS_H
#define _TICKS_H

#include "stm32f10x_rcc.h"
#include "core_cm3.h"

namespace ticks
{
	void init();
	uint32_t getTicks();
}

extern "C"
{
	void SysTick_Handler();
}

#endif
