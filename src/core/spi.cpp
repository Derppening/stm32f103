#include "spi.h"

SPI::SPI(SPI_TypeDef* _SPI_, uint32_t rcc, GPIO* SCK, GPIO* MISO, GPIO* MOSI, GPIO* SS)
{
	this->_SPI_ = _SPI_;
	this->rcc = rcc;
	this->SCK = SCK;
	this->MISO = MISO;
	this->MOSI = MOSI;
	this->SS = SS;
}

void SPI::init()
{
	SPI_InitTypeDef SPI_InitStruct;
	RCC_APB2PeriphClockCmd(this->rcc, ENABLE);
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
    SPI_Init(this->_SPI_, &SPI_InitStruct); 
    SPI_Cmd(this->_SPI_, ENABLE);
	this->SCK->init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	this->MISO->init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	this->MOSI->init(GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	this->SS->init(GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	this->disable();
}

char SPI::transfer(char byte)
{
	this->_SPI_->DR = byte;
	while (!(this->_SPI_->SR & (SPI_I2S_FLAG_TXE)));
	while (!(this->_SPI_->SR & (SPI_I2S_FLAG_RXNE)));
	while (this->_SPI_->SR & (SPI_I2S_FLAG_BSY));
	return this->_SPI_->DR;
}

void SPI::enable()
{
	this->SS->getPort()->BRR = this->SS->getPin();
}

void SPI::disable()
{
	this->SS->getPort()->BSRR = this->SS->getPin();
}
