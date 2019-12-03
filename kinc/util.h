#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../sdecc/src/ecc.h"

typedef struct parities_t Parities;

struct parities_t {
	Parity cval;
	Parity *vect;
	Parity **mtx;
};

void set1D(float **, int);
void set2D(float ***, int, int);

void setParity(Code *, Parity *, float);
void set1DParity(Code *, Parity **, float *, int);
void set2DParity(Code *, Parity ***, float **, int, int);

void alloc1DCW(Codeword ***, int);
void alloc2DCW(Codeword ****, int, int);

void free2D(float **);
void free2DCW(Codeword ****cw);
void free2DParity(Parity **);

void fill2DZeros(float ***, int, int);

void fillCW(Code *, Codeword **, float);
void fill1DCW(Code *, Codeword ***, float *, int);

void fillParity(Code *, Parity *, float);
void fill1DParity(Code *, Parity **, float *, int);
void fill2DParity(Code *, Parity ***, float **, int, int);
void fill2DSyndrome(Syndrome ***, Parity **, Parity **, int, int);
void fill2DCW(Code *, Codeword ****, float **, int, int);


void print1D(float *, int);
void print2D(float **, int, int);

void printParity(Parity);
void print1DParity(Parity *, int);
void print2DParity(Parity **, int, int);
void print2DSyndrome(Syndrome **, int, int);
void printCW(Codeword *);
void print1DCW(Codeword **, int);
void print2DCW(Codeword ***, int, int);

void checkCW(Code *, Codeword *);
void check1DCW(Code *, Codeword **, int);
void check2DCW(Code *, Codeword ****, int, int);


#endif
