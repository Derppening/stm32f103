#ifndef _TICKS_H
#define _TICKS_H

#include "timer_config.h"

namespace ticks {
    void init();

    uint32_t get();

    void handler();
}

#endif
