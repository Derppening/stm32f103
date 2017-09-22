#ifndef STM32F103_LIB_TIMER_DEVICE_H_
#define STM32F103_LIB_TIMER_DEVICE_H_

#include <cstdint>
#include <memory>

#include "timer.h"

/**
 * @brief Implements device-level abstraction for TIM deivces.
 *
 * As opposed to Timer, this class is designed to be a higher-level abstraction, and includes the ability to manage
 * listeners for each TIM device.
 */
class TimerDevice {
 public:
  /**
   * @brief TIM Listener type definition.
   */
  using Listener = std::function<void()>;

  /**
   * @brief TIM devices enumeration.
   */
  enum Timers {
    /**
     * @brief TIM1
     */
    kTim1,
    /**
     * @brief TIM2
     */
    kTim2,
    /**
     * @brief TIM3
     */
    kTim3,
    /**
     * @brief TIM4
     */
    kTim4,
    /**
     * @brief TIM5
     */
    kTim5,
    /**
     * @brief TIM6
     */
    kTim6,
    /**
     * @brief TIM7
     */
    kTim7
  };

  /**
   * @brief Configuration for TIM device.
   */
  struct Config {
    /**
     * @brief Timer
     */
    TIM_TypeDef* tim;
    /**
     * @brief RCC: Reset & Clock Control
     */
    uint32_t rcc;
    /**
     * @brief Interrupt Handler
     */
    IRQn irqn;

    /**
     * @brief Prescaler value.
     */
    uint16_t prescaler;
    /**
     * @brief Period value.
     */
    uint16_t period;

    /**
     * @brief Which timer to use.
     *
     * @see TimerDevice#Timers
     */
    Timers timer;
  };

  /**
   * @brief Constructor for Timer Device.
   * @param config Timer device configuration. See TimerDevice#Config.
   */
  explicit TimerDevice(const Config& config);

  /**
   * @brief Sets and enables listener for this device.
   *
   * Timer listeners should have function prototype of @c void().
   *
   * @param listener External listener function to trigger.
   */
  void SetListener(Listener&& listener);

  /**
   * @brief Invokes the external listener.
   *
   * @param tim_device TIM device enumeration
   * @return External listener corresponding to the TIM device
   */
  static Listener& InvokeListener(const Timers tim_device) { return listeners_[tim_device]; }

 private:
  /**
   * @brief Array of function pointers to external listeners.
   */
  static std::array<std::function<void()>, 7> listeners_;

  /**
   * @brief ID of currently managed device
   */
  Timers timer_id_;
  /**
   * @brief Pointer to underlying Timer object
   */
  std::unique_ptr<Timer> timer_;
};

/**
 * @brief Bridging fuinction between IRQ Handler and external user-defined listener.
 *
 * @param tim_device TIM device triggered
 */
void TimerDeviceTriggerListener(const TimerDevice::Timers tim_device);

#endif  // STM32F103_LIB_TIMER_DEVICE_H_
