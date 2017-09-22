#ifndef STM32F103_LIB_SYSTEM_H_
#define STM32F103_LIB_SYSTEM_H_

#include <cstdint>
#include <memory>

#include "timer_device.h"

/**
 * @brief Implements the system clock.
 */
class System {
 public:
  /**
   * @brief Performs initialization for system clock.
   */
  static void Init();
  /**
   * @brief Retrieves how long the system has been running since power on or reset.
   *
   * @return Current system uptime
   */
  static uint32_t GetMs();

 private:
  /**
   * @brief External listener for ticks counter.
   */
  static void TicksListener();

  /**
   * @brief Counter for system uptime duration.
   */
  static uint32_t counter_;
  /**
   * @brief TimerDevice responsible for system clock.
   */
  static std::unique_ptr<TimerDevice> ticker_;
};

#endif  // STM32F103_LIB_SYSTEM_H_
