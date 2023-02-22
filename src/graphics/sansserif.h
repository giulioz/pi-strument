#ifndef SANSSERIF_H
#define SANSSERIF_H

#include "pico/stdlib.h"
#include "fonts.h"

const extern uint8_t sansserif_map[];
const extern CharInfo sansserif_chars[];

const int sansserif_baseIndex = 32;
const int sansserif_lineHeight = 36;
const int sansserif_base = 27;
const int sansserif_scaleW = 256;
const int sansserif_scaleH = 256;
const int sansserif_depth = 2;

#endif
