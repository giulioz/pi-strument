#ifndef _PICO_AUDIO_DATA_H
#define _PICO_AUDIO_DATA_H

#include "hardware/pio.h"
#include "pico/types.h"


#define PICO_AUDIO_FREQ 40000
#define PICO_AUDIO_COUNT 2
#define PICO_AUDIO_DATA_PIN 26
#define PICO_AUDIO_CLOCK_PIN_BASE 27
#define PICO_AUDIO_PIO 0
#define PICO_AUDIO_SM 0

extern const uint16_t tones[3][8];
extern const uint8_t Happy_birthday[];

extern const int16_t sine_wave_table[];

#endif //_PICO_AUDIO_DATA_H
