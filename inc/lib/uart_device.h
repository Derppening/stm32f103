#ifndef STM32F103_LIB_UART_DEVICE_H_
#define STM32F103_LIB_UART_DEVICE_H_

#include <cstdint>
#include <array>
#include <functional>

#include "uart.h"

class UartDevice {
 public:
  using Listener = std::function<void(const char)>;

  enum Devices {
    kUart1,
    kUart2,
    kUart3,
    kUart4,
    kUart5
  };

  struct Config {
    uint8_t id;

    uint32_t baud_rate = 115200;
  };

  explicit UartDevice(const Config& config);

  void SetListener(Listener&& listener);

  void TxByte(const char byte);
  void Tx(const char* data, ...);
  void Tx(const std::string& s);

  static Listener& InvokeListener(const uint8_t uart_port) { return listeners_.at(uart_port); }

  static bool GetListenerState(const uint8_t uart_port) { return listener_states_.at(uart_port); }

 private:
  static std::array<bool, 5> listener_states_;
  static std::array<std::function<void(const char)>, 5> listeners_;

  uint8_t id_;
  std::unique_ptr<Uart> uart_;
};

bool UartDeviceGetInitState(const uint8_t uart_port);

void UartDeviceTriggerListener(const uint8_t uart_port, const char data);

#endif // STM32F103_LIB_UART_DEVICE_H_
