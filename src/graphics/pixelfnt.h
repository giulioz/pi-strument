#ifndef PIXELFNT_H
#define PIXELFNT_H

#include "pico/stdlib.h"
#include "fonts.h"

const extern uint8_t pixelfnt_map[];
const extern CharInfo pixelfnt_chars[];

const int pixelfnt_baseIndex = 32;
const int pixelfnt_lineHeight = 9;
const int pixelfnt_base = 12;
const int pixelfnt_scaleW = 128;
const int pixelfnt_scaleH = 72;
const int pixelfnt_depth = 1;

#endif
