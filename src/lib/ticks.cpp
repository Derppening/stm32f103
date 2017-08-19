#include "ticks.h"

uint32_t counter;

void ticks::init()
{
	CLK2.init(71, 1000);
	CLK2.interrupt(&ticks::handler);
}

uint32_t ticks::get()
{
	return counter;
}

void ticks::handler()
{
	counter++;
}
