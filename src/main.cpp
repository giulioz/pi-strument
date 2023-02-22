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
#include "ui/sequencerMode.h"

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
      startSequencerMode(currentOp);
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
