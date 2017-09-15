#ifndef STM32F103_CORE_UART_H_
#define STM32F103_CORE_UART_H_

#include <functional>
#include <memory>

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

    uint32_t baud_rate;
  };

  explicit Uart(const Config& config);

  void EnableInterrupt();

  void TxByte(const char byte);
  void Tx(const char* data, ...);
  void Tx(const std::string& str);

 protected:
  void Init(uint32_t baud_rate);

 private:
  USART_TypeDef* usart_;
  uint32_t rcc_;
  std::unique_ptr<Gpio> tx_ = nullptr;
  std::unique_ptr<Gpio> rx_ = nullptr;
  uint32_t tx_periph_;
  uint32_t rx_periph_;
  IRQn irq_;
};

#endif  // STM32F103_CORE_UART_H_
