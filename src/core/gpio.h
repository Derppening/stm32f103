#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

class GPIO
{

	private:
	GPIO_TypeDef* Port;
	GPIO_InitTypeDef GPIO_InitStructure;

	public:
	GPIO(GPIO_TypeDef* Port, uint16_t Pin);
	void init(GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed, uint32_t rcc = 0);
	void rcc(FunctionalState state, uint32_t rcc = 0);
	void set();
	void reset();
	void write(BitAction BitVal);
	uint8_t read();
	uint16_t getPinSource();

};

#endif
