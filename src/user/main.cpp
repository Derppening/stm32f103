#include "main.h"

int main()
{
	COM1.init(9600);
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
