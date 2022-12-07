#include <stdio.h>
#include <math.h>

#include "pico/audio_i2s.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "config.h"
#include "st7789.h"

#define SINE_WAVE_TABLE_LEN 2048
#define SAMPLES_PER_BUFFER 256
static int16_t sine_wave_table[SINE_WAVE_TABLE_LEN];

const struct st7789_config lcd_config = {
    .spi      = PIN_LCD_SPI,
    .gpio_din = PIN_LCD_MOSI,
    .gpio_clk = PIN_LCD_SCK,
    .gpio_cs  = PIN_LCD_TCS,
    .gpio_dc  = PIN_LCD_DC,
    .gpio_rst = PIN_LCD_RST,
    // .gpio_bl  = 0,
};
const int LCD_WIDTH = 240;
const int LCD_HEIGHT = 320;

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

  st7789_init(&lcd_config, LCD_WIDTH, LCD_HEIGHT);
  st7789_fill(0x0000);

  for (int x = 0; x < LCD_WIDTH; x++){
    for (int y = 0; y < LCD_HEIGHT; y++){
      st7789_set_cursor(x, y);
      st7789_put(((x * y) % 10) < 5 ? 0x0000 : 0xf800);
    }
  }

  gpio_init(PIN_BR1);
  gpio_init(PIN_BR2);
  gpio_init(PIN_BS1);
  gpio_init(PIN_BS2);
  gpio_init(PIN_BS3);
  gpio_set_dir(PIN_BR1, GPIO_IN);
  gpio_set_dir(PIN_BR2, GPIO_IN);
  gpio_set_dir(PIN_BS1, GPIO_OUT);
  gpio_set_dir(PIN_BS2, GPIO_OUT);
  gpio_set_dir(PIN_BS3, GPIO_OUT);
  gpio_pull_up(PIN_BR1);
  gpio_pull_up(PIN_BR2);
  gpio_put(PIN_BS1, 1);
  gpio_put(PIN_BS2, 1);
  gpio_put(PIN_BS3, 1);

  for (int i = 0; i < SINE_WAVE_TABLE_LEN; i++) {
    sine_wave_table[i] = 32767 * cosf(i * 2 * (float) (M_PI / SINE_WAVE_TABLE_LEN));
  }

  struct audio_buffer_pool *ap = init_audio();
  uint32_t step = 0x50000;
  uint32_t pos = 0;
  uint32_t pos_max = 0x10000 * SINE_WAVE_TABLE_LEN;
  while (true) {
    gpio_put(PIN_BS1, 0);
    gpio_put(PIN_BS2, 1);
    gpio_put(PIN_BS3, 1);
    sleep_ms(1);
    bool b2Value = gpio_get(PIN_BR1);
    bool b1Value = gpio_get(PIN_BR2);

    gpio_put(PIN_BS1, 1);
    gpio_put(PIN_BS2, 0);
    gpio_put(PIN_BS3, 1);
    sleep_ms(1);
    bool b6Value = gpio_get(PIN_BR1);
    bool b5Value = gpio_get(PIN_BR2);

    gpio_put(PIN_BS1, 1);
    gpio_put(PIN_BS2, 1);
    gpio_put(PIN_BS3, 0);
    sleep_ms(1);
    bool b4Value = gpio_get(PIN_BR1);
    bool b3Value = gpio_get(PIN_BR2);

    printf("%d %d %d %d %d %d\n", b1Value, b2Value, b3Value, b4Value, b5Value, b6Value);

    struct audio_buffer *buffer = take_audio_buffer(ap, true);
    int16_t *samples = (int16_t *) buffer->buffer->bytes;
    for (uint i = 0; i < buffer->max_sample_count; i++) {
      samples[i] = 0;
      if (!b1Value) {
        uint32_t clampedPosA = (pos * 3) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (3 * sine_wave_table[clampedPosA >> 16u]) >> 8u;
      }
      if (!b2Value) {
        uint32_t clampedPosB = (pos * 4) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (3 * sine_wave_table[clampedPosB >> 16u]) >> 8u;
      }
      if (!b3Value) {
        uint32_t clampedPosB = (pos * 5) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (3 * sine_wave_table[clampedPosB >> 16u]) >> 8u;
      }
      if (!b4Value) {
        uint32_t clampedPosB = (pos * 6) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (3 * sine_wave_table[clampedPosB >> 16u]) >> 8u;
      }
      if (!b5Value) {
        uint32_t clampedPosB = (pos * 7) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (3 * sine_wave_table[clampedPosB >> 16u]) >> 8u;
      }
      if (!b6Value) {
        uint32_t clampedPosB = (pos * 8) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (3 * sine_wave_table[clampedPosB >> 16u]) >> 8u;
      }
      pos += step;
    }
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(ap, buffer);
  }

  return 0;
}
