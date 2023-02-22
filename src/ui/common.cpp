#include "common.h"

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

#include "../devices/hardware.h"
#include "../graphics/graphics.h"
#include "../synth/synth.h"

void waitForNoInput() {
  while (buttonMatrixState.B0 || buttonMatrixState.B1 || buttonMatrixState.B2 ||
         buttonMatrixState.B3 || buttonMatrixState.B4 || buttonMatrixState.B5 ||
         buttonMatrixState.B6 || buttonMatrixState.B7 || buttonMatrixState.B8 ||
         buttonMatrixState.ENCBtn) {
    sleep_ms(100);
    updateHardware();
  }
}

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
}
