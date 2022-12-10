#include <math.h>
#include <stdio.h>
#include <string.h>

#include "hardware/adc.h"
#include "hardware/spi.h"
#include "pico/audio_i2s.h"
#include "pico/stdlib.h"

#include "devices/hardware.h"
#include "graphics/graphics.h"
#include "synth/synth.h"

int16_t samplingBuffer[samples_length];
int samplesRead = 0;
bool doneSampling = false;
void onAnalogSamplesReady() {
  samplesRead = analog_microphone_read(samplingBuffer, samples_length);
  doneSampling = true;
}

char strBuf[16] = {0};
void displaySample(uint16_t sampleId) {
  SampleInfo sample = samples_info[sampleId];
  uint32_t sampleStart = (sample.pos * 0x800);
  uint32_t sampleLengthExp = (sample.len & 0x70) >> 4;
  uint32_t sampleLength = (0x800 << sampleLengthExp);
  bool sampleLoop = (sample.len & 0x80) != 0;

  st7789_fill(0x0000);

  int8_t *samples_raw_int = (int8_t *)samples_raw;
  int8_t samplesMax = samples_raw_int[0];
  for (uint32_t i = sampleStart; i < sampleStart + sampleLength; i++) {
    if (abs(samples_raw_int[i]) > samplesMax)
      samplesMax = abs(samples_raw_int[i]);
  }

  uint8_t samplesPerPixel = sampleLength / LCD_WIDTH;
  for (uint32_t i = 0; i < LCD_HEIGHT; i++) {
    uint32_t currentI = sampleStart + i * samplesPerPixel;
    if (currentI >= sampleStart + sampleLength)
      break;
    int16_t lmin = samples_raw_int[currentI];
    int16_t lmax = samples_raw_int[currentI];
    for (uint16_t j = 0; j < samplesPerPixel; j++) {
      if (samples_raw_int[currentI + j] > lmax)
        lmax = samples_raw_int[currentI + j];
      if (samples_raw_int[currentI + j] < lmin)
        lmin = samples_raw_int[currentI + j];
    }

    int minY = (uint16_t)(((float)lmin / samplesMax) * (LCD_WIDTH / 2) +
                          (LCD_WIDTH / 2));
    int maxY = (uint16_t)(((float)lmax / samplesMax) * (LCD_WIDTH / 2) +
                          (LCD_WIDTH / 2));
    for (uint16_t y = minY; y < maxY; y++) {
      st7789_set_cursor(y, i);
      st7789_put(COL_RED);
    }
  }

  memcpy(strBuf, &samples_name[sampleId * 8], 8);
  snprintf(strBuf + 8, 16, " %d", sampleId);
  printString(strBuf, 10, 80);
}

int main() {
  stdio_init_all();

  initHardware();

  // st7789_fill(0x0000);
  // printString("Start Sampling!", 10, 80);
  // while (true) {
  //   updateHardware();
  //   if (buttonMatrixState.B0)
  //     break;
  // }

  // st7789_fill(0x0000);
  // printString("Started...", 10, 80);

  // analog_microphone_init(&analogMicConfig);
  // analog_microphone_set_samples_ready_handler(onAnalogSamplesReady);
  // analog_microphone_start();

  // while (!doneSampling) {
  //   sleep_ms(10);
  // }
  // sleep_ms(10);

  // analog_microphone_stop();
  // analog_microphone_deinit();

  // st7789_fill(0x0000);
  // // printString("Sampled!", 10, 80);
  // for (uint32_t i = 0; i < LCD_HEIGHT; i++) {
  //   uint32_t currentI = i * 25;
  //   int16_t lmin = samples_raw[currentI];
  //   int16_t lmax = samples_raw[currentI];
  //   for (uint16_t j = 0; j < 25; j++) {
  //     if (samples_raw[currentI + j] > lmax)
  //       lmax = samples_raw[currentI + j];
  //     if (samples_raw[currentI + j] < lmin)
  //       lmin = samples_raw[currentI + j];
  //   }

  //   int minY =
  //       (uint16_t)(((float)lmin / max) * (LCD_WIDTH / 2) + (LCD_WIDTH / 2));
  //   int maxY =
  //       (uint16_t)(((float)lmax / max) * (LCD_WIDTH / 2) + (LCD_WIDTH / 2));
  //   for (uint16_t y = minY; y < maxY; y++) {
  //     st7789_set_cursor(y, i);
  //     st7789_put(COL_RED);
  //   }
  // }

  audio_buffer_pool *outAudioPool = initAudioOut();

  int sampleId = -1;

  while (true) {
    if (rotaryEncoderRotation < 0)
      rotaryEncoderRotation = 0;
    if (sampleId != rotaryEncoderRotation % 256) {
      sampleId = rotaryEncoderRotation % 256;
      displaySample(sampleId);
    }

    updateHardware();

    updateVoiceDown(buttonMatrixState.B0, NOTE_C4, 0);
    updateVoiceDown(buttonMatrixState.B1, NOTE_C4, 3);
    updateVoiceDown(buttonMatrixState.B2, NOTE_C4, 7);
    updateVoiceDown(buttonMatrixState.B3, NOTE_C4, 8);
    updateVoiceDown(buttonMatrixState.B4, NOTE_C4, 9);
    updateVoiceDown(buttonMatrixState.B5, NOTE_C4, 10);
    updateVoiceDown(buttonMatrixState.B6, NOTE_C4, 11);
    updateVoiceDown(buttonMatrixState.B7, NOTE_C4, 13);

    struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
    int16_t *outBufferSamples = (int16_t *)buffer->buffer->bytes;
    runSynth(outBufferSamples, buffer->max_sample_count);
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(outAudioPool, buffer);
  }

  return 0;
}
