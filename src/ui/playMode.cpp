#include "playMode.h"

#include <stdio.h>
#include <string.h>

#include "pico/audio_i2s.h"

#include "../devices/hardware.h"
#include "../graphics/graphics.h"
#include "../synth/synth.h"

static void updateLeds() {
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
}

static char strBuf[32] = {0};
static void redrawUI(int sampleId, int octave, int volume, int selectedMenuItem) {
  memcpy(strBuf, &samples_name[sampleId * 8], 8);
  snprintf(strBuf + 8, 32, " %d", sampleId);
  printString(strBuf, 20, 100);

  snprintf(strBuf, 32, "Octave: %d", octave);
  printString(strBuf, 20, 80);

  snprintf(strBuf, 32, "Volume: %d", volume);
  printString(strBuf, 20, 60);

  printString("Exit", 20, 40);

  if (selectedMenuItem == 0) {
    printString("\xbb", 10, 100);
    printString("\xba", 10, 80);
    printString("\xba", 10, 60);
    printString("\xba", 10, 40);
  } else if (selectedMenuItem == 1) {
    printString("\xba", 10, 100);
    printString("\xbb", 10, 80);
    printString("\xba", 10, 60);
    printString("\xba", 10, 40);
  } else if (selectedMenuItem == 2) {
    printString("\xba", 10, 100);
    printString("\xba", 10, 80);
    printString("\xbb", 10, 60);
    printString("\xba", 10, 40);
  } else if (selectedMenuItem == 3) {
    printString("\xba", 10, 100);
    printString("\xba", 10, 80);
    printString("\xba", 10, 60);
    printString("\xbb", 10, 40);
  }
}

void startPlayMode(CurrentOp &currentOp) {
  Synth synth;

  rotaryEncoderRotation = 0;

  int sampleId = 0;
  int octave = 4;
  int volume = 6;
  int selectedMenuItem = 0;

  displaySample(sampleId);
  redrawUI(sampleId, octave, volume, selectedMenuItem);

  while (true) {
    updateHardware();
    updateLeds();

    if (buttonMatrixState.B8) {
      selectedMenuItem = (selectedMenuItem + 1) % 4;
      if (selectedMenuItem == 0) {
        rotaryEncoderRotation = sampleId;
      } else if (selectedMenuItem == 1) {
        rotaryEncoderRotation = octave;
      } else if (selectedMenuItem == 2) {
        rotaryEncoderRotation = volume;
      }

      redrawUI(sampleId, octave, volume, selectedMenuItem);
      waitForNoInput();
    }

    if (selectedMenuItem == 0) {
      if (rotaryEncoderRotation < 0)
        rotaryEncoderRotation = 0;
      if (sampleId != rotaryEncoderRotation % 256) {
        sampleId = rotaryEncoderRotation % 256;
        displaySample(sampleId);
        redrawUI(sampleId, octave, volume, selectedMenuItem);
      }
    } else if (selectedMenuItem == 1) {
      if (rotaryEncoderRotation < 0)
        rotaryEncoderRotation = 0;
      if (octave != rotaryEncoderRotation % 10) {
        octave = rotaryEncoderRotation % 10;
        redrawUI(sampleId, octave, volume, selectedMenuItem);
      }
    } else if (selectedMenuItem == 2) {
      if (rotaryEncoderRotation < 0)
        rotaryEncoderRotation = 0;
      if (volume != rotaryEncoderRotation % 8) {
        volume = rotaryEncoderRotation % 8;
        redrawUI(sampleId, octave, volume, selectedMenuItem);
      }
    } else if (selectedMenuItem == 3) {
      if (buttonMatrixState.ENCBtn) {
        currentOp = OP_MENU;
        break;
      }
    }

    // synth.updateVoiceDown(buttonMatrixState.B0, NOTE_C4, 0);
    // synth.updateVoiceDown(buttonMatrixState.B1, NOTE_C4, 3);
    // synth.updateVoiceDown(buttonMatrixState.B2, NOTE_C4, 8);
    // synth.updateVoiceDown(buttonMatrixState.B3, NOTE_A3, 8);
    // synth.updateVoiceDown(buttonMatrixState.B4, NOTE_C4, 9);
    // synth.updateVoiceDown(buttonMatrixState.B5, NOTE_C4, 11);
    // synth.updateVoiceDown(buttonMatrixState.B6, NOTE_C4, 13);
    // synth.updateVoiceDown(buttonMatrixState.B7, NOTE_C4, 18);

    synth.updateVoiceDown(buttonMatrixState.B0,
                          noteFrequencies[octave * 12 + 0], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B1,
                          noteFrequencies[octave * 12 + 2], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B2,
                          noteFrequencies[octave * 12 + 4], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B3,
                          noteFrequencies[octave * 12 + 5], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B4,
                          noteFrequencies[octave * 12 + 7], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B5,
                          noteFrequencies[octave * 12 + 9], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B6,
                          noteFrequencies[octave * 12 + 11], sampleId, volume);
    synth.updateVoiceDown(buttonMatrixState.B7,
                          noteFrequencies[octave * 12 + 12], sampleId, volume);

    struct audio_buffer *buffer = take_audio_buffer(outAudioPool, true);
    int16_t *outBufferSamples = (int16_t *)buffer->buffer->bytes;
    synth.runSynth(outBufferSamples, buffer->max_sample_count);
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(outAudioPool, buffer);
  }

  synth.stopAllVoices();
}
