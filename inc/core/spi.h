#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "gpio_config.h"
#include <stm32f10x_spi.h>

class SPI {

private:
    SPI_TypeDef *_SPI_;
    uint32_t rcc;
    GPIO *SCK;
    GPIO *MISO;
    GPIO *MOSI;
    GPIO *SS;

public:
    SPI(SPI_TypeDef *_SPI_, uint32_t rcc, GPIO *SCK, GPIO *MISO, GPIO *MOSI, GPIO *SS);

    void init();

    char transfer(char byte);

    void enable();

    void disable();

};

#endif
