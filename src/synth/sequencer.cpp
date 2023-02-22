#include "sequencer.h"

#include <math.h>
#include <string.h>

uint8_t getEventFreeI(const SequencerStep &step) {
  for (uint8_t i = 0; i < eventsPerStep; i++) {
    if (!step.events[i].enabled)
      return i;
  }
  return 0xFF;
}

Sequencer::Sequencer(Synth *synth) : synth(synth), lastStep(0), running(false) {
  reset();
}

void Sequencer::reset() {
  memset(recordedSteps, 0, sizeof(SequencerStep) * nSteps);
  running = false;
}

void Sequencer::start() {
  startTime = get_absolute_time();
  running = true;
}

void Sequencer::update() {
  currentTime = get_absolute_time();
  int64_t timeDiffMs = absolute_time_diff_us(startTime, currentTime) / 1000;
  int currentStep = (timeDiffMs / msPerStep) % nSteps;

  if (currentStep != lastStep) {
    // Metronome
    // if (currentStep == 0) {
    //   // startVoice(7, NOTE_D4, 18);

    //   printString("1", 5, 90);
    // } else if (currentStep == (nSteps / 4) || currentStep == (nSteps / 2) ||
    //            currentStep == (nSteps / 4) * 3) {
    //   // startVoice(7, NOTE_C4, 18);

    //   if (currentStep == (nSteps / 4))
    //     printString("2", 5, 90);
    //   if (currentStep == (nSteps / 2))
    //     printString("3", 5, 90);
    //   if (currentStep == (nSteps / 4) * 3)
    //     printString("4", 5, 90);
    // }

    for (uint8_t i = 0; i < eventsPerStep; i++) {
      if (recordedSteps[currentStep].events[i].enabled) {
        synth->startVoice(recordedSteps[currentStep].events[i].nVoice,
                          recordedSteps[currentStep].events[i].freq,
                          recordedSteps[currentStep].events[i].sampleId, 1);
      }
    }

    lastStep = currentStep;
  }
}

void Sequencer::addEventAtCurrentTime(const SequencerStepEvent &event) {
  currentTime = get_absolute_time();
  int64_t timeDiffMs = absolute_time_diff_us(startTime, currentTime) / 1000;
  int closestStep = (int)(roundf((float)timeDiffMs / msPerStep)) % nSteps;
  uint8_t nextFreeEvent = getEventFreeI(recordedSteps[closestStep]);
  if (nextFreeEvent != 0xFF) {
    recordedSteps[closestStep].events[nextFreeEvent] = event;
  }
}
