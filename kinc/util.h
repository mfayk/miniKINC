#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../sdecc/src/ecc.h"

typedef struct parities_t Parities;

void set1D(float **, int);
void set2D(float ***, int, int);

void setParity(Code *, Parity *, float);
void set1DParity(Code *, Parity **, float *, int);
void set2DParity(Code *, Parity ***, float **, int, int);

void free2D(float **);
void free1DParity(Parity *);
void free2DParity(Parity **);

void fill2DZeros(float ***, int, int);

void fillCW(Code *, Codeword **, float);
void fill1DCW(Code *, Codeword ***, float *, int);

void fillParity(Code *, Parity *, float);
void fill1DParity(Code *, Parity **, float *, int);
void fill2DParity(Code *, Parity ***, float **, int, int);

void print1D(float *, int);
void print2D(float **, int, int);

void printParity(Parity);
void print1DParity(Parity *, int);
void print2DParity(Parity **, int, int);

#endif
