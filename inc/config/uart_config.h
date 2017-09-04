#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H

#include "uart.h"
#include "gpio_config.h"

extern UART COM1;

extern "C"
{
void USART1_IRQHandler();
}

#endif
