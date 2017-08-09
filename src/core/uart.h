#ifndef _UART_H
#define _UART_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "gpio.h"

class UART
{

	private:
	USART_TypeDef* USART;
	uint32_t rcc;
	GPIO* TX;
	GPIO* RX;
	uint32_t TX_Peripheral;
	uint32_t RX_Peripheral;
	IRQn IRQ;
	void (*listener)(const uint8_t byte);

	public:
	UART(USART_TypeDef* USART, uint32_t rcc, GPIO* TX, GPIO* RX, uint32_t TX_Peripheral, uint32_t RX_Peripheral, IRQn IRQ);
	void init(uint32_t BaudRate);
	void interrupt(void (*callback)(const uint8_t byte));
	void tx_byte(uint8_t byte);
	void tx(const char* data, ...);

};

#endif
