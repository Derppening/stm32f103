#include "main.h"

void COM1_interrupt_func(const char byte)
{
	COM1.tx("WTF\n\r");
}

int main()
{
	COM1.init(9600);
	COM1.interrupt(&COM1_interrupt_func);
	LED_A.init();
	LED_B.init();
	LED_C.init();
	while (1)
	{
		LED_A.on();
		LED_B.on();
		LED_C.on();
		COM1.tx("Hello World!\n\r");
	}
}
