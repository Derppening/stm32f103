#include "uart.h"

#include <cstdarg>
#include <cstdio>

#include <stm32f10x_conf.h>

Uart::Uart(const Config& config, uint32_t baud_rate) :
    usart_(config.usart),
    rcc_(config.rcc),
    tx_(Gpio(config.tx)),
    rx_(Gpio(config.rx)),
    tx_periph_(config.tx_periph),
    rx_periph_(config.rx_periph),
    irq_(config.irq) {
  Init(baud_rate);
}

void Uart::Init(uint32_t baud_rate) {
  USART_InitTypeDef istruct;

  tx_.Init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz, RCC_APB2Periph_AFIO);
  rx_.Init(GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, RCC_APB2Periph_AFIO);

  if (usart_ == USART1) {
    RCC_APB2PeriphClockCmd(rcc_, ENABLE);
  } else {
    RCC_APB1PeriphClockCmd(rcc_, ENABLE);
  }

  istruct.USART_BaudRate = baud_rate;
  istruct.USART_WordLength = USART_WordLength_8b;
  istruct.USART_StopBits = USART_StopBits_1;
  istruct.USART_Parity = USART_Parity_No;
  istruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  istruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(usart_, &istruct);
  USART_Cmd(usart_, ENABLE);
}

void Uart::EnableInterrupt(Listener&& listener) {
  listener_ = listener;
  USART_ITConfig(usart_, USART_IT_RXNE, ENABLE);

  NVIC_InitTypeDef nstruct;
  nstruct.NVIC_IRQChannel = irq_;
  nstruct.NVIC_IRQChannelPreemptionPriority = 1;
  nstruct.NVIC_IRQChannelSubPriority = 1;
  nstruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nstruct);
}

void Uart::TxByte(const char byte) {
  while (USART_GetFlagStatus(usart_, USART_FLAG_TXE) == RESET) {}
  USART_SendData(usart_, byte);
}

void Uart::Tx(const char* data, ...) {
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

void Uart::Tx(const std::string& str) {
  for (const auto& c : str) {
    TxByte(c);
  }
}
