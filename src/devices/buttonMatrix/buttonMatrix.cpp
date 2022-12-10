#include "buttonMatrix.h"
#include "../hardware.h"
#include "pico/stdlib.h"

ButtonMatrixState buttonMatrixState;

void initButtonMatrix() {
  gpio_init(PIN_B0);
  gpio_init(PIN_B1);
  gpio_init(PIN_B2);
  gpio_init(PIN_B3);
  gpio_init(PIN_B4);
  gpio_init(PIN_B5);
  gpio_init(PIN_B6);
  gpio_init(PIN_B7);
  gpio_init(PIN_B8);
  gpio_init(PIN_ENCBtn);

  gpio_set_dir(PIN_B0, GPIO_IN);
  gpio_set_dir(PIN_B1, GPIO_IN);
  gpio_set_dir(PIN_B2, GPIO_IN);
  gpio_set_dir(PIN_B3, GPIO_IN);
  gpio_set_dir(PIN_B4, GPIO_IN);
  gpio_set_dir(PIN_B5, GPIO_IN);
  gpio_set_dir(PIN_B6, GPIO_IN);
  gpio_set_dir(PIN_B7, GPIO_IN);
  gpio_set_dir(PIN_B8, GPIO_IN);
  gpio_set_dir(PIN_ENCBtn, GPIO_IN);

  gpio_pull_up(PIN_B0);
  gpio_pull_up(PIN_B1);
  gpio_pull_up(PIN_B2);
  gpio_pull_up(PIN_B3);
  gpio_pull_up(PIN_B4);
  gpio_pull_up(PIN_B5);
  gpio_pull_up(PIN_B6);
  gpio_pull_up(PIN_B7);
  gpio_pull_up(PIN_B8);
  gpio_pull_up(PIN_ENCBtn);
}

void getButtonMatrix() {
  buttonMatrixState.B0 = !gpio_get(PIN_B0);
  buttonMatrixState.B1 = !gpio_get(PIN_B1);
  buttonMatrixState.B2 = !gpio_get(PIN_B2);
  buttonMatrixState.B3 = !gpio_get(PIN_B3);
  buttonMatrixState.B4 = !gpio_get(PIN_B4);
  buttonMatrixState.B5 = !gpio_get(PIN_B5);
  buttonMatrixState.B6 = !gpio_get(PIN_B6);
  buttonMatrixState.B7 = !gpio_get(PIN_B7);
  buttonMatrixState.B8 = !gpio_get(PIN_B8);
  buttonMatrixState.ENCBtn = !gpio_get(PIN_ENCBtn);
}
