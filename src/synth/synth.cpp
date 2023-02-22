#include <string.h>

#include "synth.h"

void Synth::startVoice(uint8_t voice, uint16_t freq, uint16_t sampleId) {
  voices[voice].down = true;
  voices[voice].finished = false;
  voices[voice].samplePos = 0;
  voices[voice].freq = freq;
  voices[voice].sampleId = sampleId;
}

void Synth::stopVoice(uint8_t voice) {
  voices[voice].down = false;
  voices[voice].finished = true;
  voices[voice].freq = 0;
  voices[voice].sampleId = 0xFFFF;
}

void Synth::stopAllVoices() {
  stopVoice(0);
  stopVoice(1);
  stopVoice(2);
  stopVoice(3);
  stopVoice(4);
  stopVoice(5);
  stopVoice(6);
  stopVoice(7);
}

uint8_t Synth::getEmptyVoice() {
  if (!voices[0].down || voices[0].finished)
    return 0;
  if (!voices[1].down || voices[1].finished)
    return 1;
  if (!voices[2].down || voices[2].finished)
    return 2;
  if (!voices[3].down || voices[3].finished)
    return 3;
  if (!voices[4].down || voices[4].finished)
    return 4;
  if (!voices[5].down || voices[5].finished)
    return 5;
  if (!voices[6].down || voices[6].finished)
    return 6;
  if (!voices[7].down || voices[7].finished)
    return 7;
  return 0xFF;
}

uint8_t Synth::getRunningNVoices() {
  uint8_t count = 0;
  if (!voices[0].down && !voices[0].finished)
    count++;
  if (!voices[1].down && !voices[1].finished)
    count++;
  if (!voices[2].down && !voices[2].finished)
    count++;
  if (!voices[3].down && !voices[3].finished)
    count++;
  if (!voices[4].down && !voices[4].finished)
    count++;
  if (!voices[5].down && !voices[5].finished)
    count++;
  if (!voices[6].down && !voices[6].finished)
    count++;
  if (!voices[7].down && !voices[7].finished)
    count++;
  return count;
}

uint8_t Synth::getVoice(uint16_t freq, uint16_t sampleId) {
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
  if (voices[4].down && voices[4].freq == freq &&
      voices[4].sampleId == sampleId)
    return 4;
  if (voices[5].down && voices[5].freq == freq &&
      voices[5].sampleId == sampleId)
    return 5;
  if (voices[6].down && voices[6].freq == freq &&
      voices[6].sampleId == sampleId)
    return 6;
  if (voices[7].down && voices[7].freq == freq &&
      voices[7].sampleId == sampleId)
    return 7;
  return 0xFF;
}

void Synth::updateVoiceDown(bool down, uint16_t freq, uint16_t sampleId) {
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

void Synth::runSynth(int16_t *buffer, uint32_t bufferSize) {
  memset(buffer, 0, bufferSize * 2);

  int nVoices = getRunningNVoices();
  // int volume = nVoices == 1 ? 8 : 7;
  int volume = 6;

  for (int voiceId = 0; voiceId < totalVoices; voiceId++) {
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
          } else {
            voices[voiceId].finished = true;
          }
        } else {
          buffer[bufferPos] +=
              ((int8_t *)samples_raw)[sampleStart + normSamplePos] << volume;
          voices[voiceId].samplePos +=
              (((voices[voiceId].freq << 8) * 277) / NOTE_A3) / 240;
        }
      }
    }
  }
}
