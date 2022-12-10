#include <math.h>
#include <stdio.h>

#include "hardware/adc.h"
#include "hardware/spi.h"
#include "pico/audio_i2s.h"
#include "pico/stdlib.h"

#include "devices/hardware.h"
#include "graphics/graphics.h"

struct Voice {
  bool down;
  uint32_t samplePos;
  uint16_t pitchMul;
};
Voice voices[4] = {0};

void startVoice(uint8_t voice, uint16_t pitchMul) {
  voices[voice].down = true;
  voices[voice].samplePos = 0;
  voices[voice].pitchMul = pitchMul;
}

void stopVoice(uint8_t voice) {
  voices[voice].down = false;
  voices[voice].pitchMul = 0;
}

void stopAllVoices() {
  stopVoice(0);
  stopVoice(1);
  stopVoice(2);
  stopVoice(3);
}

uint8_t getEmptyVoice() {
  if (!voices[0].down)
    return 0;
  if (!voices[1].down)
    return 1;
  if (!voices[2].down)
    return 2;
  if (!voices[3].down)
    return 3;
  return 0xFF;
}

uint8_t getVoiceWithPitch(uint16_t pitchMul) {
  if (voices[0].down && voices[0].pitchMul == pitchMul)
    return 0;
  if (voices[1].down && voices[1].pitchMul == pitchMul)
    return 1;
  if (voices[2].down && voices[2].pitchMul == pitchMul)
    return 2;
  if (voices[3].down && voices[3].pitchMul == pitchMul)
    return 3;
  return 0xFF;
}

void updateVoiceDown(bool down, uint16_t pitchMul) {
  int voiceId = getVoiceWithPitch(pitchMul);
  if (down) {
    if (voiceId == 0xFF) {
      int emptyVoiceId = getEmptyVoice();
      if (emptyVoiceId != 0xFF) {
        startVoice(emptyVoiceId, pitchMul);
      }
    }
  } else {
    if (voiceId != 0xFF) {
      voices[voiceId].down = false;
    }
  }
}

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

  int16_t max = samplingBuffer[0];
  for (uint32_t i = 0; i < 8192; i++) {
    if (abs(samplingBuffer[i]) > max)
      max = abs(samplingBuffer[i]);
  }

  st7789_fill(0x0000);
  // printString("Sampled!", 10, 80);
  for (uint32_t i = 0; i < LCD_HEIGHT; i++) {
    uint32_t currentI = i * 25;
    int16_t lmin = samplingBuffer[currentI];
    int16_t lmax = samplingBuffer[currentI];
    for (uint16_t j = 0; j < 25; j++) {
      if (samplingBuffer[currentI + j] > lmax)
        lmax = samplingBuffer[currentI + j];
      if (samplingBuffer[currentI + j] < lmin)
        lmin = samplingBuffer[currentI + j];
    }

    int minY =
        (uint16_t)(((float)lmin / max) * (LCD_WIDTH / 2) + (LCD_WIDTH / 2));
    int maxY =
        (uint16_t)(((float)lmax / max) * (LCD_WIDTH / 2) + (LCD_WIDTH / 2));
    for (uint16_t y = minY; y < maxY; y++) {
      st7789_set_cursor(y, i);
      st7789_put(COL_RED);
    }
  }

  outAudioPool = initAudioOut();

  while (true) {
    struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
    int16_t *samples = (int16_t *)buffer->buffer->bytes;

    for (uint inSamplePos = 0; inSamplePos < buffer->max_sample_count;
         inSamplePos++) {
      updateHardware();

      updateVoiceDown(buttonMatrixState.B0, 1);
      updateVoiceDown(buttonMatrixState.B1, 2);
      updateVoiceDown(buttonMatrixState.B2, 3);
      updateVoiceDown(buttonMatrixState.B3, 4);
      updateVoiceDown(buttonMatrixState.B4, 5);
      updateVoiceDown(buttonMatrixState.B5, 6);
      updateVoiceDown(buttonMatrixState.B6, 7);
      updateVoiceDown(buttonMatrixState.B7, 8);

      samples[inSamplePos] = 0;

      for (int voiceId = 0; voiceId < 4; voiceId++) {
        if (voices[voiceId].down) {
          if (voices[voiceId].samplePos >= (8192 << 1)) {
            voices[voiceId].samplePos = 0;
          }
          samples[inSamplePos] += samplingBuffer[voices[voiceId].samplePos >> 1]
                                  << 2;
          voices[voiceId].samplePos += voices[voiceId].pitchMul;
        }
      }
    }
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(outAudioPool, buffer);
  }

  return 0;
}
