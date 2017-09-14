#include "timer.h"

#include <cassert>

Timer::Timer(const Config& config) :
    tim_(config.tim),
    rcc_(config.rcc),
    irq_(config.irqn) {
  assert(tim_ != nullptr);
  Init(config.prescaler, config.period);
}

void Timer::Init(uint16_t prescaler, uint16_t period) {
  TIM_TimeBaseInitTypeDef TIM_InitStructure;
  RCC_APB1PeriphClockCmd(rcc_, ENABLE);
  TIM_InitStructure.TIM_Prescaler = prescaler;
  TIM_InitStructure.TIM_Period = period;
  TIM_TimeBaseInit(tim_, &TIM_InitStructure);
  TIM_Cmd(tim_, ENABLE);
}

void Timer::SetInterrupt(Listener&& listener) {
  listener_ = listener;

  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ClearITPendingBit(tim_, TIM_IT_Update);
  TIM_ITConfig(tim_, TIM_IT_Update, ENABLE);
  NVIC_InitStructure.NVIC_IRQChannel = irq_;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
