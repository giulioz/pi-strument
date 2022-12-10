#ifndef BUTTONMATRIX_H
#define BUTTONMATRIX_H

typedef struct ButtonMatrixState {
  bool B0;
  bool B1;
  bool B2;
  bool B3;
  bool B4;
  bool B5;
  bool B6;
  bool B7;
  bool B8;
  bool ENCBtn;
} ButtonMatrixState;

extern ButtonMatrixState buttonMatrixState;

void initButtonMatrix();
void getButtonMatrix();

#endif
