#ifndef _BUTTON_H
#define _BUTTON_H

#include "gpio_config.h"

class Button {

private:
    GPIO *gpio;

public:
    Button(GPIO *gpio);

    void init();

    uint8_t read();

};

#endif
