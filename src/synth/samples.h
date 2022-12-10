#ifndef SAMPLES_H
#define SAMPLES_H

#include "pico/stdlib.h"

const extern uint8_t samples_raw[];
const int samples_length = 0x80000;

struct SampleInfo {
  uint8_t pos;
  uint8_t len;
  uint16_t pitch;
};

const SampleInfo samples_info[] = {
  {0x60, 0x10, 0x5000},
  {0x6E, 0x00, 0x5000},
  {0x44, 0x20, 0x5000},
  {0x20, 0x20, 0x5000},
  {0x28, 0x20, 0x5000},
  {0x24, 0x20, 0x5000},
  {0x40, 0x20, 0x46A5},
  {0x00, 0x30, 0x5000},
  {0x08, 0x30, 0x5000},
  {0x2C, 0x20, 0x5000},
  {0x50, 0xA0, 0x5000},
  {0x18, 0x30, 0x5000},
  {0x5C, 0xA0, 0x5000},
  {0x10, 0x30, 0x5000},
  {0x58, 0xA0, 0x5000},
  {0x30, 0x20, 0x5000},
  {0x34, 0x20, 0x5000},
  {0x54, 0xA0, 0x5000},
  {0x6F, 0x00, 0x5000},
  {0x68, 0x10, 0x5000},
  {0x6C, 0x00, 0x5000},
  {0x48, 0x20, 0x5000},
  {0x6D, 0x00, 0x5000},
  {0x66, 0x10, 0x5000},
  {0x62, 0x10, 0x5000},
  {0x64, 0x10, 0x5000},
  {0xD2, 0x00, 0x5000},
  {0x38, 0x20, 0x5000},
  {0x3C, 0x20, 0x5000},
  {0x6A, 0x10, 0x5000},
  {0x4C, 0x20, 0x5000},
  {0x70, 0x30, 0x5000},
  {0x80, 0x30, 0x52AB},
  {0x88, 0x30, 0x3D4B},
  {0x9C, 0x10, 0x4000},
  {0x9E, 0x10, 0x414C},
  {0xA0, 0x10, 0x4540},
  {0xD3, 0x00, 0x5082},
  {0xA2, 0x10, 0x4125},
  {0xA4, 0x10, 0x5126},
  {0xA6, 0x10, 0x54CA},
  {0xA8, 0x10, 0x518F},
  {0xAA, 0x10, 0x50C9},
  {0xD4, 0x00, 0x40F3},
  {0x9A, 0x10, 0x48C3},
  {0xAC, 0x10, 0x47CD},
  {0xAE, 0x10, 0x53C3},
  {0xB0, 0x10, 0x50C3},
  {0xD5, 0x00, 0x4283},
  {0xB2, 0x10, 0x5253},
  {0xDA, 0x00, 0x5165},
  {0xB4, 0x10, 0x33BE},
  {0x98, 0x10, 0x4711},
  {0xD6, 0x00, 0x4C11},
  {0xD7, 0x00, 0x40C3},
  {0xD8, 0x00, 0x40C3},
  {0xD9, 0x00, 0x410B},
  {0x90, 0x20, 0x4BA9},
  {0x94, 0x20, 0x63C6},
  {0xB6, 0x10, 0x6ABB},
  {0xB8, 0x10, 0x510E},
  {0xBA, 0x10, 0x4E74},
  {0xBC, 0x10, 0x60F6},
  {0xBE, 0x10, 0x4D2E},
  {0xC0, 0x10, 0x4D4F},
  {0xC2, 0x10, 0x484C},
  {0xC4, 0x10, 0x4D6A},
  {0xC6, 0x10, 0x5123},
  {0xC8, 0x10, 0x5101},
  {0xCA, 0x10, 0x58F4},
  {0xCC, 0x10, 0x5080},
  {0xCE, 0x10, 0x4177},
  {0xD0, 0x10, 0x4A76},
  {0xDB, 0x80, 0x6111},
  {0xDC, 0x80, 0x6111},
  {0xDD, 0x80, 0x6111},
  {0xDE, 0x80, 0x6111},
  {0xDF, 0x80, 0x6111},
  {0xE0, 0x80, 0x5111},
  {0xE1, 0x80, 0x5111},
  {0xE2, 0x80, 0x6111},
  {0xE3, 0x80, 0x7111},
  {0xE4, 0x80, 0x5111},
  {0xE5, 0x80, 0x6111},
  {0xE6, 0x80, 0x6111},
  {0xE7, 0x80, 0x7111},
  {0xE8, 0x80, 0x7111},
  {0xE9, 0x80, 0x6111},
  {0xEA, 0x80, 0x5111},
  {0xEB, 0x80, 0x7111},
  {0xEC, 0x80, 0x6111},
  {0xED, 0x80, 0x5111},
  {0xEE, 0x80, 0x4111},
  {0xEF, 0x80, 0x56C4},
  {0xF0, 0x80, 0x6111},
  {0xF1, 0x80, 0x5111},
  {0xF2, 0x80, 0x5111},
  {0xF3, 0x80, 0x5111},
  {0xF4, 0x80, 0x6111},
  {0xF5, 0x80, 0x6111},
  {0xF6, 0x80, 0x4111},
  {0xF7, 0x80, 0x4111},
  {0xF8, 0x80, 0x4111},
  {0xF9, 0x80, 0x4111},
  {0xFA, 0x80, 0x4111},
  {0xFB, 0x80, 0x4111},
  {0xFC, 0x80, 0x4111},
  {0xFD, 0x80, 0x4111},
  {0xFE, 0x80, 0x4111},
  {0xFF, 0x80, 0x4111},
  {0x78, 0xB0, 0x5111},
  {0x2A, 0x10, 0x5000},
  {0x26, 0x10, 0x5000},
  {0x04, 0x20, 0x5000},
  {0x2E, 0x10, 0x5000},
  {0x1C, 0x20, 0x5000},
  {0x69, 0x00, 0x5000},
  {0x63, 0x00, 0x5000},
  {0x6B, 0x00, 0x5000},
  {0x74, 0x20, 0x5000},
  {0x84, 0x20, 0x52AB},
  {0x8C, 0x20, 0x3D4B},
  {0x9D, 0x00, 0x4000},
  {0xA5, 0x00, 0x5126},
  {0xB7, 0x00, 0x6ABB},
  {0xBD, 0x00, 0x60F6},
  {0xC1, 0x00, 0x4D4F},
  {0xCF, 0x00, 0x4177},
  {0x60, 0x11, 0x5000},
  {0x6E, 0x01, 0x5000},
  {0x44, 0x21, 0x5000},
  {0x20, 0x21, 0x5000},
  {0x28, 0x21, 0x5000},
  {0x24, 0x21, 0x5000},
  {0x40, 0x21, 0x46A5},
  {0x00, 0x31, 0x5000},
  {0x08, 0x31, 0x5000},
  {0x2C, 0x21, 0x5000},
  {0x50, 0xA1, 0x5000},
  {0x18, 0x31, 0x5000},
  {0x5C, 0xA1, 0x5000},
  {0x10, 0x31, 0x5000},
  {0x58, 0xA1, 0x5000},
  {0x30, 0x21, 0x5000},
  {0x34, 0x21, 0x5000},
  {0x54, 0xA1, 0x5000},
  {0x6F, 0x01, 0x5000},
  {0x68, 0x11, 0x5000},
  {0x6C, 0x01, 0x5000},
  {0x48, 0x21, 0x5000},
  {0x6D, 0x01, 0x5000},
  {0x66, 0x11, 0x5000},
  {0x62, 0x11, 0x5000},
  {0x64, 0x11, 0x5000},
  {0xD2, 0x01, 0x5000},
  {0x38, 0x21, 0x5000},
  {0x3C, 0x21, 0x5000},
  {0x6A, 0x11, 0x5000},
  {0x60, 0x90, 0x5000},
  {0x6E, 0x80, 0x5000},
  {0x20, 0xA0, 0x5000},
  {0x28, 0xA0, 0x5000},
  {0x40, 0xA0, 0x5000},
  {0x08, 0xB0, 0x5000},
  {0x2C, 0xA0, 0x5000},
  {0x18, 0xA0, 0x5000},
  {0x10, 0xA0, 0x5000},
  {0x30, 0xA0, 0x5000},
  {0x30, 0x90, 0x5000},
  {0x34, 0xA0, 0x5000},
  {0x6F, 0x80, 0x5000},
  {0x68, 0x90, 0x5000},
  {0x68, 0x80, 0x5000},
  {0x6C, 0x80, 0x5000},
  {0x48, 0x90, 0x5000},
  {0x6D, 0x80, 0x5000},
  {0x66, 0x90, 0x5000},
  {0x62, 0x90, 0x5000},
  {0x63, 0x80, 0x5000},
  {0x64, 0x90, 0x5000},
  {0xD2, 0x80, 0x5000},
  {0x38, 0xA0, 0x5000},
  {0x3C, 0xA0, 0x5000},
  {0x6A, 0x90, 0x5000},
  {0x6A, 0x80, 0x5000},
  {0x4C, 0xA0, 0x5000},
  {0x9C, 0x90, 0x5000},
  {0x9E, 0x90, 0x5000},
  {0xA0, 0x90, 0x5000},
  {0xD3, 0x80, 0x5000},
  {0xA2, 0x90, 0x5000},
  {0xD4, 0x80, 0x5000},
  {0x9A, 0x90, 0x5000},
  {0xA4, 0x90, 0x5000},
  {0xA6, 0x90, 0x5000},
  {0xAA, 0x90, 0x5000},
  {0xAC, 0x90, 0x5000},
  {0xAE, 0x90, 0x5000},
  {0xB0, 0x90, 0x5000},
  {0xD5, 0x80, 0x5000},
  {0xB4, 0x90, 0x5000},
  {0xD6, 0x80, 0x5000},
  {0xD7, 0x80, 0x5000},
  {0xD8, 0x80, 0x5000},
  {0xD9, 0x80, 0x5000},
  {0x90, 0xA0, 0x5000},
  {0x94, 0xA0, 0x5000},
  {0xB6, 0x90, 0x5000},
  {0xB8, 0x90, 0x5000},
  {0xBA, 0x90, 0x5000},
  {0xDA, 0x80, 0x5000},
  {0xBC, 0x90, 0x5000},
  {0x98, 0x90, 0x5000},
  {0xBE, 0x90, 0x5000},
  {0xC0, 0x90, 0x5000},
  {0xC2, 0x90, 0x5000},
  {0xC4, 0x90, 0x5000},
  {0xC6, 0x90, 0x5000},
  {0xC8, 0x90, 0x5000},
  {0xCA, 0x90, 0x5000},
  {0xCC, 0x90, 0x5000},
  {0xD0, 0x90, 0x5000},
  {0x60, 0xC0, 0x5000},
  {0xA0, 0xC0, 0x5000},
  {0xB0, 0xC0, 0x5000},
  {0xC0, 0xC0, 0x5000},
  {0xD0, 0xC0, 0x5000},
  {0xE0, 0xC0, 0x5000},
  {0x60, 0xB0, 0x5000},
  {0x68, 0xB0, 0x5000},
  {0x98, 0xB0, 0x5000},
  {0xA0, 0xB0, 0x5000},
  {0xB0, 0xB0, 0x5000},
  {0xC0, 0xB0, 0x5000},
  {0xC8, 0xB0, 0x5000},
  {0xD0, 0xB0, 0x5000},
  {0xE0, 0xB0, 0x5000},
  {0xE8, 0xB0, 0x5000},
  {0xF0, 0xB0, 0x5000},
  {0xB8, 0xB0, 0x5000},
  {0xD8, 0xB0, 0x5000},
  {0xF8, 0xB0, 0x5000},
  {0x6C, 0xA0, 0x5000},
  {0xD0, 0xA0, 0x5000},
  {0xD4, 0xA0, 0x5000},
  {0xD8, 0xA0, 0x5000},
  {0xDC, 0xA0, 0x5000},
  {0xE0, 0xA0, 0x5000},
  {0xE4, 0xA0, 0x5000},
  {0xE8, 0xA0, 0x5000},
  {0xEC, 0xA0, 0x5000},
  {0xF0, 0xA0, 0x5000},
  {0xF4, 0xA0, 0x5000},
  {0xF8, 0xA0, 0x5000},
  {0xF2, 0x90, 0x5000},
  {0xF4, 0x90, 0x5000}
};

const char samples_name[] ="BsDrum1 BsDrum2 BsDrum3 Snare 1 Snare 2 Snare 3 Snare 4 TomTom1 TomTom2 HiHat   HiHatLp Crash   CrashLp Ride    Ride Lp Cup     China   ChinaLp RimShot Clap    MtHCnga Conga   Bongo   Cowbell Tambrin Agogo   Claves  HiTimbl LoTimbl Cabasa  TimpAtakTimpani AcPianoHAcPianoLPf ThumpOrgnPercTrumpet Lips    TromboneClarinetFlute HiFlute LoSteamer IndFluteBreath  Vibe Hi Vibe LowMarimba Xylo Hi Xylo LowKalimba WindBellChimeBarHammer  Guiro   Chink   Nails   FretlsBsPullBassSlapBassThmpBassAcouBassElecBassGut Gtr SteelGtrDirtyGtrPizzcatoHarp    CntrbassCello   Violin 1Violin 2Koto    DrawbrLpHiOrgnLpLoOrgnLpTrumptLpTrboneLpSax Lp1 Sax Lp2 Reed Lp SlapBsLpAcBassLpEBassLp1EBassLp2GutGtrLpStlGtrLpEleGtrLpClav Lp Cello LpViolinLpEPianLp1EPianLp2HrpsiLp1HrpsiLp2TelephonFemalLp1FemalLp2Male Lp1Male Lp2Spctrm 1Spctrm 2Spctrm 3Spctrm 4Spctrm 5Spctrm 6Spctrm 7Spctrm 8Spctrm 9Spctrm10Noise   Shot   1Shot   2Shot   3Shot   4Shot   5Shot   6Shot   7Shot   8Shot   9Shot  10Shot  11Shot  12Shot  13Shot  14Shot  15Shot  16Shot  17BsDrum1*BsDrum2*BsDrum3*Snare 1*Snare 2*Snare 3*Snare 4*TomTom1*TomTom2*HiHat  *HiHatLp*Crash  *CrashLp*Ride   *Ride Lp*Cup    *China  *ChinaLp*RimShot*Clap   *MtHCnga*Conga  *Bongo  *Cowbell*Tambrin*Agogo  *Claves *HiTimbl*LoTimbl*Cabasa *Loop   1Loop   2Loop   3Loop   4Loop   5Loop   6Loop   7Loop   8Loop   9Loop  10Loop  11Loop  12Loop  13Loop  14Loop  15Loop  16Loop  17Loop  18Loop  19Loop  20Loop  21Loop  22Loop  23Loop  24Loop  25Loop  26Loop  27Loop  28Loop  29Loop  30Loop  31Loop  32Loop  33Loop  34Loop  35Loop  36Loop  37Loop  38Loop  39Loop  40Loop  41Loop  42Loop  43Loop  44Loop  45Loop  46Loop  47Loop  48Loop  49Loop  50Loop  51Loop  52Loop  53Loop  54Loop  55Loop  56Loop  57Loop  58Loop  59Loop  60Loop  61Loop  62Loop  63Loop  64JamLp  1JamLp  2JamLp  3JamLp  4JamLp  5JamLp  6JamLp  7JamLp  8JamLp  9JamLp 10JamLp 11JamLp 12JamLp 13JamLp 14JamLp 15JamLp 16JamLp 17JamLp 18JamLp 19JamLp 20JamLp 21JamLp 22JamLp 23JamLp 24JamLp 25JamLp 26JamLp 27JamLp 28JamLp 29JamLp 30JamLp 31JamLp 32JamLp 33JamLp 34";

#endif