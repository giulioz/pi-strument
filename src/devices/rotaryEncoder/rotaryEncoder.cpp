#include "hardware/irq.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "../hardware.h"
#include "pio_rotary_encoder.pio.h"
#include "rotaryEncoder.h"

int rotaryEncoderRotation = 0;

void rotaryEncoder_pio_irq_handler() {
  // test if irq 0 was raised
  if (pio1_hw->irq & 1) {
    rotaryEncoderRotation = rotaryEncoderRotation + 1;
  }
  // test if irq 1 was raised
  if (pio1_hw->irq & 2) {
    rotaryEncoderRotation = rotaryEncoderRotation - 1;
  }
  // clear both interrupts
  pio1_hw->irq = 3;
}

void initRotaryEncoder() {
  PIO pio = pio1;
  uint8_t sm = 1;

  // configure the used pins as input with pull up
  pio_gpio_init(pio, PIN_ENCA);
  gpio_set_pulls(PIN_ENCA, true, false);
  pio_gpio_init(pio, PIN_ENCB);
  gpio_set_pulls(PIN_ENCB, true, false);
  // load the pio program into the pio memory
  uint offset = pio_add_program(pio, &pio_rotary_encoder_program);
  // make a sm config
  pio_sm_config c = pio_rotary_encoder_program_get_default_config(offset);
  // set the 'in' pins
  sm_config_set_in_pins(&c, PIN_ENCA);
  // set shift to left: bits shifted by 'in' enter at the least
  // significant bit (LSB), no autopush
  sm_config_set_in_shift(&c, false, false, 0);
  // set the IRQ handler
  irq_set_exclusive_handler(PIO1_IRQ_0, rotaryEncoder_pio_irq_handler);
  // enable the IRQ
  irq_set_enabled(PIO1_IRQ_0, true);
  pio1_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;
  // init the sm.
  // Note: the program starts after the jump table -> initial_pc = 16
  pio_sm_init(pio, sm, 16, &c);
  // enable the sm
  pio_sm_set_enabled(pio, sm, true);
}
