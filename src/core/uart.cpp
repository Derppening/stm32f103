#include "uart.h"

#include <cassert>
#include <cstdarg>
#include <cstdio>

#include <stm32f10x_conf.h>

UART::UART(const Config& config) :
    usart_(config.usart),
    rcc_(config.rcc),
    tx_periph_(config.tx_periph),
    rx_periph_(config.rx_periph),
    irq_(config.irq) {
  // idiot-proof check
  assert(usart_ != nullptr);

  // TX
  GPIO::Config gpio_config;
  gpio_config.speed = GPIO_Speed_50MHz;
  gpio_config.rcc = RCC_APB2Periph_AFIO;
  gpio_config.mode = GPIO_Mode_AF_PP;
  gpio_config.pin = config.tx;
  tx_ = std::make_unique<GPIO>(gpio_config);

  // RX
  gpio_config.mode = GPIO_Mode_IN_FLOATING;
  gpio_config.pin = config.rx;
  rx_ = std::make_unique<GPIO>(gpio_config);

  // make sure everything is ok before proceeding
  assert(tx_ != nullptr);
  assert(rx_ != nullptr);

  Init(config.baud_rate);
}

void UART::Init(uint32_t baud_rate) {
  // enable the RCC the UART uses
  if (usart_ == USART1) {
    RCC_APB2PeriphClockCmd(rcc_, ENABLE);
  } else {
    RCC_APB1PeriphClockCmd(rcc_, ENABLE);
  }

  // setup the USART_InitStruct
  USART_InitTypeDef istruct;
  istruct.USART_BaudRate = baud_rate;
  istruct.USART_WordLength = USART_WordLength_8b;
  istruct.USART_StopBits = USART_StopBits_1;
  istruct.USART_Parity = USART_Parity_No;
  istruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  istruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  // initialize the UART interface
  USART_Init(usart_, &istruct);
  USART_Cmd(usart_, ENABLE);
}

void UART::EnableInterrupt() {
  // enable the interrupt
  USART_ITConfig(usart_, USART_IT_RXNE, ENABLE);

  // setup the NVIC_InitStruct
  NVIC_InitTypeDef nstruct;
  nstruct.NVIC_IRQChannel = irq_;
  nstruct.NVIC_IRQChannelPreemptionPriority = 1;
  nstruct.NVIC_IRQChannelSubPriority = 1;
  nstruct.NVIC_IRQChannelCmd = ENABLE;

  // initialize the NVIC for our UART
  NVIC_Init(&nstruct);
}

void UART::TxByte(const uint8_t byte) {
  while (USART_GetFlagStatus(usart_, USART_FLAG_TXE) == RESET) {}
  USART_SendData(usart_, byte);
}

void UART::Tx(const char* data, ...) {
  va_list args;
  char buffer[256];
  char* ptr = buffer;

  va_start(args, data);
  std::vsprintf(buffer, data, args);
  va_end(args);

  while (*ptr != '\0') {
    TxByte(*ptr);
    ptr++;
  }
}

void UART::Tx(const std::string& str) {
  for (const auto& c : str) {
    TxByte(c);
  }
}
