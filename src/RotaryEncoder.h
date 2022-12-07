#ifndef RotaryEncoder_H
#define RotaryEncoder_H

#include "hardware/irq.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

class RotaryEncoder
{
public:
    RotaryEncoder(uint rotary_encoder_A, uint rotary_encoder_B);
    void set_rotation(int _rotation);
    int get_rotation(void);

private:
    static void pio_irq_handler();

    // the pio instance
    PIO pio;
    // the state machine
    uint sm;
    // the current location of rotation
    static int rotation;
};

#endif
