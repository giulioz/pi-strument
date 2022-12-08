#include <stdio.h>
#include <math.h>

#include "pico/audio_i2s.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/adc.h"

#include "config.h"
#include "st7789.h"
#include "RotaryEncoder.h"
#include "analog_microphone.h"

#define SINE_WAVE_TABLE_LEN 2048
#define SAMPLES_PER_BUFFER 256
static int16_t sine_wave_table[SINE_WAVE_TABLE_LEN];

const struct st7789_config lcd_config = {
    .spi      = PIN_LCD_SPI,
    .gpio_din = PIN_LCD_MOSI,
    .gpio_clk = PIN_LCD_SCK,
    .gpio_cs  = PIN_LCD_TCS,
    .gpio_dc  = PIN_LCD_DC,
    // .gpio_rst = PIN_LCD_RST,
    // .gpio_bl  = 0,
};
const int LCD_WIDTH = 240;
const int LCD_HEIGHT = 320;

const struct analog_microphone_config config = {
    .gpio = PIN_ADC_MIC,
    .bias_voltage = 1.25,
    .sample_rate = 24000,
    .sample_buffer_size = 256,
};

struct audio_buffer_pool *init_audio() {
  static audio_format_t audio_format = {
          .sample_freq = 24000,
          .format = AUDIO_BUFFER_FORMAT_PCM_S16,
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
          .data_pin = PIN_I2S_DATA,
          .clock_pin_base = PIN_I2S_CLOCK_BASE,
          .dma_channel = 1,
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

int RotaryEncoder::rotation = 0;

struct audio_buffer_pool *ap;

int16_t sample_buffer[256];
volatile int samples_read = 0;
void on_analog_samples_ready() {
  samples_read = analog_microphone_read(sample_buffer, 256);
}

int main() {
  stdio_init_all();

  sleep_ms(3000);

  st7789_init(&lcd_config, LCD_WIDTH, LCD_HEIGHT);
  st7789_fill(0x0000);
  // for (int x = 0; x < LCD_WIDTH; x++){
  //   for (int y = 0; y < LCD_HEIGHT; y++){
  //     st7789_set_cursor(x, y);
  //     st7789_put(((x * y) % 10) < 5 ? 0x0000 : 0xf800);
  //   }
  // }

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

  RotaryEncoder enc(PIN_ENCA, PIN_ENCB);
  enc.set_rotation(400);

  for (int i = 0; i < SINE_WAVE_TABLE_LEN; i++) {
    sine_wave_table[i] = 32767 * cosf(i * 2 * (float) (M_PI / SINE_WAVE_TABLE_LEN));
  }

  if (analog_microphone_init(&config) < 0) {
    printf("analog microphone initialization failed!\n");
    st7789_fill(0xf800);
    while (1) { tight_loop_contents(); }
  }
  analog_microphone_set_samples_ready_handler(on_analog_samples_ready);
  if (analog_microphone_start() < 0) {
    printf("analog microphone start failed!\n");
    st7789_fill(0xf800);
    while (1) { tight_loop_contents();  }
  }

  ap = init_audio();
  uint32_t step = 0x50000;
  uint32_t pos = 0;
  uint32_t pos_max = 0x10000 * SINE_WAVE_TABLE_LEN;

  while (true) {
    bool b0Value = !gpio_get(PIN_B0);
    bool b1Value = !gpio_get(PIN_B1);
    bool b2Value = !gpio_get(PIN_B2);
    bool b3Value = !gpio_get(PIN_B3);
    bool b4Value = !gpio_get(PIN_B4);
    bool b5Value = !gpio_get(PIN_B5);
    bool b6Value = !gpio_get(PIN_B6);
    bool b7Value = !gpio_get(PIN_B7);
    bool b8Value = !gpio_get(PIN_B8);
    bool bEncValue = !gpio_get(PIN_ENCBtn);

    printf("%d %d %d %d %d %d %d %d %d %d %d\n", b0Value, b1Value, b2Value, b3Value, b4Value, b5Value, b6Value, b7Value, b8Value, bEncValue, enc.get_rotation());

    int sample_count = samples_read;
    samples_read = 0;

    struct audio_buffer *buffer = take_audio_buffer(ap, true);
    int16_t *samples = (int16_t *) buffer->buffer->bytes;
    int vol = enc.get_rotation() / 30;
    for (uint i = 0; i < buffer->max_sample_count; i++) {
      samples[i] = sample_buffer[i];
      if (b0Value) {
        uint32_t clampedPos = (pos * 3) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b1Value) {
        uint32_t clampedPos = (pos * 4) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b2Value) {
        uint32_t clampedPos = (pos * 5) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b3Value) {
        uint32_t clampedPos = (pos * 6) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b4Value) {
        uint32_t clampedPos = (pos * 7) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b5Value) {
        uint32_t clampedPos = (pos * 8) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b6Value) {
        uint32_t clampedPos = (pos * 9) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      if (b7Value) {
        uint32_t clampedPos = (pos * 10) % (0x10000 * SINE_WAVE_TABLE_LEN);
        samples[i] += (vol * sine_wave_table[clampedPos >> 16u]) >> 8u;
      }
      pos += step;
    }
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(ap, buffer);
  }

  return 0;
}
