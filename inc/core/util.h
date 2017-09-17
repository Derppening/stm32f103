#ifndef STM32F103_CORE_UTIL_H_
#define STM32F103_CORE_UTIL_H_

#include <cstdint>
#include <utility>
#include <stm32f10x_gpio.h>

/**
 * @brief Type definition for a single pin
 * @details You can initialize a pin using `
 * ```
 * Pin myPin{ GPIOA, GPIO_Pin_1 }
 * ```
 * For more pin definitions you may refer to stm32f10x_gpio.h
 */
using Pin = std::pair<GPIO_TypeDef*, uint16_t>;

#endif  // STM32F103_CORE_UTIL_H_
