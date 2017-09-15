#ifndef STM32F103_CORE_UTIL_H_
#define STM32F103_CORE_UTIL_H_

#include <cstdint>
#include <utility>
#include <stm32f10x_gpio.h>

/**
 * @brief Type definition for all pins.
 */
using Pin = std::pair<GPIO_TypeDef*, uint16_t>;

#endif  // STM32F103_CORE_UTIL_H_
