#ifndef STM32F103_CONFIG_CONFIG_H_
#define STM32F103_CONFIG_CONFIG_H_

#if defined(TEST_CONFIG)
#include "test_config.h"
#elif defined(DEV_BOARD)
#include "dev_board.h"
#else
#error "Configuration not specified"
#endif

#endif  // STM32F103_CONFIG_CONFIG_H_
