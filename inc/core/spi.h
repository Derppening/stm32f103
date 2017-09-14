#ifndef STM32F103_CORE_SPI_H_
#define STM32F103_CORE_SPI_H_

#include <memory>

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

 protected:
  void Init();

 private:
  SPI_TypeDef* spi_;
  uint32_t rcc_;
  std::unique_ptr<Gpio> sck_ = nullptr;
  std::unique_ptr<Gpio> miso_ = nullptr;
  std::unique_ptr<Gpio> mosi_ = nullptr;
  std::unique_ptr<Gpio> ss_ = nullptr;
};

#endif  // STM32F103_CORE_SPI_H_
