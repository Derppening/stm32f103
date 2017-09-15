#ifndef STM32F103_CORE_SPI_H_
#define STM32F103_CORE_SPI_H_

#include <memory>

#include <stm32f10x_spi.h>

#include "gpio.h"
#include "util.h"

/**
 * @brief Implements an abstraction layer for SPI.
 */
class Spi {
 public:
  /**
   * @brief Configuration for individual SPI.
   */
  struct Config {
    /**
     * @brief SPI Bus
     */
    SPI_TypeDef* spi;
    /**
     * @brief RCC: Reset & Clock Control
     */
    uint32_t rcc;
    /**
     * @brief Serial Clock Pin
     */
    Pin sck;
    /**
     * @brief Master Output -> Slave Input Pin
     */
    Pin miso;
    /**
     * @brief Master Input -> Slave Output Pin
     */
    Pin mosi;
    /**
     * @brief Slave Select Pin
     */
    Pin ss;
  };

  /**
   * @brief Constructor for SPI.
   *
   * @param config SPI Bus configuration
   */
  explicit Spi(const Config& config);

  char Transfer(char byte);

  /**
   * @brief Enables the SPI bus.
   */
  void Enable();
  /**
   * @brief Disables the SPI bus.
   */
  void Disable();

 protected:
  /**
   * @brief Performs initialization for this SPI bus.
   */
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
