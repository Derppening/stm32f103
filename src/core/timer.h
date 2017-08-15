#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x_tim.h"
#include "misc.h"

class TIMER
{

	private:
	TIM_TypeDef* TIM;
	uint32_t rcc;
	IRQn IRQ;

	public:
	void (*listener)(void);
	TIMER(TIM_TypeDef* TIM, uint32_t rcc, IRQn IRQn);
	void init(uint16_t Prescaler, uint16_t Period);
	void interrupt(void (*callback)(void));

};

#endif
