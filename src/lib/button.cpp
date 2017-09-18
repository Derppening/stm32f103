#include "config.h"

#ifdef LIB_USE_BUTTON

#include "button.h"

#include <cassert>

namespace {
/**
 * @param id ID of button we are using
 * @return
 */
inline Pin GetPinout(const uint8_t id) {
  assert_param(id < LIB_USE_BUTTON);
  switch (id) {
    default:
      assert(false);
      [[fallthrough]];
#if LIB_USE_BUTTON > 0
    case 0:
      return LIB_BUTTON1_PINOUT;
#endif  // LIB_USE_LED > 0
#if LIB_USE_BUTTON > 1
    case 1:
      return LIB_BUTTON2_PINOUT;
#endif  // LIB_USE_LED > 1
  }
}
}  // namespace

Button::Button(const Config& config) :
    pin_(GetPinout(config.id)) {
  Gpio::Config gpio_config;
  gpio_config.pin = pin_;
  gpio_config.mode = GPIO_Mode_IPU;
  gpio_config.speed = GPIO_Speed_50MHz;
  gpio_ = std::make_unique<Gpio>(gpio_config);

  assert(gpio_ != nullptr);
}

bool Button::Read() {
  return !gpio_->Read();
}

#endif  // LIB_USE_BUTTON
