#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "pico/stdlib.h"
#include <stdint.h>

#include "synth.h"

const int nSteps = 32;
const int msPerStep = 2000 / nSteps;
const uint8_t eventsPerStep = 8;

struct SequencerStepEvent {
  bool enabled;
  uint16_t freq;
  uint16_t sampleId;
  uint16_t nVoice;
};

struct SequencerStep {
  SequencerStepEvent events[eventsPerStep];
};

class Sequencer {
  SequencerStep recordedSteps[nSteps];
  int lastStep;
  absolute_time_t startTime, currentTime;
  bool running;

  Synth *synth;

public:
  Sequencer(Synth *synth);
  void reset();
  void start();
  void update();
  void addEventAtCurrentTime(const SequencerStepEvent &event);
};

#endif
