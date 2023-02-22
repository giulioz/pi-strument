#include <math.h>
#include <stdio.h>
#include <string.h>

#include "hardware/adc.h"
#include "hardware/spi.h"
#include "pico/audio_i2s.h"
#include "pico/stdlib.h"

#include "devices/hardware.h"
#include "graphics/graphics.h"
#include "synth/sequencer.h"
#include "synth/synth.h"
#include "ui/common.h"
#include "ui/mainMenu.h"
#include "ui/playMode.h"

int16_t samplingBuffer[samples_length];
int samplesRead = 0;
bool doneSampling = false;
void onAnalogSamplesReady() {
  samplesRead = analog_microphone_read(samplingBuffer, samples_length);
  doneSampling = true;
}

CurrentOp currentOp = OP_MENU;

int main() {
  stdio_init_all();

  initHardware();

  while (true) {
    if (currentOp == OP_MENU) {
      startMainMenu(currentOp);
    } else if (currentOp == OP_PLAY) {
      startPlayMode(currentOp);
    } else if (currentOp == OP_SEQUENCER) {
      st7789_fill(0x0000);
      printString("Tempo: 120 BPM", 5, 120);

      // uint16_t ledsState = 0;
      // setLEDS(ledsState);

      // bool lastB0 = false;
      // bool lastB1 = false;
      // bool lastB2 = false;
      // bool lastB3 = false;
      // bool lastB4 = false;
      // bool lastB5 = false;
      // bool lastB6 = false;
      // bool lastB7 = false;

      // Sequencer sequencer(&synth);
      // sequencer.start();

      // while (true) {
      //   updateHardware();

      //   if (buttonMatrixState.B8) {
      //     currentOp = OP_MENU;
      //     break;
      //   }

      //   sequencer.update();

      //   SequencerStepEvent eventToAdd = {0};
      //   if (buttonMatrixState.B0 && !lastB0) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 0;
      //     eventToAdd.nVoice = 0;
      //     lastB0 = true;
      //     synth.startVoice(0, NOTE_C4, 0);
      //   }
      //   lastB0 = buttonMatrixState.B0;
      //   if (buttonMatrixState.B1 && !lastB1) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 3;
      //     eventToAdd.nVoice = 1;
      //     lastB1 = true;
      //     synth.startVoice(1, NOTE_C4, 3);
      //   }
      //   lastB1 = buttonMatrixState.B1;
      //   if (buttonMatrixState.B2 && !lastB2) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 8;
      //     eventToAdd.nVoice = 2;
      //     lastB2 = true;
      //     synth.startVoice(2, NOTE_C4, 8);
      //   }
      //   lastB2 = buttonMatrixState.B2;
      //   if (buttonMatrixState.B3 && !lastB3) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_A3;
      //     eventToAdd.sampleId = 8;
      //     eventToAdd.nVoice = 3;
      //     lastB3 = true;
      //     synth.startVoice(3, NOTE_A3, 8);
      //   }
      //   lastB3 = buttonMatrixState.B3;
      //   if (buttonMatrixState.B4 && !lastB4) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 9;
      //     eventToAdd.nVoice = 4;
      //     lastB4 = true;
      //     synth.startVoice(4, NOTE_C4, 9);
      //   }
      //   lastB4 = buttonMatrixState.B4;
      //   if (buttonMatrixState.B5 && !lastB5) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 11;
      //     eventToAdd.nVoice = 5;
      //     lastB5 = true;
      //     synth.startVoice(5, NOTE_C4, 11);
      //   }
      //   lastB5 = buttonMatrixState.B5;
      //   if (buttonMatrixState.B6 && !lastB6) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 13;
      //     eventToAdd.nVoice = 6;
      //     lastB6 = true;
      //     synth.startVoice(6, NOTE_C4, 13);
      //   }
      //   lastB6 = buttonMatrixState.B6;
      //   if (buttonMatrixState.B7 && !lastB7) {
      //     eventToAdd.enabled = true;
      //     eventToAdd.freq = NOTE_C4;
      //     eventToAdd.sampleId = 18;
      //     eventToAdd.nVoice = 7;
      //     lastB7 = true;
      //     synth.startVoice(7, NOTE_C4, 18);
      //   }
      //   lastB7 = buttonMatrixState.B7;

      //   if (eventToAdd.enabled) {
      //     sequencer.addEventAtCurrentTime(eventToAdd);
      //   }

      //   struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
      //   int16_t *outBufferSamples = (int16_t *)buffer->buffer->bytes;
      //   synth.runSynth(outBufferSamples, buffer->max_sample_count);
      //   buffer->sample_count = buffer->max_sample_count;
      //   give_audio_buffer(outAudioPool, buffer);
      // }

      // sequencer.reset();
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
