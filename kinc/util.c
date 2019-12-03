#include <stdio.h>
#include <stdlib.h>
#include "../sdecc/src/ecc.h"

void fill1D(float **vect, int len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		(*vect)[i] = 2.0;
	}
}

void print1D(float *vect, int len)
{
	int i = 0;
	for(i = 0; i<len; i++) {
		printf("%f ", vect[i]);
	}
	printf("\n");
}

void set1D(float **vect, int len)
{
	*vect = malloc(sizeof(float) * len);
	fill1D(vect, len);
}

void alloc2D(float ***mtx, int rows, int cols)
{
	int i = 0;
	*mtx = malloc(sizeof(float*) * rows);
	*mtx[0] = malloc(sizeof(float) * rows * cols);
	for(i=0; i<rows; i++) {
		(*mtx)[i] = (**mtx + (cols * i));
	}
}

void free2D(float **mtx)
{
	free(*mtx);
	free(mtx);
}

void fill2D(float ***mtx, int rows, int cols)
{
	int i = 0;
	int j = 0;
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			//(*mtx)[i][j] = 10.5;	
			(*mtx)[i][j] = (float)rand()/RAND_MAX;
		}
	}
}

void set2D(float ***mtx, int rows, int cols)
{
	alloc2D(mtx, rows, cols);
	fill2D(mtx, rows, cols);
}

void fill2DZeros(float ***mtx, int rows, int cols)
{
	int i = 0;
	int j = 0;
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			(*mtx)[i][j] = 0;	
		}
	}
}

void print2D(float **mtx, int rows, int cols)
{
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			printf("%f ", mtx[i][j]);
		}
		printf("\n");
	}
}

/*
 * -----------------
 * CODEWORD MATRICES
 * -----------------
 */

/* Single Codewords */
void fillCW(Code *c, Codeword **cw, float val)
{
	Data dat = *(Data *)&val;
	*cw = ECC_Codeword_create(c, dat);
}

void checkCW(Code *c, Codeword *val)
{
	int res = 0;
	Syndrome syn = ECC_Codeword_detect(c, val);
	if(syn != 0) {
		printf("silent data corruption detected . . .\n");
		printf("corrupted value: ");
		ECC_Codeword_printData(val);
		printf("attempting to correct . . .\n");
		res = ECC_Codeword_correct(c, val, syn);	
	}
}

void printCW(Codeword *cw)
{
	printf("\n");
	ECC_Codeword_printData(cw);
	printf("\n");
}

/* 1D Codewords */
void alloc1DCW(Codeword ***vect, int len)
{
	*vect = malloc(sizeof(Codeword*) * len);
}

void free1DCW(Codeword ***vect, int rows)
{
	int i = 0;
	for(i=0; i<rows; i++) {
		ECC_Codeword_destroy((*vect)[i]);
	}
	free(*vect);
	free(vect);
}

void fill1DCW(Code *c, Codeword ***cw, float *vect, int len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		Data dat = *(Data *)&(vect[i]);
		(*cw)[i] = ECC_Codeword_create(c, dat);
	}
}

void check1DCW(Code *c, Codeword **vect, int len)
{
	int i = 0;
	Syndrome syn = 0;
	int res = 0;
	for(i=0; i<len; i++) {
		syn = ECC_Codeword_detect(c, vect[i]);
		if(syn != 0) {
			printf("silent data corruption detected . . .\n");
			printf("corrupted value: ");
			ECC_Codeword_printData(vect[i]);
			printf("attempting to correct . . .\n");
			res = ECC_Codeword_correct(c, vect[i], syn);	
		}
	}
}

void print1DCW(Codeword **cw, int len)
{
	int i = 0;
	printf("\n");
	for(i=0; i<len; i++) {
		ECC_Codeword_printData(cw[i]);
	}
	printf("\n");
}

/* 2D Codewords */
void alloc2DCW(Codeword ****mtx, int rows, int cols)
{
	int i = 0;
	*mtx = malloc(sizeof(Codeword**) * rows);
	*mtx[0] = malloc(sizeof(Codeword*) * rows * cols);
	for(i=0; i<rows; i++) {
		(*mtx)[i] = (**mtx + (cols * i));
	}
}

void free2DCW(Codeword ****cw, int rows, int cols)
{
	int i = 0;
	int j = 0;
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			ECC_Codeword_destroy((*cw)[i][j]);
		}
	}
	free(*cw);
	free(cw);
}

void fill2DCW(Code *c, Codeword ****cw, float **mtx, int rows, int cols)
{
	int i = 0;
	int j = 0;
	alloc2DCW(cw, rows, cols);
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			Data dat = *(Data *)&(mtx[i][j]); 
			(*cw)[i][j] = ECC_Codeword_create(c, dat);
		}
	}
}
void check2DCW(Code *c, Codeword ****cw, int x, int y)
{
	int i = 0;
	int j = 0;
	Syndrome syn = 0;
	int res = 0;
	for(i=0; i<x; i++) {
		for(j=0; j<y; j++) {
			syn = ECC_Codeword_detect(c, (*cw)[i][j]);
			if(syn != 0) {
				printf("silent data corruption detected . . .\n");
				printf("corrupted value: ");
				ECC_Codeword_printData((*cw)[i][j]);
				printf("attempting to correct . . .\n");
				res = ECC_Codeword_correct(c, (*cw)[i][j], syn);
			}
		}
	}

}

void print2DCW(Codeword ***cw, int rows, int cols)
{
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0; i<rows; i++) {
		for(j=0;j<cols;j++) {
			ECC_Codeword_printData(cw[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * ---------------
 * PARITY MATRICES
 * ---------------
 */
void freeParity(Parity *par)
{
	free(par);
}

void setParity(Code *c, Parity *par, float val)
{
	*par = ECC_Parity_get(c, val); 
}

void printParity(Parity par)
{
	printf("\n%02hhx\n", par);
}

void alloc1DParity(Parity **par, int len)
{
	*par = malloc(sizeof(Parity) * len);
}

void free1DParity(Parity **par)
{
	free(*par);
}

void fill1DParity(Code *c, Parity **par, float *vect, int len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		(*par)[i] = ECC_Parity_get(c, vect[i]);
	}
}

void set1DParity(Code *c, Parity **par, float *vect, int len)
{
	*par = malloc(sizeof(Parity) * len);
	int i;
	for(i=0; i<len; i++) {
		(*par)[i] = ECC_Parity_get(c, vect[i]);
	}
}

void print1DParity(Parity *par, int len)
{
	int i = 0;
	printf("\n");
	for(i=0; i<len; i++) {
		printf("%02llx ", par[i]);
	}
	printf("\n");
}

void alloc2DParity(Parity ***par, int rows, int cols)
{	
	int i = 0;
	*par = malloc(sizeof(Parity*) * rows);
	*par[0] = malloc(sizeof(Parity) * rows * cols);
	for(i=0; i<rows; i++) {
		(*par)[i] = (**par + (cols * i));
	}
}

void free2DParity(Parity **par)
{
	free(*par);
	free(par);
}

void fill2DParity(Code *c, Parity ***par, float **mtx, int rows, int cols)
{
	int i = 0;
	int j = 0;
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			(*par)[i][j] = ECC_Parity_get(c, mtx[i][j]);
		}
	}
}

void set2DParity(Code *c, Parity ***par, float **mtx, int rows, int cols)
{
	alloc2DParity(par, rows, cols);
	fill2DParity(c, par, mtx, rows, cols);
}

void print2DParity(Parity **par, int rows, int cols)
{
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			printf("%02llx ", par[i][j]);
		}
		printf("\n");
	}
}

