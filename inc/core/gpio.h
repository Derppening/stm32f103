// gpio.h
//
// This file contains the class manipulating Gpio-related functions, including both reading from and write to a GPIO
// pinout.

#ifndef STM32F103_CORE_GPIO_H_
#define STM32F103_CORE_GPIO_H_

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "util.h"

class Gpio {
 public:
  /**
   * @brief Constructor accepting a port and a pin.
   *
   * @param port Port. Usually in the format of GPIOx, where x is an upper case character.
   * @param pin Pin number. Usually in the format of GPIO_Pin_x, where x is a positive integer.
   */
  Gpio(GPIO_TypeDef* port, uint16_t pin);

  /**
   * @brief Constructor accept a Pin object.
   *
   * @note For most use cases, this constructor is unnecessary. @c Gpio(GPIO_TypeDef*,uint16_t) is similar to this
   * in every single way, except it lacks the overhead of delegating to the above constructor.
   *
   * @param pin Pin object.
   */
  explicit Gpio(Pin pin) : Gpio(pin.first, pin.second) {}

  /**
   * @brief Performs initialization of this GPIO.
   *
   * @param Mode
   * @param Speed
   * @param rcc
   */
  void Init(GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed, uint32_t rcc = 0);
  void Rcc(FunctionalState state, uint32_t rcc = 0);

  /**
   * @brief Set this GPIO to low position.
   *
   * @note Use @c Set(bool) instead. Please.
   */
  void Reset();
  /**
   * @brief Set this GPIO to high position.
   *
   * @note Use @c Set(bool) instead. Please.
   */
  void Set();
  /**
   * @brief Sets this GPIO to @c state.
   *
   * @param state New state of GPIO
   */
  void Set(bool state);
  /**
   * @brief Swap the state of the GPIO.
   */
  void Toggle();

  /**
   * @brief Read the current state of GPIO.
   * @return Current state of GPIO
   */
  uint8_t Read();

  uint16_t GetPinSource();
  GPIO_TypeDef* GetPort();
  uint16_t GetPin();

 private:
  GPIO_TypeDef* port_;
  GPIO_InitTypeDef GPIO_InitStructure_;
};

#endif  // STM32F103_CORE_GPIO_H_
