#ifndef STM32F103_LIB_LED_H_
#define STM32F103_LIB_LED_H_

#include <cstdint>
#include <memory>
#include <utility>
#include <stm32f10x.h>

#include "config.h"
#include "gpio.h"
#include "util.h"

#if !defined(LIB_USE_LED) || LIB_USE_LED < 1
#error "This configuration is not specified to use this library"
#endif  // !defined(LIB_USE_LED) || LIB_USE_LED < 1

class Led {
 public:
  struct Config {
    uint8_t id;
  };

  explicit Led(const Config& config);

  void SetEnable(const bool flag);
  void Switch();

 protected:
  Pin* GetPin() { return &pin_; }

  Gpio* GetGpio() { return gpio_.get(); }

 private:
  Pin pin_;
  std::unique_ptr<Gpio> gpio_;
};

#endif  // STM32F103_LIB_LED_H_
