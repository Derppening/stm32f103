#include "spi.h"

#include <cassert>
#include <stm32f10x_conf.h>

#include "config.h"

Spi::Spi(const Config& config) :
    spi_(config.spi),
    rcc_(config.rcc) {
  assert(spi_ != nullptr);

  Gpio::Config gpio_config;
  gpio_config.speed = GPIO_Speed_50MHz;
  gpio_config.mode = GPIO_Mode_AF_PP;
  gpio_config.pin = config.sck;
  sck_ = std::make_unique<Gpio>(gpio_config);

  gpio_config.pin = config.miso;
  miso_ = std::make_unique<Gpio>(gpio_config);

  gpio_config.pin = config.mosi;
  mosi_ = std::make_unique<Gpio>(gpio_config);

  gpio_config.mode = GPIO_Mode_Out_PP;
  gpio_config.pin = config.ss;
  ss_ = std::make_unique<Gpio>(gpio_config);

  assert(sck_ != nullptr);
  assert(miso_ != nullptr);
  assert(mosi_ != nullptr);
  assert(ss_ != nullptr);

  Init();
}

void Spi::Init() {
  RCC_APB2PeriphClockCmd(rcc_, ENABLE);

  SPI_InitTypeDef istruct;
  istruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  istruct.SPI_CPHA = SPI_CPHA_1Edge;
  istruct.SPI_CPOL = SPI_CPOL_Low;
  istruct.SPI_DataSize = SPI_DataSize_8b;
  istruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  istruct.SPI_FirstBit = SPI_FirstBit_MSB;
  istruct.SPI_Mode = SPI_Mode_Master;
  istruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;

  SPI_Init(spi_, &istruct);
  SPI_Cmd(spi_, ENABLE);
  SPI_CalculateCRC(spi_, DISABLE);
  SPI_SSOutputCmd(spi_, DISABLE);
}

char Spi::Transfer(char byte) {
  spi_->DR = byte;
  while (!(spi_->SR & SPI_I2S_FLAG_TXE) ||
      !(spi_->SR & SPI_I2S_FLAG_RXNE) ||
      (spi_->SR & SPI_I2S_FLAG_BSY)) {}
  return spi_->DR;
}

void Spi::Enable() {
  ss_->GetPort()->BRR = ss_->GetPin();
}

void Spi::Disable() {
  ss_->GetPort()->BSRR = ss_->GetPin();
}
