#include <stdio.h>
#include <math.h>

#include "config.h"
#include "pico/audio_i2s.h"
#include "pico/stdlib.h"

#define SINE_WAVE_TABLE_LEN 2048
#define SAMPLES_PER_BUFFER 256

static int16_t sine_wave_table[SINE_WAVE_TABLE_LEN];

struct audio_buffer_pool *init_audio() {
  static audio_format_t audio_format = {
          .format = AUDIO_BUFFER_FORMAT_PCM_S16,
          .sample_freq = 24000,
          .channel_count = 1,
  };

  static struct audio_buffer_format producer_format = {
          .format = &audio_format,
          .sample_stride = 2
  };

  struct audio_buffer_pool *producer_pool = audio_new_producer_pool(&producer_format, 3,
                                                                    SAMPLES_PER_BUFFER); // todo correct size
  bool __unused ok;
  const struct audio_format *output_format;
  struct audio_i2s_config config = {
          .data_pin = PICO_AUDIO_I2S_DATA_PIN,
          .clock_pin_base = PICO_AUDIO_I2S_CLOCK_PIN_BASE,
          .dma_channel = 0,
          .pio_sm = 0,
  };

  output_format = audio_i2s_setup(&audio_format, &config);
  if (!output_format) {
    panic("PicoAudio: Unable to open audio device.\n");
  }

  ok = audio_i2s_connect(producer_pool);
  assert(ok);
  audio_i2s_set_enabled(true);
  return producer_pool;
}

int main() {
  stdio_init_all();

  // sleep_ms(4000);

  gpio_init(PIN_B1);
  gpio_init(PIN_B2);
  gpio_pull_up(PIN_B1);
  gpio_pull_up(PIN_B2);
  gpio_set_dir(PIN_B1, GPIO_IN);
  gpio_set_dir(PIN_B2, GPIO_IN);

  for (int i = 0; i < SINE_WAVE_TABLE_LEN; i++) {
    sine_wave_table[i] = 32767 * cosf(i * 2 * (float) (M_PI / SINE_WAVE_TABLE_LEN));
  }

  struct audio_buffer_pool *ap = init_audio();
  uint32_t step = 0x50000;
  uint32_t pos = 0;
  uint32_t pos_max = 0x10000 * SINE_WAVE_TABLE_LEN;
  while (true) {
      int c = getchar_timeout_us(0);
      bool b1Value = gpio_get(PIN_B1);
      bool b2Value = gpio_get(PIN_B2);
      struct audio_buffer *buffer = take_audio_buffer(ap, true);
      int16_t *samples = (int16_t *) buffer->buffer->bytes;
      for (uint i = 0; i < buffer->max_sample_count; i++) {
        samples[i] = 0;
        if (!b1Value) {
          uint32_t clampedPosA = (pos * 3*2) % (0x10000 * SINE_WAVE_TABLE_LEN);
          uint32_t clampedPosA_H = (sine_wave_table[clampedPosA >> 16u] + (pos * 3)) % (0x10000 * SINE_WAVE_TABLE_LEN);
          samples[i] += (3 * sine_wave_table[clampedPosA_H >> 16u]) >> 8u;
        }
        if (!b2Value) {
          uint32_t clampedPosB = (pos * 4*2) % (0x10000 * SINE_WAVE_TABLE_LEN);
          uint32_t clampedPosB_H = (sine_wave_table[clampedPosB >> 16u] + (pos * 4)) % (0x10000 * SINE_WAVE_TABLE_LEN);
          samples[i] += (3 * sine_wave_table[clampedPosB_H >> 16u]) >> 8u;
        }
        pos += step;
      }
      buffer->sample_count = buffer->max_sample_count;
      give_audio_buffer(ap, buffer);
  }

  return 0;
}
