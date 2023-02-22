#include "playMode.h"

#include <stdio.h>
#include <string.h>

#include "pico/audio_i2s.h"

#include "../devices/hardware.h"
#include "../graphics/graphics.h"
#include "../synth/sequencer.h"
#include "../synth/synth.h"

static char strBuf[32] = {0};
static void redrawUI(int sampleId, int octave, int volume,
                     int selectedMenuItem) {
  st7789_fill(0x0000);

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

void startSequencerMode(CurrentOp &currentOp) {
  Synth synth;
  Sequencer sequencer(&synth);

  rotaryEncoderRotation = 0;

  int sampleId = 0;
  int octave = 4;
  int volume = 6;
  int selectedMenuItem = 0;

  bool lastB0 = false;
  bool lastB1 = false;
  bool lastB2 = false;
  bool lastB3 = false;
  bool lastB4 = false;
  bool lastB5 = false;
  bool lastB6 = false;
  bool lastB7 = false;

  redrawUI(sampleId, octave, volume, selectedMenuItem);

  sequencer.start();

  while (true) {
    updateHardware();

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

    sequencer.update();

    SequencerStepEvent eventToAdd = {0};
    if (buttonMatrixState.B0 && !lastB0) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 0];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 0;
      lastB0 = true;
      synth.startVoice(0, noteFrequencies[octave * 12 + 0], sampleId, 1);
    }
    lastB0 = buttonMatrixState.B0;
    if (buttonMatrixState.B1 && !lastB1) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 2];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 1;
      lastB1 = true;
      synth.startVoice(1, noteFrequencies[octave * 12 + 2], sampleId, 1);
    }
    lastB1 = buttonMatrixState.B1;
    if (buttonMatrixState.B2 && !lastB2) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 4];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 2;
      lastB2 = true;
      synth.startVoice(2, noteFrequencies[octave * 12 + 4], sampleId, 1);
    }
    lastB2 = buttonMatrixState.B2;
    if (buttonMatrixState.B3 && !lastB3) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 5];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 3;
      lastB3 = true;
      synth.startVoice(3, noteFrequencies[octave * 12 + 5], sampleId, 1);
    }
    lastB3 = buttonMatrixState.B3;
    if (buttonMatrixState.B4 && !lastB4) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 7];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 4;
      lastB4 = true;
      synth.startVoice(4, noteFrequencies[octave * 12 + 7], sampleId, 1);
    }
    lastB4 = buttonMatrixState.B4;
    if (buttonMatrixState.B5 && !lastB5) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 9];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 5;
      lastB5 = true;
      synth.startVoice(5, noteFrequencies[octave * 12 + 9], sampleId, 1);
    }
    lastB5 = buttonMatrixState.B5;
    if (buttonMatrixState.B6 && !lastB6) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 11];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 6;
      lastB6 = true;
      synth.startVoice(6, noteFrequencies[octave * 12 + 11], sampleId, 1);
    }
    lastB6 = buttonMatrixState.B6;
    if (buttonMatrixState.B7 && !lastB7) {
      eventToAdd.enabled = true;
      eventToAdd.freq = noteFrequencies[octave * 12 + 12];
      eventToAdd.sampleId = sampleId;
      eventToAdd.nVoice = 7;
      lastB7 = true;
      synth.startVoice(7, noteFrequencies[octave * 12 + 12], sampleId, 1);
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
  synth.stopAllVoices();
}
