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
	void init(GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed);
	void rcc(FunctionalState state);
	void write(BitAction BitVal);
	uint8_t read();
	uint16_t getPinSource();

};

#endif
