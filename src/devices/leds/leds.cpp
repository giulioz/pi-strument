#include "leds.h"
#include "../hardware.h"
#include "pico/stdlib.h"

void initLEDS() {
  spi_init(PIN_LED_SPI, LED_BAUDRATE);
  spi_set_format(PIN_LED_SPI, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);

  gpio_init(PIN_LED_SCK);
  gpio_init(PIN_LED_TX);
  gpio_init(PIN_LED_LATCH);
  gpio_init(PIN_LED8);

  gpio_set_dir(PIN_LED_SCK, GPIO_OUT);
  gpio_set_dir(PIN_LED_TX, GPIO_OUT);
  gpio_set_dir(PIN_LED_LATCH, GPIO_OUT);
  gpio_set_dir(PIN_LED8, GPIO_OUT);

  gpio_set_function(PIN_LED_SCK, GPIO_FUNC_SPI);
  gpio_set_function(PIN_LED_TX, GPIO_FUNC_SPI);
}

void setLEDS(uint16_t state) {
  gpio_put(PIN_LED8, state >> 8);

  unsigned char data = state & 0xFF;
  spi_write_blocking(PIN_LED_SPI, &data, 1);
  gpio_put(PIN_LED_LATCH, 1);
  sleep_us(LED_LATCH_DELAY_US);
  gpio_put(PIN_LED_LATCH, 0);
}
