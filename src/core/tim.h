#ifndef _TIM_H
#define _TIM_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

class TIM
{

	private:
	TIM_TypeDef* base;
	uint32_t rcc;
	IRQn_Type IRQ;
	TIM_TimeBaseInitTypeDef TIM_InitStructure;

	public:
	TIM(TIM_TypeDef* base, uint32_t rcc, IRQn_Type IRQ);
	void init(uint16_t Prescaler, uint16_t CounterMode, uint32_t Period, uint16_t ClockDivision);
	void init(uint16_t Prescaler, uint16_t CounterMode, uint32_t Period, uint16_t ClockDivision, void (*interrupt)(void), uint8_t PreemptionPriority = 0, uint8_t SubPriority = 0);
	TIM_TypeDef* getBase();

};

#endif
