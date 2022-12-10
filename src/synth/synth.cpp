#include <string.h>

#include "synth.h"

Voice voices[4] = {0};

void startVoice(uint8_t voice, uint16_t freq, uint16_t sampleId) {
  voices[voice].down = true;
  voices[voice].samplePos = 0;
  voices[voice].freq = freq;
  voices[voice].sampleId = sampleId;
}

void stopVoice(uint8_t voice) {
  voices[voice].down = false;
  voices[voice].freq = 0;
  voices[voice].sampleId = 0xFFFF;
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

uint8_t getVoice(uint16_t freq, uint16_t sampleId) {
  if (voices[0].down && voices[0].freq == freq &&
      voices[0].sampleId == sampleId)
    return 0;
  if (voices[1].down && voices[1].freq == freq &&
      voices[1].sampleId == sampleId)
    return 1;
  if (voices[2].down && voices[2].freq == freq &&
      voices[2].sampleId == sampleId)
    return 2;
  if (voices[3].down && voices[3].freq == freq &&
      voices[3].sampleId == sampleId)
    return 3;
  return 0xFF;
}

void updateVoiceDown(bool down, uint16_t freq, uint16_t sampleId) {
  int voiceId = getVoice(freq, sampleId);
  if (down) {
    if (voiceId == 0xFF) {
      int emptyVoiceId = getEmptyVoice();
      if (emptyVoiceId != 0xFF) {
        startVoice(emptyVoiceId, freq, sampleId);
      }
    }
  } else {
    if (voiceId != 0xFF) {
      voices[voiceId].down = false;
    }
  }
}

void runSynth(int16_t *buffer, uint32_t bufferSize) {
  memset(buffer, 0, bufferSize * 2);

  for (int voiceId = 0; voiceId < 4; voiceId++) {
    if (voices[voiceId].down) {
      SampleInfo sample = samples_info[voices[voiceId].sampleId];
      uint32_t sampleStart = (sample.pos * 0x800);
      uint32_t sampleLengthExp = (sample.len & 0x70) >> 4;
      uint32_t sampleLength = (0x800 << sampleLengthExp);
      bool sampleLoop = (sample.len & 0x80) != 0;

      for (uint16_t bufferPos = 0; bufferPos < bufferSize; bufferPos++) {
        uint32_t normSamplePos = voices[voiceId].samplePos >> 8;
        if (normSamplePos >= sampleLength) {
          if (sampleLoop) {
            voices[voiceId].samplePos = 0;
            normSamplePos = 0;
          }
        } else {
          buffer[bufferPos] +=
              ((int8_t *)samples_raw)[sampleStart + normSamplePos] << 8;
          voices[voiceId].samplePos +=
              (((voices[voiceId].freq << 8) * 277) / NOTE_A3) / 240;
        }
      }
    }
  }
}
