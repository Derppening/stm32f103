#ifndef STM32F103_CORE_SPI_H_
#define STM32F103_CORE_SPI_H_

#include <stm32f10x_spi.h>

#include "gpio.h"
#include "util.h"

class Spi {
 public:
  struct Config {
    SPI_TypeDef* spi;
    uint32_t rcc;
    Pin sck;
    Pin miso;
    Pin mosi;
    Pin ss;
  };

  explicit Spi(const Config& config);

  char Transfer(char byte);

  void Enable();
  void Disable();

 private:
  void Init();

  SPI_TypeDef* spi_;
  uint32_t rcc_;
  Gpio sck_;
  Gpio miso_;
  Gpio mosi_;
  Gpio ss_;
};

#endif  // STM32F103_CORE_SPI_H_
