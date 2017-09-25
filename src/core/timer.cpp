#include "timer.h"

#include <cassert>
#include <stm32f10x_conf.h>

Timer::Timer(const Config& config) :
    tim_(config.tim),
    rcc_(config.rcc),
    irq_(config.irqn) {
  // idiot-proof check
  assert(tim_ != nullptr);

  Init(config.prescaler, config.period);
}

void Timer::Init(uint16_t prescaler, uint16_t period) {
  // enable the RCC
  RCC_APB1PeriphClockCmd(rcc_, ENABLE);

  // setup the TIM_InitStructure
  TIM_TimeBaseInitTypeDef TIM_InitStructure;
  TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_InitStructure.TIM_Prescaler = prescaler;
  TIM_InitStructure.TIM_Period = period;
  TIM_InitStructure.TIM_ClockDivision = 0;
  TIM_InitStructure.TIM_RepetitionCounter = 0;

  // initialize the TIM clock
  TIM_TimeBaseInit(tim_, &TIM_InitStructure);
  TIM_Cmd(tim_, ENABLE);
}

void Timer::EnableInterrupt() {
  TIM_ClearITPendingBit(tim_, TIM_IT_Update);
  TIM_ITConfig(tim_, TIM_IT_Update, ENABLE);

  // setup the NVIC_InitStructure
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = irq_;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  // initialize the NVIC for our Timer
  NVIC_Init(&NVIC_InitStructure);
}
