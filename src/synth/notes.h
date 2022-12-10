#ifndef NOTES_H
#define NOTES_H

// Taken from http://www.phy.mtu.edu/~suits/notefreqs.html
// Rounded to nearest number
// Format: <note><octave>(sharp/flat)
//    Ex: C5S = C# note in 5th octave
#define NOTE_C0 16
#define NOTE_C0S 17
#define NOTE_D0F NOTE_C0S
#define NOTE_D0 18
#define NOTE_D0S 19
#define NOTE_E0F NOTE_D0S
#define NOTE_E0 21
#define NOTE_F0 22
#define NOTE_F0S 23
#define NOTE_G0F NOTE_F0S
#define NOTE_G0 25
#define NOTE_G0S 26
#define NOTE_A0F NOTE_G0S
#define NOTE_A0 28
#define NOTE_A0S 29
#define NOTE_B0F NOTE_A0S
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_C1S 35
#define NOTE_D1F NOTE_C1S
#define NOTE_D1 37
#define NOTE_D1S 39
#define NOTE_E1F NOTE_D1S
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_F1S 46
#define NOTE_G1F NOTE_F1S
#define NOTE_G1 49
#define NOTE_G1S 52
#define NOTE_A1F NOTE_G1S
#define NOTE_A1 55
#define NOTE_A1S 58
#define NOTE_B1F NOTE_A1S
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_C2S 69
#define NOTE_D2F NOTE_C2S
#define NOTE_D2 73
#define NOTE_D2S 78
#define NOTE_E2F NOTE_D2S
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_F2S 93
#define NOTE_G2F NOTE_F2S
#define NOTE_G2 98
#define NOTE_G2S 104
#define NOTE_A2F NOTE_G2S
#define NOTE_A2 110
#define NOTE_A2S 117
#define NOTE_B2F NOTE_A2S
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_C3S 139
#define NOTE_D3F NOTE_C3S
#define NOTE_D3 147
#define NOTE_D3S 156
#define NOTE_E3F NOTE_D3S
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_F3S 185
#define NOTE_G3F NOTE_F3S
#define NOTE_G3 196
#define NOTE_G3S 208
#define NOTE_A3F NOTE_G3S
#define NOTE_A3 220
#define NOTE_A3S 233
#define NOTE_B3F NOTE_A3S
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_C4S 277
#define NOTE_D4F NOTE_C4S
#define NOTE_D4 294
#define NOTE_D4S 311
#define NOTE_E4F NOTE_D4S
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_F4S 370
#define NOTE_G4F NOTE_F4S
#define NOTE_G4 392
#define NOTE_G4S 412
#define NOTE_A4F NOTE_G4S
#define NOTE_A4 440
#define NOTE_A4S 466
#define NOTE_B4F NOTE_A4S
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_C5S 554
#define NOTE_D5F NOTE_C5S
#define NOTE_D5 587
#define NOTE_D5S 622
#define NOTE_E5F NOTE_D5S
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_F5S 740
#define NOTE_G5F NOTE_F5S
#define NOTE_G5 784
#define NOTE_G5S 830
#define NOTE_A5F NOTE_G5S
#define NOTE_A5 880
#define NOTE_A5S 932
#define NOTE_B5F NOTE_A5S
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_C6S 1109
#define NOTE_D6F NOTE_C6S
#define NOTE_D6 1175
#define NOTE_D6S 1245
#define NOTE_E6F NOTE_D6S
#define NOTE_E6 1318
#define NOTE_F6 1397
#define NOTE_F6S 1480
#define NOTE_G6F NOTE_F6S
#define NOTE_G6 1568
#define NOTE_G6S 1661
#define NOTE_A6F NOTE_G6S
#define NOTE_A6 1760
#define NOTE_A6S 1865
#define NOTE_B6F NOTE_A6S
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_C7S 2217
#define NOTE_D7F NOTE_C7S
#define NOTE_D7 2349
#define NOTE_D7S 2489
#define NOTE_E7F NOTE_D7S
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_F7S 2960
#define NOTE_G7F NOTE_F7S
#define NOTE_A7 3520
#define NOTE_A7S 3729
#define NOTE_B7F NOTE_A7S
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_C8S 4435
#define NOTE_D8F NOTE_C8S
#define NOTE_D8 4699
#define NOTE_D8S 4978
#define NOTE_E8F NOTE_D8S
#define NOTE_E8 5274
#define NOTE_F8 5588
#define NOTE_F8S 5920
#define NOTE_G8F NOTE_F8S
#define NOTE_G8 6272
#define NOTE_G8S 6645
#define NOTE_A8 7040
#define NOTE_A8S 7459
#define NOTE_B8F NOTE_A8S
#define NOTE_B8 7902

// Note macros for the lazy
#define NOTE_WHOLE 1
#define NOTE_HALF 0.5
#define NOTE_QUATER 0.25
#define NOTE_EIGHTH 0.125
#define NOTE_SIXTEENTH 0.0625
#define NOTE_THIRTY_SECOND 0.03125
#define NOTE_SIXTY_FOURTH 0.015625

/// Note-to-Milliseconds (at given tempo)
/// @param Note:
///   * Whole note is 1
///   * Half note is 0.5
///   * Quater note is 0.25
///   ...
///   * 1/(2^(Note))
/// @return:
///   An integer millisecond value
#define NTM(note, tempo) ((240000 / tempo) / note)

#endif
