#ifndef STM32F103_CORE_UART_H_
#define STM32F103_CORE_UART_H_

#include <functional>
#include <memory>

#include <stm32f10x_usart.h>

#include "gpio.h"
#include "util.h"

/**
 * @brief Implements an abstraction layer for UART interface.
 */
class UART {
 public:
  /**
   * @brief Configuration for individual UART interfaces.
   */
  struct Config {
    /**
     * @brief UART/USART
     */
    USART_TypeDef* usart;
    /**
     * @brief RCC: Reset & Clock Control
     */
    uint32_t rcc;
    /**
     * @brief TX Pin
     */
    Pin tx;
    /**
     * @brief RX Pin
     */
    Pin rx;
    /**
     * @brief TX Peripheral Clock
     */
    uint32_t tx_periph;
    /**
     * @brief RX Peripheral Clock
     */
    uint32_t rx_periph;
    /**
     * @brief Interrupt Handler
     */
    IRQn irq;

    /**
     * @brief Baud Rate
     */
    uint32_t baud_rate;
  };

  /**
   * @brief Constructor for UART
   *
   * @param config UART configuration
   */
  explicit UART(const Config& config);

  /**
   * @brief Enables interrupt for UART RX.
   */
  void EnableInterrupt();

  /**
   * @brief Transmits one byte.
   *
   * @param byte Character to transmit
   */
  void TxByte(const uint8_t byte);
  /**
   * @brief Transmits a formatted string.
   *
   * @param data Formatted string
   * @param ... Variables
   */
  void Tx(const char* data, ...);
  /**
   * @brief Transmits a string.
   *
   * @param str String to transmit
   */
  void Tx(const std::string& str);

 protected:
  /**
   * @brief Performs initialization for this UART interface.
   *
   * @param baud_rate Baud Rate
   */
  void Init(uint32_t baud_rate);

 private:
  USART_TypeDef* usart_;
  uint32_t rcc_;
  std::unique_ptr<GPIO> tx_ = nullptr;
  std::unique_ptr<GPIO> rx_ = nullptr;
  uint32_t tx_periph_;
  uint32_t rx_periph_;
  IRQn irq_;
};

#endif  // STM32F103_CORE_UART_H_
