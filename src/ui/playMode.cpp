#include "playMode.h"

#include "pico/audio_i2s.h"

#include "../devices/hardware.h"
#include "../graphics/graphics.h"
#include "../synth/synth.h"

static int playSampleId = -1;

void startPlayMode(CurrentOp &currentOp) {
  Synth synth;

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

    // synth.updateVoiceDown(buttonMatrixState.B0, NOTE_C4, 0);
    // synth.updateVoiceDown(buttonMatrixState.B1, NOTE_C4, 3);
    // synth.updateVoiceDown(buttonMatrixState.B2, NOTE_C4, 8);
    // synth.updateVoiceDown(buttonMatrixState.B3, NOTE_A3, 8);
    // synth.updateVoiceDown(buttonMatrixState.B4, NOTE_C4, 9);
    // synth.updateVoiceDown(buttonMatrixState.B5, NOTE_C4, 11);
    // synth.updateVoiceDown(buttonMatrixState.B6, NOTE_C4, 13);
    // synth.updateVoiceDown(buttonMatrixState.B7, NOTE_C4, 18);

    synth.updateVoiceDown(buttonMatrixState.B0, NOTE_C4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B1, NOTE_D4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B2, NOTE_E4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B3, NOTE_F4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B4, NOTE_G4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B5, NOTE_A4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B6, NOTE_B4, playSampleId);
    synth.updateVoiceDown(buttonMatrixState.B7, NOTE_C5, playSampleId);

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
}
