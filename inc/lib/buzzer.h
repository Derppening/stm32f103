#ifndef STM32F103_LIB_BUZZER_H_
#define STM32F103_LIB_BUZZER_H_

#include <cstdint>
#include <memory>
#include <stm32f10x.h>

#include "config.h"
#include "gpio.h"
#include "util.h"

#if !defined(LIB_USE_BUZZER) || LIB_USE_BUZZER < 1
#error "This configuration is not specified to use this library"
#endif  // !defined(LIB_USE_BUZZER) || LIB_USE_BUZZER < 1

/**
 * @brief Implements abstraction layer for buzzers.
 */
class Buzzer {
 public:
  /**
   * @brief Configuration for buzzers.
   */
  struct Config {
    /**
     * @brief ID of buzzer.
     */
    uint8_t id;
  };

  /**
   * @brief Constructor for buzzer.
   *
   * @note Buzzer will always be in off state after constructor is called. If it isn't, your board may have a pull-up
   * resistor, and this feature will be implemented later.
   *
   * @param config Buzzer configuration
   */
  explicit Buzzer(const Config& config);

  /**
   * @brief Sets the state of the buzzer.
   *
   * @param flag True if the buzzer should be on
   */
  void SetEnable(const bool flag);

 protected:
  /**
   * @return Pinout of buzzer
   */
  Pin* GetPin() { return &pin_; }

  /**
   * @return GPIO object underlying the buzzer
   */
  GPIO* GetGpio() { return gpio_.get(); }

 private:
  Pin pin_;
  std::unique_ptr<GPIO> gpio_;
};

#endif  // STM32F103_LIB_BUZZER_H_
