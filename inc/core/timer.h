#ifndef STM32F103_CORE_TIMER_H_
#define STM32F103_CORE_TIMER_H_

#include <functional>

#include <misc.h>
#include <stm32f10x_tim.h>

/**
 * @brief Implements an abstraction layer for TIM.
 *
 * @note TIM is love, TIM is life.
 */
class Timer {
 public:
  /**
   * @brief Timer Listener type definition.
   */
  using Listener = std::function<void()>;

  /**
   * @brief Configuration for an individual TIM.
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
  };

  /**
   * @brief Constructor for Timer.
   *
   * @param config TIM configuration
   */
  explicit Timer(const Config& config);

  /**
   * @brief Setups interrupt handling for this timer.
   *
   * @note A replacement will soon be available in @c Ticks class.
   *
   * @param listener External listener function to trigger
   */
  void SetInterrupt(Listener&& listener);

 protected:
  /**
   * @brief Performs initialization for this TIM.
   *
   * @param prescaler
   * @param period
   */
  void Init(uint16_t prescaler, uint16_t period);

 private:
  /**
   * @brief TIM Listener.
   */
  Listener listener_ = nullptr;

  TIM_TypeDef* tim_ = nullptr;
  uint32_t rcc_;
  IRQn irq_;
};

#endif  // STM32F103_CORE_TIMER_H_
