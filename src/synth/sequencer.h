#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "pico/stdlib.h"
#include <stdint.h>

#include "synth.h"

const int stepsPerBar = 16;
const int maxBars = 4;
const int msPerStep = 2000 / stepsPerBar;
const uint8_t eventsPerStep = 8;

struct SequencerStepEvent {
  bool enabled;
  uint16_t freq;
  uint16_t sampleId;
};

struct SequencerStep {
  SequencerStepEvent events[eventsPerStep];
};

class Sequencer {
public:
  SequencerStep recordedSteps[stepsPerBar * maxBars];
  int lastStep;
  int currentBars;
  uint32_t totalEvents;
  absolute_time_t startTime, currentTime;
  bool running;

  Synth *synth;

  Sequencer(Synth *synth);
  void reset();
  void start();
  void update();
  void addEventAtCurrentTime(const SequencerStepEvent &event, int quantReso);
  void setBars(int nBars);
};

#endif
