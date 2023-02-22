#ifndef UI_COMMON_H
#define UI_COMMON_H

#include <stdint.h>

enum CurrentOp {
  OP_MENU,
  OP_PLAY,
  OP_SEQUENCER,
  OP_SAMPLER,
};

void waitForNoInput();
void displaySample(uint16_t sampleId);

#endif
