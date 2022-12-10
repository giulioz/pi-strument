#ifndef SYNTH_H
#define SYNTH_H

#include "pico/stdlib.h"

#include "notes.h"
#include "samples.h"

struct Voice {
  bool down;
  uint32_t samplePos; // Shifted by 8
  uint16_t freq;
  uint16_t sampleId;
};

extern Voice voices[4];

void startVoice(uint8_t voice, uint16_t freq, uint16_t sampleId);
void stopVoice(uint8_t voice);
void stopAllVoices();
uint8_t getEmptyVoice();
uint8_t getVoice(uint16_t freq, uint16_t sampleId);
void updateVoiceDown(bool down, uint16_t freq, uint16_t sampleId);
void runSynth(int16_t *buffer, uint32_t bufferSize);

#endif
