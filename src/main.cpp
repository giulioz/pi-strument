#include <math.h>
#include <stdio.h>

#include "hardware/adc.h"
#include "hardware/spi.h"
#include "pico/audio_i2s.h"
#include "pico/stdlib.h"

#include "devices/hardware.h"
#include "graphics/graphics.h"

struct audio_buffer_pool *outAudioPool;

int16_t samplingBuffer[8192];
int samplesRead = 0;
bool doneSampling = false;
void onAnalogSamplesReady() {
  samplesRead = analog_microphone_read(samplingBuffer, 8192);
  doneSampling = true;
}

int main() {
  stdio_init_all();

  initHardware();

  st7789_fill(0x0000);
  printString("Start Sampling!", 10, 80);
  while (true) {
    updateHardware();
    if (buttonMatrixState.B0)
      break;
  }

  st7789_fill(0x0000);
  printString("Started...", 10, 80);

  analog_microphone_init(&analogMicConfig);
  analog_microphone_set_samples_ready_handler(onAnalogSamplesReady);
  analog_microphone_start();

  while (!doneSampling) {
    sleep_ms(10);
  }
  sleep_ms(10);


  analog_microphone_stop();
  analog_microphone_deinit();

  st7789_fill(0x0000);
  printString("Sampled!", 10, 80);

  outAudioPool = initAudioOut();

  uint32_t pos = 0;

  while (true) {
    struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
    int16_t *samples = (int16_t *)buffer->buffer->bytes;

    for (uint i = 0; i < buffer->max_sample_count; i++) {
      updateHardware();
      samples[i] = 0;
      if (buttonMatrixState.B0) {
        uint32_t clampedPos = (pos * 1) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B1) {
        uint32_t clampedPos = (pos * 3) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B2) {
        uint32_t clampedPos = (pos * 5) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B3) {
        uint32_t clampedPos = (pos * 7) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B4) {
        uint32_t clampedPos = (pos * 9) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B5) {
        uint32_t clampedPos = (pos * 11) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B6) {
        uint32_t clampedPos = (pos * 13) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      if (buttonMatrixState.B7) {
        uint32_t clampedPos = (pos * 15) % 8192;
        samples[i] += samplingBuffer[clampedPos] >> 3;
      }
      pos += 1;
    }
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(outAudioPool, buffer);
  }

  return 0;
}
