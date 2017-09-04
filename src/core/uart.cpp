#include "uart.h"

UART::UART(USART_TypeDef *USART, uint32_t rcc, GPIO *TX, GPIO *RX, uint32_t TX_Peripheral, uint32_t RX_Peripheral,
           IRQn IRQ) {
    this->USART = USART;
    this->rcc = rcc;
    this->TX = TX;
    this->RX = RX;
    this->TX_Peripheral = TX_Peripheral;
    this->RX_Peripheral = RX_Peripheral;
    this->IRQ = IRQ;
    this->listener = 0;
}

void UART::init(uint32_t BaudRate) {
    USART_InitTypeDef USART_InitStructure;
    this->TX->init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz, RCC_APB2Periph_AFIO);
    this->RX->init(GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, RCC_APB2Periph_AFIO);
    if (this->USART == USART1) {
        RCC_APB2PeriphClockCmd(this->rcc, ENABLE);
    } else {
        RCC_APB1PeriphClockCmd(this->rcc, ENABLE);
    }
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(this->USART, &USART_InitStructure);
    USART_Cmd(this->USART, ENABLE);
}

void UART::interrupt(void (*callback)(const char byte)) {
    NVIC_InitTypeDef NVIC_InitStructure;
    this->listener = callback;
    USART_ITConfig(this->USART, USART_IT_RXNE, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = this->IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void UART::tx_byte(char byte) {
    while (USART_GetFlagStatus(this->USART, USART_FLAG_TXE) == RESET);
    USART_SendData(this->USART, byte);
}

void UART::tx(const char *data, ...) {
    va_list args;
    char buffer[256];
    char *ptr = buffer;
    va_start(args, data);
    vsprintf(buffer, data, args);
    va_end(args);
    while (*ptr != '\0') {
        this->tx_byte(*ptr);
        ptr++;
    }
}
