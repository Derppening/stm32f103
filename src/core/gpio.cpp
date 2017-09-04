#include "gpio.h"

GPIO::GPIO(GPIO_TypeDef *Port, uint16_t Pin) {
    this->Port = Port;
    GPIO_StructInit(&(this->GPIO_InitStructure));
    this->GPIO_InitStructure.GPIO_Pin = Pin;
}

void GPIO::init(GPIOMode_TypeDef Mode, GPIOSpeed_TypeDef Speed, uint32_t rcc) {
    this->rcc(ENABLE, rcc);
    this->GPIO_InitStructure.GPIO_Mode = Mode;
    this->GPIO_InitStructure.GPIO_Speed = Speed;
    GPIO_Init(this->Port, &(this->GPIO_InitStructure));
}

void GPIO::rcc(FunctionalState state, uint32_t rcc) {
    if (this->Port == GPIOA) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | rcc, state);
    } else if (this->Port == GPIOB) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | rcc, state);
    } else if (this->Port == GPIOC) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | rcc, state);
    } else if (this->Port == GPIOD) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | rcc, state);
    } else if (this->Port == GPIOE) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | rcc, state);
    } else if (this->Port == GPIOF) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | rcc, state);
    } else if (this->Port == GPIOG) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG | rcc, state);
    }
}

void GPIO::set() {
    GPIO_SetBits(this->Port, this->GPIO_InitStructure.GPIO_Pin);
}

void GPIO::reset() {
    GPIO_ResetBits(this->Port, this->GPIO_InitStructure.GPIO_Pin);
}

void GPIO::toggle() {
    this->write(!this->read());
}

void GPIO::write(bool state) {
    if (state) {
        GPIO_WriteBit(this->Port, this->GPIO_InitStructure.GPIO_Pin, Bit_SET);
    } else {
        GPIO_WriteBit(this->Port, this->GPIO_InitStructure.GPIO_Pin, Bit_RESET);
    }
}

uint8_t GPIO::read() {
    return GPIO_ReadInputDataBit(this->Port, this->GPIO_InitStructure.GPIO_Pin);
}

uint16_t GPIO::getPinSource() {
    switch (this->GPIO_InitStructure.GPIO_Pin) {
        case GPIO_Pin_0:
            return GPIO_PinSource0;
        case GPIO_Pin_1:
            return GPIO_PinSource1;
        case GPIO_Pin_2:
            return GPIO_PinSource2;
        case GPIO_Pin_3:
            return GPIO_PinSource3;
        case GPIO_Pin_4:
            return GPIO_PinSource4;
        case GPIO_Pin_5:
            return GPIO_PinSource5;
        case GPIO_Pin_6:
            return GPIO_PinSource6;
        case GPIO_Pin_7:
            return GPIO_PinSource7;
        case GPIO_Pin_8:
            return GPIO_PinSource8;
        case GPIO_Pin_9:
            return GPIO_PinSource9;
        case GPIO_Pin_10:
            return GPIO_PinSource10;
        case GPIO_Pin_11:
            return GPIO_PinSource11;
        case GPIO_Pin_12:
            return GPIO_PinSource12;
        case GPIO_Pin_13:
            return GPIO_PinSource13;
        case GPIO_Pin_14:
            return GPIO_PinSource14;
        case GPIO_Pin_15:
            return GPIO_PinSource15;
    }
    return 0;
}

GPIO_TypeDef *GPIO::getPort() {
    return this->Port;
}

uint16_t GPIO::getPin() {
    return this->GPIO_InitStructure.GPIO_Pin;
}
