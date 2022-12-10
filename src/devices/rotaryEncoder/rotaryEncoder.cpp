#include "hardware/irq.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "../hardware.h"
#include "rotaryEncoder.h"

int rotaryEncoderRotation = 0;

void encoderCallback(uint gpio, uint32_t events) {
  uint32_t enc_value = (gpio_get_all() >> 27) & 0b011;

  static bool ccw_fall = 0; // bool used when falling edge is triggered
  static bool cw_fall = 0;

  if (gpio == PIN_ENCA) {
    if ((!cw_fall) &&
        (enc_value ==
         0b10)) // cw_fall is set to TRUE when phase A interrupt is triggered
      cw_fall = 1;

    if ((ccw_fall) &&
        (enc_value ==
         0b00)) // if ccw_fall is already set to true from a previous B phase
                // trigger, the ccw event will be triggered
    {
      cw_fall = 0;
      ccw_fall = 0;
      rotaryEncoderRotation -= 1;
    }
  }

  if (gpio == PIN_ENCB) {
    if ((!ccw_fall) && (enc_value == 0b01)) // ccw leading edge is true
      ccw_fall = 1;

    if ((cw_fall) && (enc_value == 0b00)) // cw trigger
    {
      cw_fall = 0;
      ccw_fall = 0;
      rotaryEncoderRotation += 1;
    }
  }
}

void initRotaryEncoder() {
  gpio_init(PIN_ENCA);
  gpio_set_dir(PIN_ENCA, GPIO_IN);
  gpio_pull_up(PIN_ENCA);

  gpio_init(PIN_ENCB);
  gpio_set_dir(PIN_ENCB, GPIO_IN);
  gpio_pull_up(PIN_ENCB);

  gpio_set_irq_enabled_with_callback(PIN_ENCA, GPIO_IRQ_EDGE_FALL, true,
                                     &encoderCallback);
  gpio_set_irq_enabled_with_callback(PIN_ENCB, GPIO_IRQ_EDGE_FALL, true,
                                     &encoderCallback);
}
