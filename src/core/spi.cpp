#include "spi.h"

#include <cassert>
#include <stm32f10x_conf.h>

#include "config.h"

Spi::Spi(const Config& deps) :
    spi_(deps.spi),
    rcc_(deps.rcc),
    sck_(deps.sck),
    miso_(deps.miso),
    mosi_(deps.mosi),
    ss_(deps.ss) {
  assert(spi_ != nullptr);
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

  sck_.Init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
  miso_.Init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
  mosi_.Init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
  ss_.Init(GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

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
  ss_.GetPort()->BRR = ss_.GetPin();
}

void Spi::Disable() {
  ss_.GetPort()->BSRR = ss_.GetPin();
}
