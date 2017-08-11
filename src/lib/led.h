#ifndef _LED_H
#define _LED_H

#include "gpio_config.h"

class LED
{

	private:
	GPIO* gpio;

	public:
	LED(GPIO* gpio);
	void init();
	void on();
	void off();

};

#endif
