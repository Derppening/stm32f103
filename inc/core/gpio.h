#ifndef STM32F103_CORE_GPIO_H_
#define STM32F103_CORE_GPIO_H_

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "util.h"

/**
 * @brief Implements an abstraction layer for GPIO.
 */
class Gpio {
 public:
  /**
   * @brief Configuration for an individual GPIO pin.
   */
  struct Config {
    /**
     * @brief GPIO Pin to enable and initialize
     */
    Pin pin;

    /**
     * @brief GPIO Mode.
     *
     * See documentation for @c GPIOMode_TypeDef.
     */
    GPIOMode_TypeDef mode;
    /**
     * @brief GPIO output maximum frequency.
     *
     * See documentation for @c GPIOSpeed_TypeDef.
     */
    GPIOSpeed_TypeDef speed = GPIO_Speed_50MHz;
    /**
     * @brief Reset and Clock Control (RCC).
     */
    uint32_t rcc = 0;
  };

  /**
   * @brief Constructor for Gpio.
   *
   * @param config GPIO configuration settings
   */
  explicit Gpio(const Config& config);

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

  /**
   * @return Pin source for the current GPIO
   */
  uint16_t GetPinSource();
  /**
   * @return Port for the current GPIO
   */
  GPIO_TypeDef* GetPort();
  /**
   * @return Pin for the current GPIO
   */
  uint16_t GetPin();

 protected:
  /**
 * @brief Performs initialization of this GPIO.
 *
 * @param mode GPIO mode
 * @param speed GPIO maximum output speed
 * @param rcc Reset and Clock Control
 */
  void Init(GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, uint32_t rcc = 0);
  /**
   * @brief Enables/Disables RCC.
   *
   * @param state ENABLE or DISABLE
   * @param rcc Reset and Clock Control
   */
  void Rcc(FunctionalState state, uint32_t rcc = 0);

 private:
  GPIO_TypeDef* port_;
  GPIO_InitTypeDef GPIO_InitStructure_;
};

#endif  // STM32F103_CORE_GPIO_H_
