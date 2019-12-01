#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include "../sdecc/src/ecc.h"

void alloc2D(float ***, int, int);
void alloc2DParity(Parity ***, int, int);
void alloc2DCW(Codeword ****, int, int);

void free2D(float **);
void free2DParity(Parity **);

void fill1D(float **, int);
void fill2D(float ***, int, int);
void fill2DParity(Code *, Parity ***, float **, int, int);
void fill2DSyndrome(Syndrome ***, Parity **, Parity **, int, int);
void fill2DCW(Code *, Codeword ****, float **, int, int);

void print1D(float *, int);
void print2D(float **, int, int);
void print2DParity(Parity **, int, int);
void print2DSyndrome(Syndrome **, int, int);

#endif
