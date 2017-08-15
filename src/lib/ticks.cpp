#include "ticks.h"

uint32_t counter;

void handler()
{
	counter++;
}

void ticks::init()
{
	counter = 0;
	CLK2.init(71, 1000);
	CLK2.interrupt(&handler);
}

uint32_t ticks::getTicks()
{
	return counter;
}
