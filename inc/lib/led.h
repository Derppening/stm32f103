#ifndef STM32F103_LIB_LED_H_
#define STM32F103_LIB_LED_H_

#include <cstdint>

#include <utility>

#include <CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h>

#include "gpio.h"
#include "util.h"

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
  Gpio* GetGpio() { return &gpio_; }

 private:
  Pin pin_;
  Gpio gpio_;
};

#endif  // STM32F103_LIB_LED_H_
