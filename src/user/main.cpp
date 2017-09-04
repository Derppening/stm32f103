#include "main.h"

void COM1_interrupt_func(const char byte)
{
	COM1.tx("byte: %c\n\r", byte);
}

int main()
{
	//ticks::init();
	//COM1.init(9600);
	//COM1.interrupt(&COM1_interrupt_func);
//	LEDa.init();
//	LEDb.init();
//	LEDc.init();
//	BUTTON1.init();
//	BUTTON2.init();
//	BUTTON3.init();
    LED LEDa(&PA15);
    LEDa.init();
	while (1)
	{
        LEDa.on();
//        COM1.tx("lololol\r\n");
		//COM1.tx("%d: %d %d %d\n\r", ticks::get(), BUTTON1.read(), BUTTON2.read(), BUTTON3.read());
//		LEDa.set(BUTTON1.read());
//		LEDb.set(BUTTON2.read());
//		LEDc.set(BUTTON3.read());
	}
}
