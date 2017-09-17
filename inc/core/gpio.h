#ifndef STM32F103_CORE_GPIO_H_
#define STM32F103_CORE_GPIO_H_

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "util.h"

/**
 * @brief HAL implementation for GPIO pins.
 */
class Gpio {
 public:
  /**
   * @brief Configuration for an individual GPIO pin.
   */
  struct Config {
    /**
     * @brief GPIO Pin to enable and initialize.
     */
    Pin pin;

    /**
     * @brief GPIO Mode.
     *
     * See documentation for GPIOMode_TypeDef.
     */
    GPIOMode_TypeDef mode;
    /**
     * @brief GPIO output maximum frequency.
     *
     * See documentation for GPIOSpeed_TypeDef.
     */
    GPIOSpeed_TypeDef speed = GPIO_Speed_50MHz;
    /**
     * @brief Reset and Clock Control (RCC).
     *
     * Extra RCC configurations you want to enable eg. RCC_APB2Periph_AFIO
     *
     * Refer to stm32f10x_rcc.h for more RCC definitions.
     */
    uint32_t rcc = 0;
  };

  /**
   * @brief Constructor for Gpio class.
   *
   * @param config GPIO configuration settings
   */
  explicit Gpio(const Config& config);

  /**
   * @brief Sets this GPIO state based on passed in boolean.
   *
   * @param state New state of GPIO
   * | Value | Effect |
   * | :---: | :----: |
   * |  true | Drives the GPIO pin to logic high |
   * | false | Drives the GPIO pin to logic low  |
   */
  void Set(bool state);
  /**
   * @brief Toggles GPIO state, Logic High -> Logic Low and vice versa.
   */
  void Toggle();

  /**
   * @brief Read the current logic state of GPIO.
   * @return Current state of GPIO, a non-zero value represents a logic high
   */
  uint8_t Read();

  /**
   * @return Pin number representation of currently configured pin.
   *
   * Under the hood this returns the value of GPIO_PinSourceX where X is the
   * pin number. This differs from GPIO_Pin_X in that it returns the actual
   * number of the pin eg. Pin 15 -> 0x000F, whereas GPIO_Pin_X returns a register mask value,
   * eg. `( 1 << X )`
   */
  uint16_t GetPinSource();
  /**
   * @return Port for the current GPIO
   */
  GPIO_TypeDef* GetPort();
  /**
   * @return Pin mask representation of currently configured pin.
   *
   * Under the hood this returns the value of GPIO_Pin_X where X is the
   * pin number. This differs from GPIO_PinSourceX in that it returns the
   * register mask value `( 1 << X )` of the pin eg. Pin 15 -> 0x8000
   * whereas GPIO_PinSourceX returns the actual pin number eg. 0x000F
   */
  uint16_t GetPin();

 protected:
  /**
 * @brief Performs initialization of this GPIO.
 *
 * @param mode GPIO mode
 * @param speed GPIO maximum output speed
 * @param rcc Extra configuration values for Reset and Clock Control
 */
  void Init(GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, uint32_t rcc = 0);
  /**
   * @brief Enables/Disables RCC.
   *
   * @param state ENABLE or DISABLE
   * @param rcc Extra configuration values for Reset and Clock Control
   */
  void Rcc(FunctionalState state, uint32_t rcc = 0);

 private:
  GPIO_TypeDef* port_;
  GPIO_InitTypeDef GPIO_InitStructure_;
};

#endif  // STM32F103_CORE_GPIO_H_
