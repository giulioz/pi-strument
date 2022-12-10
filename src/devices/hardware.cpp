#include "hardware.h"

st7789_config lcdConfig = {
    .spi = PIN_LCD_SPI,
    .gpio_din = PIN_LCD_MOSI,
    .gpio_clk = PIN_LCD_SCK,
    .gpio_cs = PIN_LCD_TCS,
    .gpio_dc = PIN_LCD_DC,
    // .gpio_rst = PIN_LCD_RST,
    // .gpio_bl  = 0,
};

analog_microphone_config analogMicConfig = {
    .gpio = PIN_ADC_MIC,
    .bias_voltage = 1.25,
    .sample_rate = 24000,
    .sample_buffer_size = 8192,
};

audio_format_t outAudioFormat = {
    .sample_freq = 24000,
    .format = AUDIO_BUFFER_FORMAT_PCM_S16,
    .channel_count = 1,
};

audio_buffer_format outProducerFormat = {.format = &outAudioFormat,
                                         .sample_stride = 2};

void initHardware() {
  initRotaryEncoder();
  initButtonMatrix();

  st7789_init(&lcdConfig, LCD_WIDTH, LCD_HEIGHT);
  st7789_fill(0x0000);
}

void updateHardware() { getButtonMatrix(); }

audio_buffer_pool *initAudioOut() {
  audio_buffer_pool *producerPool =
      audio_new_producer_pool(&outProducerFormat, 3, SAMPLES_PER_BUFFER);
  bool __unused ok;
  const audio_format *output_format;
  audio_i2s_config config = {
      .data_pin = PIN_I2S_DATA,
      .clock_pin_base = PIN_I2S_CLOCK_BASE,
      .dma_channel = 1,
      .pio_sm = 0,
  };

  output_format = audio_i2s_setup(&outAudioFormat, &config);
  if (!output_format) {
    panic("PicoAudio: Unable to open audio device.\n");
  }

  ok = audio_i2s_connect(producerPool);
  assert(ok);
  audio_i2s_set_enabled(true);
  return producerPool;
}
