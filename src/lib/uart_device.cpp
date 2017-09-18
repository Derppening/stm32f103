#include "config.h"

#ifdef LIB_USE_UART

#include <cassert>
#include <cstdarg>

#include "uart_device.h"
#include "util.h"

std::array<bool, 5> UartDevice::listener_states_ = {};
std::array<UartDevice::Listener, 5> UartDevice::listeners_ = {nullptr};

/**
 * @brief USART1 Handler
 */
extern "C" void USART1_IRQHandler();
/**
 * @brief USART2 Handler
 */
extern "C" void USART2_IRQHandler();
/**
 * @brief USART3 Handler
 */
extern "C" void USART3_IRQHandler();
/**
 * @brief UART4 Handler
 */
extern "C" void USART4_IRQHandler();
/**
 * @brief UART5 Handler
 */
extern "C" void USART5_IRQHandler();

namespace {
/**
 * @param id ID of UART we are using
 * @return @c Uart::Config object of our UART object
 */
inline UART::Config GetUartConfig(const uint8_t id) {
  assert_param(id < LIB_USE_UART);

  UART::Config uart_config;
  switch (id) {
    default:
      assert(false);
      [[fallthrough]];
    case 0:
#if LIB_USE_UART > 0
      uart_config.usart = USART1;
      uart_config.rcc = RCC_APB2Periph_USART1;
      uart_config.tx = {GPIOA, GPIO_Pin_9};
      uart_config.rx = {GPIOA, GPIO_Pin_10};
      uart_config.tx_periph = RCC_APB2Periph_GPIOA;
      uart_config.rx_periph = RCC_APB2Periph_GPIOA;
      uart_config.irq = USART1_IRQn;
      break;
#endif  // LIB_USE_UART > 0
  }

  return uart_config;
}
}  // namespace

extern "C" void USART1_IRQHandler() {
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    auto data = static_cast<char>(USART_ReceiveData(USART1));

    if (UartDeviceGetInitState(UartDevice::kUart1)) {
      UartDeviceTriggerListener(UartDevice::kUart1, data);
    }

    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
}

extern "C" void USART2_IRQHandler() {
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
    auto data = static_cast<char>(USART_ReceiveData(USART2));

    if (UartDeviceGetInitState(UartDevice::kUart2)) {
      UartDeviceTriggerListener(UartDevice::kUart2, data);
    }

    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}

extern "C" void USART3_IRQHandler() {
  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
    auto data = static_cast<char>(USART_ReceiveData(USART3));

    if (UartDeviceGetInitState(UartDevice::kUart3)) {
      UartDeviceTriggerListener(UartDevice::kUart3, data);
    }

    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
}

extern "C" void USART4_IRQHandler() {
  if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) {
    auto data = static_cast<char>(USART_ReceiveData(UART4));

    if (UartDeviceGetInitState(UartDevice::kUart4)) {
      UartDeviceTriggerListener(UartDevice::kUart4, data);
    }

    USART_ClearITPendingBit(UART4, USART_IT_RXNE);
  }
}

extern "C" void USART5_IRQHandler() {
  if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
    auto data = static_cast<char>(USART_ReceiveData(UART5));

    if (UartDeviceGetInitState(UartDevice::kUart5)) {
      UartDeviceTriggerListener(UartDevice::kUart5, data);
    }

    USART_ClearITPendingBit(UART5, USART_IT_RXNE);
  }
}

bool UartDeviceGetInitState(const uint8_t uart_port) { return UartDevice::GetListenerState(uart_port); }

void UartDeviceTriggerListener(const uint8_t uart_port, const char data) {
  auto listener = UartDevice::InvokeListener(uart_port);
  if (listener) {
    listener(data);
  }
}

UartDevice::UartDevice(const Config& config) :
    id_(config.id) {
  auto uart_config = GetUartConfig(id_);
  uart_config.baud_rate = config.baud_rate;

  uart_ = std::make_unique<UART>(uart_config);
}

void UartDevice::SetListener(Listener&& listener) {
  listeners_.at(id_) = listener;
  listener_states_.at(id_) = true;

  uart_->EnableInterrupt();
}

void UartDevice::Tx(const std::string& s) {
  uart_->Tx(s);
}

void UartDevice::Tx(const char* data, ...) {
  va_list args;
  va_start(args, data);
  uart_->Tx(data, args);
  va_end(args);
}

void UartDevice::TxByte(const uint8_t byte) {
  uart_->TxByte(byte);
}

#endif  // LIB_USE_UART
