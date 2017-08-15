#include "timer_config.h"

TIMER CLK2(TIM2, RCC_APB1Periph_TIM2, TIM2_IRQn);

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		if (CLK2.listener != 0)
		{
			CLK2.listener();
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		}
	}
}
