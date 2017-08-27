#include "main.h"

void COM1_interrupt_func(const char byte)
{
	COM1.tx("byte: %c\n\r", byte);
}

int main()
{
	ticks::init();
	COM1.init(9600);
	COM1.interrupt(&COM1_interrupt_func);
	LEDa.init();
	LEDb.init();
	LEDc.init();
	BUTTON1.init();
	BUTTON2.init();
	BUTTON3.init();
	while (1)
	{
		COM1.tx("%d: %d %d %d\n\r", ticks::get(), BUTTON1.read(), BUTTON2.read(), BUTTON3.read());
		if (BUTTON1.read())
		{
			LEDa.on();
		}
		else
		{
			LEDa.off();
		}
		if (BUTTON2.read())
		{
			LEDb.on();
		}
		else
		{
			LEDb.off();
		}
		if (BUTTON3.read())
		{
			LEDc.on();
		}
		else
		{
			LEDc.off();
		}
	}
}
