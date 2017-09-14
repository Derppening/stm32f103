#ifndef STM32F103_CORE_UART_H_
#define STM32F103_CORE_UART_H_

#include <functional>
#include <stm32f10x_usart.h>

#include "gpio.h"
#include "util.h"

class Uart {
 public:
  using Listener = std::function<void(const char)>;

  struct Config {
    USART_TypeDef* usart;
    uint32_t rcc;
    Pin tx;
    Pin rx;
    uint32_t tx_periph;
    uint32_t rx_periph;
    IRQn irq;
  };

  Uart(const Config& config, uint32_t baud_rate);

  void EnableInterrupt(Listener&& listener);

  void TxByte(const char byte);
  void Tx(const char* data, ...);
  void Tx(const std::string& str);

 private:
  void Init(uint32_t baud_rate);

  Listener listener_ = nullptr;

  USART_TypeDef* usart_;
  uint32_t rcc_;
  Gpio tx_;
  Gpio rx_;
  uint32_t tx_periph_;
  uint32_t rx_periph_;
  IRQn irq_;
};

#endif  // STM32F103_CORE_UART_H_
