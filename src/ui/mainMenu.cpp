#include "mainMenu.h"

#include "../devices/hardware.h"
#include "../graphics/graphics.h"

void startMainMenu(CurrentOp &currentOp) {
  st7789_fill(0x0000);
  printString("1. Play", 5, 120);
  printString("2. Sequencer", 5, 90);
  printString("3. Sampler", 5, 60);
  setLEDS(0b111);

  while (true) {
    updateHardware();
    if (buttonMatrixState.B0) {
      currentOp = OP_PLAY;
      break;
    }
    if (buttonMatrixState.B1) {
      currentOp = OP_SEQUENCER;
      break;
    }
    if (buttonMatrixState.B2) {
      currentOp = OP_SAMPLER;
      break;
    }
    waitForNoInput();
  }
}
