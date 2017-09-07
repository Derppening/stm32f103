#ifndef STM32F103_CORE_GPIO_H_
#define STM32F103_CORE_GPIO_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "util.h"

class Gpio {
 public:
  Gpio(GPIO_TypeDef* port, uint16_t pin);

  explicit Gpio(Pin pin) : Gpio(pin.first, pin.second) {}

  void Init(GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed, uint32_t rcc = 0);
  void Rcc(FunctionalState state, uint32_t rcc = 0);

  void Set();
  void Set(bool state);
  void Reset();
  void Toggle();

  uint8_t Read();
  uint16_t GetPinSource();
  GPIO_TypeDef* GetPort();
  uint16_t GetPin();

 private:
  GPIO_TypeDef* port_;
  GPIO_InitTypeDef GPIO_InitStructure_;
};

#endif  // STM32F103_CORE_GPIO_H_
