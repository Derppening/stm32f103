#include "button.h"

#include <cassert>

#include "config.h"

#ifdef LIB_USE_BUTTON

namespace {
inline Pin GetPin(const uint8_t id) {
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

Button::Button(const Config& config) : pin_(::GetPin(config.id)), gpio_(Gpio(pin_.first, pin_.second)) {
  gpio_.Init(GPIO_Mode_IPU, GPIO_Speed_50MHz);
}

bool Button::Read() {
  return !static_cast<bool>(gpio_.Read());
}

#else
#error "This configuration is not specified to use the Button library."
#endif  // LIB_USE_BUTTON
