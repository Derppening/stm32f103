#include "led.h"

LED::LED(GPIO* gpio)
{
	this->gpio = gpio;
}

void LED::init()
{
	this->gpio->init(GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	this->gpio->reset();
}

void LED::on()
{
	this->gpio->set();
}

void LED::off()
{
	this->gpio->reset();
}

void LED::toggle()
{
	this->gpio->toggle();
}
