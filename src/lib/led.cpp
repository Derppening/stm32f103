#include "led.h"

#include <cassert>

#include "config.h"

#ifdef LIB_USE_LED

namespace {
inline Pin GetPin(const uint8_t id) {
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

Led::Led(const Led::Config& config) : pin_(::GetPin(config.id)), gpio_(Gpio(pin_.first, pin_.second)) {
  gpio_.Init(GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  gpio_.Reset();
}

void Led::SetEnable(const bool flag) {
  gpio_.Set(flag);
}

void Led::Switch() {
  gpio_.Toggle();
}

#else
#error "This configuration is not specified to use the Led library."
#endif  // LIB_USE_LED
