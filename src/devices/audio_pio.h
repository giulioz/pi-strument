#ifndef _PICO_AUDIO_PIO_H
#define _PICO_AUDIO_PIO_H

#include "audio_data.h"
#include "audio_pio.h"
#include "audio_pio.pio.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

#define AUDIO_PIO __CONCAT(pio, PICO_AUDIO_PIO)
#define GPIO_FUNC_PIOx __CONCAT(GPIO_FUNC_PIO, PICO_AUDIO_PIO)

// Audio format definition
typedef struct audio_format {
  uint32_t sample_freq;
  uint16_t channel_count;
  uint8_t audio_data;
  uint8_t audio_clock;
  PIO pio;
  uint8_t sm;
} audio_format_t;

static audio_format_t audio_format = {
    .sample_freq = PICO_AUDIO_FREQ,
    .channel_count = PICO_AUDIO_COUNT,
    .audio_data = PICO_AUDIO_DATA_PIN,
    .audio_clock = PICO_AUDIO_CLOCK_PIN_BASE,
    .pio = AUDIO_PIO,
    .sm = PICO_AUDIO_SM,
};

void pio_init();
void set_frequency(uint32_t frequency);
void update_pio_frequency(uint32_t sample_freq);
int32_t *data_treating(const int16_t *audio, uint32_t len);
void audio_out(int32_t *samples);

void Time_out(int32_t *samples, uint32_t time);
void Time_out_ms(int32_t *samples, uint32_t time_ms);
int32_t *Volume_16(int16_t *samples, uint32_t len, uint8_t volume);
int32_t *Volume_32(int16_t *samples, uint32_t len, uint8_t volume);
int32_t *Volume_321(int32_t *samples, uint32_t len, uint8_t volume);
void free_32(int32_t *samples);
void free_16(int16_t *samples);

void Happy_birthday_out(int32_t *samples);

#endif //_PICO_AUDIO_PIO_H
