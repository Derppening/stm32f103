#include "led.h"

LED::LED(GPIO* gpio)
{
	this->gpio = gpio;
}

void LED::init()
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	this->gpio->init(GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}

void LED::on()
{
	this->gpio->set();
}

void LED::off()
{
	this->gpio->reset();
}
