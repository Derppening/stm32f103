#include "timer.h"

TIMER::TIMER(TIM_TypeDef* TIM, uint32_t rcc, IRQn IRQn)
{
	this->TIM = TIM;
	this->rcc = rcc;
	this->IRQ = IRQn;
	this->listener = 0;
}

void TIMER::init(uint16_t Prescaler, uint16_t Period)
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	RCC_APB1PeriphClockCmd(this->rcc , ENABLE);
	TIM_InitStructure.TIM_Prescaler = Prescaler;
	TIM_InitStructure.TIM_Period = Period;
	TIM_TimeBaseInit(this->TIM, &TIM_InitStructure);
	TIM_Cmd(this->TIM, ENABLE);
}

void TIMER::interrupt(void (*callback)(void))
{
	NVIC_InitTypeDef NVIC_InitStructure;
	this->listener = callback;
	TIM_ClearITPendingBit(this->TIM, TIM_IT_Update);
	TIM_ITConfig(this->TIM, TIM_IT_Update, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = this->IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
