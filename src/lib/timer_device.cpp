#include "timer_device.h"

#include <cassert>

std::array<std::function<void()>, 7> TimerDevice::listeners_;

extern "C" void TIM1_IRQHandler();
extern "C" void TIM2_IRQHandler();
extern "C" void TIM3_IRQHandler();
extern "C" void TIM4_IRQHandler();
extern "C" void TIM5_IRQHandler();
extern "C" void TIM6_IRQHandler();
extern "C" void TIM7_IRQHandler();

extern "C" void TIM1_IRQHandler() {
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim1);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  }
}

extern "C" void TIM2_IRQHandler() {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim2);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  }
}

extern "C" void TIM3_IRQHandler() {
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim3);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  }
}

extern "C" void TIM4_IRQHandler() {
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim4);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  }
}

extern "C" void TIM5_IRQHandler() {
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim5);
    TIM_ClearFlag(TIM5, TIM_FLAG_Update);
  }
}

extern "C" void TIM6_IRQHandler() {
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim6);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
  }
}

extern "C" void TIM7_IRQHandler() {
  if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {
    TimerDeviceTriggerListener(TimerDevice::kTim7);
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
  }
}

void TimerDeviceTriggerListener(const TimerDevice::Timers timer_device) {
  auto listener = TimerDevice::InvokeListener(timer_device);
  if (listener) {
    listener();
  }
}

TimerDevice::TimerDevice(const Config& config) :
    timer_id_(config.timer) {
  assert(timer_id_ >= 0 && timer_id_ < 7);

  Timer::Config timer_config;
  timer_config.tim = config.tim;
  timer_config.rcc = config.rcc;
  timer_config.irqn = config.irqn;
  timer_config.prescaler = config.prescaler;
  timer_config.period = config.period;

  timer_ = std::make_unique<Timer>(timer_config);
}

void TimerDevice::SetListener(Listener&& listener) {
  listeners_[timer_id_] = listener;

  timer_->EnableInterrupt();
}
