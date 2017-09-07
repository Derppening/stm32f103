#ifndef STM32F103_LIB_BUTTON_H_
#define STM32F103_LIB_BUTTON_H_

#include <cstdint>

#include <utility>

#include <stm32f10x.h>

#include "gpio.h"
#include "util.h"

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
