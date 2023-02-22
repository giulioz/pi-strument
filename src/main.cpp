#include <math.h>
#include <stdio.h>
#include <string.h>

#include "hardware/adc.h"
#include "hardware/spi.h"
#include "pico/audio_i2s.h"
#include "pico/stdlib.h"

#include "devices/hardware.h"
#include "graphics/graphics.h"
#include "sequencer.h"
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

enum CurrentOp {
  OP_MENU,
  OP_PLAY,
  OP_SEQUENCER,
  OP_SAMPLER,
};

CurrentOp currentOp = OP_MENU;
int menuPos = 0;
int playSampleId = -1;

int main() {
  stdio_init_all();

  initHardware();

  audio_buffer_pool *outAudioPool = initAudioOut();

  Synth synth;

  while (true) {
    if (currentOp == OP_MENU) {
      st7789_fill(0x0000);
      printString("1. Play", 5, 120);
      printString("2. Sequencer", 5, 90);
      printString("3. Sampler", 5, 60);
      setLEDS(0b111);

      while (true) {
        updateHardware();
        if (buttonMatrixState.B0) {
          currentOp = OP_PLAY;
          rotaryEncoderRotation = playSampleId;
          while (buttonMatrixState.B0) {
            sleep_ms(100);
            updateHardware();
          }
          buttonMatrixState.B0 = false;
          break;
        }
        if (buttonMatrixState.B1) {
          currentOp = OP_SEQUENCER;
          while (buttonMatrixState.B1) {
            sleep_ms(100);
            updateHardware();
          }
          buttonMatrixState.B1 = false;
          break;
        }
        if (buttonMatrixState.B2) {
          currentOp = OP_SAMPLER;
          while (buttonMatrixState.B2) {
            sleep_ms(100);
            updateHardware();
          }
          buttonMatrixState.B2 = false;
          break;
        }
      }
    } else if (currentOp == OP_PLAY) {
      rotaryEncoderRotation = 0;
      playSampleId = 0;
      displaySample(playSampleId);

      while (true) {
        updateHardware();

        if (buttonMatrixState.B8) {
          currentOp = OP_MENU;
          break;
        }

        if (rotaryEncoderRotation < 0)
          rotaryEncoderRotation = 0;
        if (playSampleId != rotaryEncoderRotation % 256) {
          playSampleId = rotaryEncoderRotation % 256;
          displaySample(playSampleId);
        }

        synth.updateVoiceDown(buttonMatrixState.B0, NOTE_C4, 0);
        synth.updateVoiceDown(buttonMatrixState.B1, NOTE_C4, 3);
        synth.updateVoiceDown(buttonMatrixState.B2, NOTE_C4, 8);
        synth.updateVoiceDown(buttonMatrixState.B3, NOTE_A3, 8);
        synth.updateVoiceDown(buttonMatrixState.B4, NOTE_C4, 9);
        synth.updateVoiceDown(buttonMatrixState.B5, NOTE_C4, 11);
        synth.updateVoiceDown(buttonMatrixState.B6, NOTE_C4, 13);
        synth.updateVoiceDown(buttonMatrixState.B7, NOTE_C4, 18);

        uint16_t ledsState = 0;
        if (buttonMatrixState.B0)
          ledsState |= 0b000000001;
        if (buttonMatrixState.B1)
          ledsState |= 0b000000010;
        if (buttonMatrixState.B2)
          ledsState |= 0b000000100;
        if (buttonMatrixState.B3)
          ledsState |= 0b000001000;
        if (buttonMatrixState.B4)
          ledsState |= 0b00010000;
        if (buttonMatrixState.B5)
          ledsState |= 0b000100000;
        if (buttonMatrixState.B6)
          ledsState |= 0b001000000;
        if (buttonMatrixState.B7)
          ledsState |= 0b010000000;
        if (buttonMatrixState.B8)
          ledsState |= 0b100000000;
        if (buttonMatrixState.ENCBtn)
          ledsState |= 0b111111111;
        setLEDS(ledsState);

        struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
        int16_t *outBufferSamples = (int16_t *)buffer->buffer->bytes;
        synth.runSynth(outBufferSamples, buffer->max_sample_count);
        buffer->sample_count = buffer->max_sample_count;
        give_audio_buffer(outAudioPool, buffer);
      }
    } else if (currentOp == OP_SEQUENCER) {
      st7789_fill(0x0000);
      printString("Tempo: 120 BPM", 5, 120);

      uint16_t ledsState = 0;
      setLEDS(ledsState);

      bool lastB0 = false;
      bool lastB1 = false;
      bool lastB2 = false;
      bool lastB3 = false;
      bool lastB4 = false;
      bool lastB5 = false;
      bool lastB6 = false;
      bool lastB7 = false;

      Sequencer sequencer(&synth);
      sequencer.start();

      while (true) {
        updateHardware();

        if (buttonMatrixState.B8) {
          currentOp = OP_MENU;
          break;
        }

        sequencer.update();

        SequencerStepEvent eventToAdd = {0};
        if (buttonMatrixState.B0 && !lastB0) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 0;
          eventToAdd.nVoice = 0;
          lastB0 = true;
          synth.startVoice(0, NOTE_C4, 0);
        }
        lastB0 = buttonMatrixState.B0;
        if (buttonMatrixState.B1 && !lastB1) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 3;
          eventToAdd.nVoice = 1;
          lastB1 = true;
          synth.startVoice(1, NOTE_C4, 3);
        }
        lastB1 = buttonMatrixState.B1;
        if (buttonMatrixState.B2 && !lastB2) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 8;
          eventToAdd.nVoice = 2;
          lastB2 = true;
          synth.startVoice(2, NOTE_C4, 8);
        }
        lastB2 = buttonMatrixState.B2;
        if (buttonMatrixState.B3 && !lastB3) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_A3;
          eventToAdd.sampleId = 8;
          eventToAdd.nVoice = 3;
          lastB3 = true;
          synth.startVoice(3, NOTE_A3, 8);
        }
        lastB3 = buttonMatrixState.B3;
        if (buttonMatrixState.B4 && !lastB4) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 9;
          eventToAdd.nVoice = 4;
          lastB4 = true;
          synth.startVoice(4, NOTE_C4, 9);
        }
        lastB4 = buttonMatrixState.B4;
        if (buttonMatrixState.B5 && !lastB5) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 11;
          eventToAdd.nVoice = 5;
          lastB5 = true;
          synth.startVoice(5, NOTE_C4, 11);
        }
        lastB5 = buttonMatrixState.B5;
        if (buttonMatrixState.B6 && !lastB6) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 13;
          eventToAdd.nVoice = 6;
          lastB6 = true;
          synth.startVoice(6, NOTE_C4, 13);
        }
        lastB6 = buttonMatrixState.B6;
        if (buttonMatrixState.B7 && !lastB7) {
          eventToAdd.enabled = true;
          eventToAdd.freq = NOTE_C4;
          eventToAdd.sampleId = 18;
          eventToAdd.nVoice = 7;
          lastB7 = true;
          synth.startVoice(7, NOTE_C4, 18);
        }
        lastB7 = buttonMatrixState.B7;

        if (eventToAdd.enabled) {
          sequencer.addEventAtCurrentTime(eventToAdd);
        }

        struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
        int16_t *outBufferSamples = (int16_t *)buffer->buffer->bytes;
        synth.runSynth(outBufferSamples, buffer->max_sample_count);
        buffer->sample_count = buffer->max_sample_count;
        give_audio_buffer(outAudioPool, buffer);
      }

      sequencer.reset();
    }
  }

  // st7789_fill(0x0000);
  // printString("Start Sampling!", 10, 80);
  // while (true) {
  //   updateHardware();
  //   if (buttonMatrixState.B8)
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

  return 0;
}
