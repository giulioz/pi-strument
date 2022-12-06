#include <stdio.h>

#include "config.h"
#include "devices/audio_pio.h"

int main() {
  pio_init();

  gpio_init(PIN_B1);
  gpio_init(PIN_B2);
  gpio_pull_up(PIN_B1);
  gpio_pull_up(PIN_B2);
  gpio_set_dir(PIN_B1, GPIO_IN);
  gpio_set_dir(PIN_B2, GPIO_IN);

  int32_t *samples = (int32_t *)data_treating(sine_wave_table, 256);
  int32_t *samples1 = NULL;

  while (true) {
    bool b1Value = gpio_get(PIN_B1);
    bool b2Value = gpio_get(PIN_B2);

    // for (int i = 20; i < 100; i = i + 20) {
    //   sleep_ms(1000);
    //   samples1 = (int32_t *)Volume_32((int16_t *)samples, 256, i);
    //   Happy_birthday_out(samples1);
    //   free_32(samples1);
    // }
  }

  return 0;
}
