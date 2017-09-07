#ifndef STM32F103_LIB_BUTTON_H_
#define STM32F103_LIB_BUTTON_H_

#include <cstdint>
#include <utility>
#include <stm32f10x.h>

#include "config.h"
#include "gpio.h"
#include "util.h"

#if !defined(LIB_USE_BUTTON) || LIB_USE_BUTTON < 1
#error "This configuration is not specified to use this library"
#endif  // !defined(LIB_USE_BUTTON) || LIB_USE_BUTTON < 1

class Button {
 public:
  struct Config {
    uint8_t id;
  };

  explicit Button(const Config& config);
  bool Read();

 protected:
  Pin* GetPin() { return &pin_; }

  Gpio* GetGpio() { return &gpio_; }

 private:
  Pin pin_;
  Gpio gpio_;
};

#endif
