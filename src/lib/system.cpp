#include "system.h"

uint32_t System::counter_ = 0;
std::unique_ptr<TimerDevice> System::ticker_ = nullptr;

void System::TicksListener() {
  ++counter_;
}

void System::Init() {
  TimerDevice::Config td_conf;
  td_conf.tim = TIM2;
  td_conf.rcc = RCC_APB1Periph_TIM2;
  td_conf.irqn = TIM2_IRQn;
  td_conf.prescaler = 71;
  td_conf.period = 1000;
  td_conf.timer = TimerDevice::kTim2;
  ticker_ = std::make_unique<TimerDevice>(td_conf);

  ticker_->SetListener(&System::TicksListener);
}

uint32_t System::GetMs() {
  return counter_;
}
