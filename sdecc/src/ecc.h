#ifdef __cplusplus
extern "C" {
#endif

#ifndef ECC_H
#define ECC_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <inttypes.h>

typedef struct codeword_t Codeword;
typedef uint8_t Parity;
typedef uint32_t Data;
//typedef uint64_t Data;
typedef uint8_t Syndrome;
typedef struct code_t Code;
typedef struct ecc_lut_t ECC_LUT;

struct ecc_lut_t {
    Syndrome *syn;
    Codeword **cw;
};

struct codeword_t {
    Data dat;
    Parity par;
};

struct code_t { 
	int n; 
	int k; 
	uint8_t p_bits; 
	Data *matrix; 
	char *scheme;
    ECC_LUT *lut;
};

Code *ECC_Code_create(int, int, char *);
void ECC_Code_destroy(Code *);
Parity ECC_Parity_get(Code *, float);
Codeword *ECC_Codeword_create(Code *, Data);
Syndrome ECC_Codeword_detect(Code *, Codeword *);
int ECC_Codeword_correct(Code *, Codeword *, Syndrome);
void ECC_Codeword_print(Codeword *cw);
void ECC_Codeword_destroy(Codeword *);
#endif

#ifdef __cplusplus
}
#endif
