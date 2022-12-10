#ifndef SANSSERIF_H
#define SANSSERIF_H

#include "pico/stdlib.h"

typedef struct CharInfo {
  int id;
  int x;
  int y;
  int width;
  int height;
  int xoffset;
  int yoffset;
  int xadvance;
} CharInfo;

extern uint8_t sansserif_map[];
extern CharInfo sansserif_chars[];

const int sansserif_baseIndex = 32;
const int sansserif_lineHeight = 36;
const int sansserif_base = 27;
const int sansserif_scaleW = 256;
const int sansserif_scaleH = 256;

#endif
