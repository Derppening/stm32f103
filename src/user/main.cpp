#include "main.h"

int main()
{
	ticks::init();
	COM1.init(9600);
	while (1)
	{
		COM1.tx("%d\n\r", ticks::getTicks());
	}
}
