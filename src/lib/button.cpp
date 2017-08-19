#include "button.h"

Button::Button(GPIO* gpio)
{
	this->gpio = gpio;
}

void Button::init()
{
	this->gpio->init(GPIO_Mode_IPU, GPIO_Speed_50MHz);
}

uint8_t Button::read()
{
	return this->gpio->read();
}
