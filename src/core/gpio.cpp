#include "gpio.h"

#include <cassert>

Gpio::Gpio(GPIO_TypeDef* port, uint16_t pin) : port_(port) {
  GPIO_StructInit(&GPIO_InitStructure_);
  GPIO_InitStructure_.GPIO_Pin = pin;
}

void Gpio::Init(GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed, uint32_t rcc) {
  Rcc(ENABLE, rcc);
  GPIO_InitStructure_.GPIO_Mode = Mode;
  GPIO_InitStructure_.GPIO_Speed = Speed;
  GPIO_Init(port_, &(GPIO_InitStructure_));
}

void Gpio::Rcc(FunctionalState state, uint32_t rcc) {
  if (port_ == GPIOA) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | rcc, state);
  } else if (port_ == GPIOB) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | rcc, state);
  } else if (port_ == GPIOC) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | rcc, state);
  } else if (port_ == GPIOD) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | rcc, state);
  } else if (port_ == GPIOE) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | rcc, state);
  } else if (port_ == GPIOF) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | rcc, state);
  } else if (port_ == GPIOG) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG | rcc, state);
  }
}

void Gpio::Set() {
  Set(true);
}

void Gpio::Reset() {
  Set(false);
}

void Gpio::Toggle() {
  Set(!static_cast<bool>(Read()));
}

void Gpio::Set(bool state) {
  if (state) {
    GPIO_WriteBit(port_, GPIO_InitStructure_.GPIO_Pin, Bit_SET);
  } else {
    GPIO_WriteBit(port_, GPIO_InitStructure_.GPIO_Pin, Bit_RESET);
  }
}

uint8_t Gpio::Read() {
  return GPIO_ReadInputDataBit(port_, GPIO_InitStructure_.GPIO_Pin);
}

uint16_t Gpio::GetPinSource() {
  switch (GPIO_InitStructure_.GPIO_Pin) {
    case GPIO_Pin_0: return GPIO_PinSource0;
    case GPIO_Pin_1: return GPIO_PinSource1;
    case GPIO_Pin_2: return GPIO_PinSource2;
    case GPIO_Pin_3: return GPIO_PinSource3;
    case GPIO_Pin_4: return GPIO_PinSource4;
    case GPIO_Pin_5: return GPIO_PinSource5;
    case GPIO_Pin_6: return GPIO_PinSource6;
    case GPIO_Pin_7: return GPIO_PinSource7;
    case GPIO_Pin_8: return GPIO_PinSource8;
    case GPIO_Pin_9: return GPIO_PinSource9;
    case GPIO_Pin_10: return GPIO_PinSource10;
    case GPIO_Pin_11: return GPIO_PinSource11;
    case GPIO_Pin_12: return GPIO_PinSource12;
    case GPIO_Pin_13: return GPIO_PinSource13;
    case GPIO_Pin_14: return GPIO_PinSource14;
    case GPIO_Pin_15: return GPIO_PinSource15;
    default: assert(false);
  }
  return 0;
}

GPIO_TypeDef* Gpio::GetPort() {
  return port_;
}

uint16_t Gpio::GetPin() {
  return GPIO_InitStructure_.GPIO_Pin;
}
