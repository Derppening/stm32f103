#ifndef STM32F103_LIB_BUTTON_H_
#define STM32F103_LIB_BUTTON_H_

#include <cstdint>
#include <memory>
#include <utility>
#include <stm32f10x.h>

#include "config.h"
#include "gpio.h"
#include "util.h"

#if !defined(LIB_USE_BUTTON) || LIB_USE_BUTTON < 1
#error "This configuration is not specified to use this library"
#endif  // !defined(LIB_USE_BUTTON) || LIB_USE_BUTTON < 1

/**
 * @brief Implements button-related features.
 */
class Button {
 public:
  /**
   * @brief Configuration for button.
   */
  struct Config {
    /**
     * @brief ID of button.
     */
    uint8_t id;
  };

  /**
   * @brief Constructor for button.
   *
   * @param config Button configuration
   */
  explicit Button(const Config& config);
  /**
   * @return State of button
   */
  bool Read();

 protected:
  /**
   * @return Pinout of button
   */
  Pin* GetPin() { return &pin_; }

  /**
   * @return GPIO object underlying the button
   */
  GPIO* GetGpio() { return gpio_.get(); }

 private:
  Pin pin_;
  std::unique_ptr<GPIO> gpio_ = nullptr;
};

#endif
