#include "ticks.h"

uint32_t ms_ticks;
TIM _ticks(TIM2, RCC_APB1Periph_TIM2, TIM2_IRQn);

void ticks::init()
{
	_ticks.init(85, TIM_CounterMode_Up, 1000, TIM_CKD_DIV4, &ticks::interrupt_handler, 0, 5);
}

void ticks::interrupt_handler()
{
	if (TIM_GetITStatus(_ticks.getBase(), TIM_IT_Update) != RESET)
	{
		ms_ticks++;
		TIM_ClearITPendingBit(_ticks.getBase(), TIM_IT_Update);
	}
}
