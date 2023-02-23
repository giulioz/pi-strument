#ifndef SYNTH_H
#define SYNTH_H

#include "pico/stdlib.h"

#include "notes.h"
#include "samples.h"

struct Voice {
  bool down;
  bool finished;
  uint32_t samplePos; // Shifted by 8
  uint16_t freq;
  uint16_t sampleId;
  uint8_t volume;
};

const int totalVoices = 8;

class Synth {
public:
  Voice voices[totalVoices] = {0};

  void startVoice(uint8_t voice, uint16_t freq, uint16_t sampleId,
                  uint8_t volume);
  void stopVoice(uint8_t voice);
  void stopAllVoices();
  uint8_t getEmptyVoice(bool alsoFinished);
  uint8_t getRunningNVoices();
  uint8_t getVoice(uint16_t freq, uint16_t sampleId);
  void updateVoiceDown(bool down, uint16_t freq, uint16_t sampleId,
                       uint8_t volume);
  void runSynth(int16_t *buffer, uint32_t bufferSize);
};

#endif
