#ifndef _TICKS_H
#define _TICKS_H

#include "stm32f10x_tim.h"

namespace ticks
{

	void init();
	uint32_t getTicks();

};

#endif
