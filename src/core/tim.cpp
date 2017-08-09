#include "tim.h"

void (*TIM2_interrupt)(void);
void (*TIM3_interrupt)(void);
void (*TIM4_interrupt)(void);

void TIM2_IRQHandler()
{
	TIM2_interrupt();
}

void TIM3_IRQHandler()
{
	TIM3_interrupt();
}

void TIM4_IRQHandler()
{
	TIM4_interrupt();
}

TIM::TIM(TIM_TypeDef* base, uint32_t rcc, IRQn_Type IRQ)
{
	this->base = base;
	this->rcc = rcc;
	this->IRQ = IRQ;
}

void TIM::init(uint16_t Prescaler, uint16_t CounterMode, uint32_t Period, uint16_t ClockDivision)
{
	this->TIM_InitStructure.TIM_Prescaler = Prescaler;
	this->TIM_InitStructure.TIM_CounterMode = CounterMode;
	this->TIM_InitStructure.TIM_Period = Period;
	this->TIM_InitStructure.TIM_ClockDivision = ClockDivision;
	this->TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(this->base, &(this->TIM_InitStructure));
	TIM_Cmd(this->base, ENABLE);
}

void TIM::init(uint16_t Prescaler, uint16_t CounterMode, uint32_t Period, uint16_t ClockDivision, void (*interrupt)(void), uint8_t PreemptionPriority, uint8_t SubPriority)
{
	this->TIM_InitStructure.TIM_Prescaler = Prescaler;
	this->TIM_InitStructure.TIM_CounterMode = CounterMode;
	this->TIM_InitStructure.TIM_Period = Period;
	this->TIM_InitStructure.TIM_ClockDivision = ClockDivision;
	this->TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(this->base, &(this->TIM_InitStructure));
	if (this->IRQ == TIM2_IRQn)
	{
		TIM2_interrupt = interrupt;
	}
	else if (this->IRQ == TIM3_IRQn)
	{
		TIM3_interrupt = interrupt;
	}
	else if (this->IRQ == TIM4_IRQn)
	{
		TIM4_interrupt = interrupt;
	}
	TIM_ITConfig(this->base, TIM_IT_Update, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = this->IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(this->base, ENABLE);
}

TIM_TypeDef* TIM::getBase()
{
	return this->base;
}
