#ifndef STM32F103_LIB_UART_DEVICE_H_
#define STM32F103_LIB_UART_DEVICE_H_

#include <cstdint>
#include <array>
#include <functional>

#include "config.h"
#include "uart.h"

#if !defined(LIB_USE_UART) || LIB_USE_UART < 1
#error "This configuration is not specified to use this library"
#endif  // !defined(LIB_USE_UART) || LIB_USE_UART < 1

/**
 * @brief Implements device-level abstraction for UART devices.
 */
class UartDevice {
 public:
  /**
   * @brief UART RX Listener type definition.
   */
  using Listener = std::function<void(const uint8_t)>;

  /**
   * @brief UART devices enumeration.
   */
  enum Devices {
    kUart1,
    kUart2,
    kUart3,
    kUart4,
    kUart5
  };

  /**
   * @brief Configuration for UART device.
   */
  struct Config {
    /**
     * @brief UART device ID.
     */
    uint8_t id;

    /**
     * @brief UART baud rate.
     */
    uint32_t baud_rate = 115200;
  };

  /**
   * @brief Constructor for UART device.
   *
   * @param config UART device configuration. See UartDevice#Config.
   */
  explicit UartDevice(const Config& config);

  /**
   * @brief Sets and enables RX listener for this device.
   *
   * @param listener External listener function to trigger.
   */
  void SetListener(Listener&& listener);

  /**
   * @brief Transmites one byte.
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
   * @param s String to transmit
   */
  void Tx(const std::string& s);

  /**
   * @brief Invokes the external listener.
   *
   * @param uart_port UART Port ID
   * @return External listener corresponding to the UART port
   */
  static Listener& InvokeListener(const uint8_t uart_port) { return listeners_[uart_port]; }

 private:
  /**
   * @brief Array of function pointers to external listeners.
   */
  static std::array<std::function<void(const uint8_t)>, 5> listeners_;

  /**
   * @brief ID of currently managed device
   */
  uint8_t device_id_;
  /**
   * @brief Pointer to underlying UART object
   */
  std::unique_ptr<UART> uart_;
};

/**
 * @brief Bridging function between IRQ Handler and external user-defined listener.
 *
 * @param uart_port UART Port triggered
 * @param data Data sent to @p uart_port
 */
void UartDeviceTriggerListener(const uint8_t uart_port, const char data);

#endif // STM32F103_LIB_UART_DEVICE_H_
