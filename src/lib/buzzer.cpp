#include "config.h"

#ifdef LIB_USE_BUZZER

#include "buzzer.h"

#include <cassert>

namespace {
inline Pin GetPinout(const uint8_t id) {
  assert_param(id < LIB_USE_BUZZER);
  switch (id) {
    default:
      assert(false);
      [[fallthrough]];
#if LIB_USE_BUZZER > 0
    case 0:
      return LIB_BUZZER1_PINOUT;
#endif  // LIB_USE_BUZZER > 0
  }
}
}  // namespace

Buzzer::Buzzer(const Config& config) :
    pin_(GetPinout(config.id)) {
  GPIO::Config gpio_config;
  gpio_config.pin = pin_;
  gpio_config.mode = GPIO_Mode_Out_PP;
  gpio_config.speed = GPIO_Speed_50MHz;
  gpio_ = std::make_unique<GPIO>(gpio_config);

  assert(gpio_ != nullptr);

  SetEnable(false);
}

void Buzzer::SetEnable(const bool flag) {
  gpio_->Set(flag);
}

#endif  // LIB_USE_BUZZER
