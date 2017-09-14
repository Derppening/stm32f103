#ifndef STM32F103_CORE_TIMER_H_
#define STM32F103_CORE_TIMER_H_

#include <functional>

#include <misc.h>
#include <stm32f10x_tim.h>

class Timer {
 public:
  using Listener = std::function<void()>;

  struct Config {
    TIM_TypeDef* tim;
    uint32_t rcc;
    IRQn irqn;

    uint16_t prescaler;
    uint16_t period;
  };

  explicit Timer(const Config& config);

  void SetInterrupt(Listener&& listener);

 protected:
  void Init(uint16_t prescaler, uint16_t period);

 private:
  Listener listener_ = nullptr;

  TIM_TypeDef* tim_ = nullptr;
  uint32_t rcc_;
  IRQn irq_;
};

#endif  // STM32F103_CORE_TIMER_H_
