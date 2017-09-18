#include "config.h"

#ifdef LIB_USE_LED

#include "led.h"

#include <cassert>

namespace {
/**
 * @param id ID of the LED we are using
 * @return Pin for the LED
 */
inline Pin GetPinout(const uint8_t id) {
  assert_param(id < LIB_USE_LED);
  switch (id) {
    default:
      assert(false);
      [[fallthrough]];
#if LIB_USE_LED > 0
    case 0:
      return LIB_LED1_PINOUT;
#endif  // LIB_USE_LED > 0
#if LIB_USE_LED > 1
    case 1:
      return LIB_LED2_PINOUT;
#endif  // LIB_USE_LED > 1
#if LIB_USE_LED > 2
    case 2:
      return LIB_LED3_PINOUT;
#endif  // LIB_USE_LED > 2
  }
}
}  // namespace

Led::Led(const Config& config) :
    pin_(GetPinout(config.id)) {
  GPIO::Config gpio_config;
  gpio_config.pin = pin_;
  gpio_config.mode = GPIO_Mode_Out_PP;
  gpio_config.speed = GPIO_Speed_50MHz;
  gpio_ = std::make_unique<GPIO>(gpio_config);

  assert(gpio_ != nullptr);
}

void Led::SetEnable(const bool flag) {
  gpio_->Set(flag);
}

void Led::Switch() {
  gpio_->Toggle();
}

#endif  // LIB_USE_LED
