#include "audio_pio.h"

#include <stdlib.h>

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

void set_frequency(uint32_t frequency) {
  update_pio_frequency(frequency * 256);
}

/******************************************************************************
function: Sampling frequency modification
parameter:
    sample_freq :  sample freq
******************************************************************************/
void update_pio_frequency(uint32_t sample_freq) {
  uint32_t system_clock_frequency = clock_get_hz(clk_sys);
  uint32_t divider =
      system_clock_frequency * 4 / sample_freq;  // avoid arithmetic overflow
  pio_sm_set_clkdiv_int_frac(audio_format.pio, audio_format.sm, divider >> 8u,
                             divider & 0xffu);
  audio_format.sample_freq = sample_freq;
}

/******************************************************************************
function: 16 bit unsigned audio data processing
parameter:
    audio :  16-bit audio array
    len   :  The length of the array
return:  The address of a 32-bit array
******************************************************************************/
int32_t *data_treating(const int16_t *audio, uint32_t len) {
  int32_t *samples = (int32_t *)calloc(len, sizeof(int32_t));
  for (uint32_t i = 0; i < len; i++) {
    if (audio_format.channel_count == 1) {
      samples[i] = sine_wave_table[i] - 0x7fff;
    } else {
      samples[i] = ((sine_wave_table[i] - 0x7fff) * 65536) +
                   (sine_wave_table[i] - 0x7fff);
    }
  }
  return samples;
}

/******************************************************************************
function: audio out
parameter:
    samples :  32-bit audio array
******************************************************************************/
void audio_out(int32_t *samples) {
  for (uint16_t i = 0; i < 256; i++)
    pio_sm_put_blocking(audio_format.pio, audio_format.sm, samples[i]);
}

/******************************************************************************
function: pio init
parameter:
******************************************************************************/
void pio_init() {
  gpio_set_function(audio_format.audio_data, GPIO_FUNC_PIOx);
  gpio_set_function(audio_format.audio_clock, GPIO_FUNC_PIOx);
  gpio_set_function(audio_format.audio_clock + 1, GPIO_FUNC_PIOx);

  pio_sm_claim(audio_format.pio, audio_format.sm);

  uint offset = pio_add_program(audio_format.pio, &audio_pio_program);

  audio_pio_program_init(audio_format.pio, audio_format.sm, offset,
                         audio_format.audio_data, audio_format.audio_clock);

  uint32_t system_clock_frequency = clock_get_hz(clk_sys);
  uint32_t divider = system_clock_frequency * 4 /
                     audio_format.sample_freq;  // avoid arithmetic overflow
  pio_sm_set_clkdiv_int_frac(audio_format.pio, audio_format.sm, divider >> 8u,
                             divider & 0xffu);

  pio_sm_set_enabled(audio_format.pio, audio_format.sm, true);
}

/******************************************************************************
function: Audio output over time
parameter:
    samples :  32-bit audio array
        time	:  unit seconds
******************************************************************************/
void Time_out(int32_t *samples, uint32_t time) {
  for (uint32_t i = 0; i < (audio_format.sample_freq * time) / 256; i++)
    audio_out(samples);
}

/******************************************************************************
function: Audio output over time
parameter:
    samples :  32-bit audio array
        time_ms	:  unit ms
******************************************************************************/
void Time_out_ms(int32_t *samples, uint32_t time_ms) {
  for (uint32_t i = 0; i < (audio_format.sample_freq * time_ms) / (1000 * 256);
       i++)
    audio_out(samples);
}

/******************************************************************************
function: Adjust 32-bit volume
parameter:
    samples :  32-bit audio array
        len     :  The length of the array
        volume	:  The volume size
return:  The address of a 32-bit array
******************************************************************************/
int32_t *Volume_32(int16_t *samples, uint32_t len, uint8_t volume) {
  uint32_t *samples1 = (uint32_t *)calloc(len, sizeof(uint32_t));
  for (uint32_t i = 0; i < len; i++)
    samples1[i] =
        (((samples[i] * volume) / 100) * 65536) + ((samples[i] * volume) / 100);
  return samples1;
}

int32_t *Volume_321(int32_t *samples, uint32_t len, uint8_t volume) {
  uint32_t *samples1 = (uint32_t *)calloc(len, sizeof(uint32_t));
  int16_t a, b;
  for (uint32_t i = 0; i < len; i++) {
    a = samples[i] >> 16;
    b = samples[i];
    samples1[i] = (((a * volume) / 100) * 65536) + ((b * volume) / 100);
  }

  return samples1;
}

/******************************************************************************
function: Adjust 16-bit volume
parameter:
    samples :  16-bit audio array
        len     :  The length of the array
        volume	:  The volume size
return:  The address of a 16-bit array
******************************************************************************/
int32_t *Volume_16(int16_t *samples, uint32_t len, uint8_t volume) {
  int32_t *samples1 = (int32_t *)calloc(len, sizeof(int32_t));
  for (uint32_t i = 0; i < len; i++) samples1[i] = (samples[i] * volume) / 100;
  return samples1;
}

/******************************************************************************
function: Free the 32-bit array
parameter:
    samples :  32-bit audio array
******************************************************************************/
void free_32(int32_t *samples) {
  int32_t *samples1 = samples;
  samples = NULL;
  free(samples1);
}

/******************************************************************************
function: Free the 16-bit array
parameter:
    samples :  16-bit audio array
******************************************************************************/
void free_16(int16_t *samples) {
  int16_t *samples1 = samples;
  samples = NULL;
  free(samples1);
}

/******************************************************************************
function: Default song playing
parameter:
    samples :  32 bit default song data
******************************************************************************/
void Happy_birthday_out(int32_t *samples) {
  uint8_t k, n, g, o;
  uint16_t p;
  k = 0;
  while (Happy_birthday[k] != 0) {
    n = Happy_birthday[k++];
    g = Happy_birthday[k++];
    p = tones[g][n];
    o = Happy_birthday[k++];
    set_frequency(p);
    Time_out_ms(samples, o * 344);
  }
  sleep_ms(500);
}
