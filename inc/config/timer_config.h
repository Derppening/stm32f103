#ifndef _TIMER_CONFIG_H
#define _TIMER_CONFIG_H

#include "timer.h"

extern TIMER CLK2;

extern "C"
{
void TIM2_IRQHandler();
}

#endif
