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
	BUTTON1.init();
	BUTTON2.init();
	BUTTON3.init();
	LEDa.init();
	LEDb.init();
	LEDc.init();
	while (1)
	{
		COM1.tx("%d\n\r", ticks::get());
	}
}
