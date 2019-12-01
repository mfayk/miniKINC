#include <stdio.h>
#include <stdlib.h>
//#include "/scratch1/mfaykus/FlipIt/include/FlipIt/corrupt/corrupt.h"
#include "/home/alpoulo/install/flipit-install/FlipIt/include/FlipIt/corrupt/corrupt.h"
#include "../sdecc/src/ecc.h"

void alloc2D(float ***mtx, int rows, int cols)
{
	int i = 0;
	*mtx = malloc(sizeof(float*) * rows);
	*mtx[0] = malloc(sizeof(float) * rows * cols);
	for(i=0; i<rows; i++) {
		(*mtx)[i] = (**mtx + (cols * i));
	}
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

void alloc2DCW(Codeword ****mtx, int rows, int cols)
{
	int i = 0;
	*mtx = malloc(sizeof(Codeword**) * rows);
	*mtx[0] = malloc(sizeof(Codeword*) * rows * cols);
	for(i=0; i<rows; i++) {
		(*mtx)[i] = (**mtx + (cols * i));
	}
}

void alloc2DSyndrome(Syndrome ***syn, int x, int y)
{
	int i = 0;
	*syn = malloc(sizeof(Syndrome *) * x);
	*syn[0] = malloc(sizeof(Syndrome) * x * y);
	for(i=0; i<x; i++) {
		(*syn)[i] = (**syn + (x * i));
	}
}

void free2D(float **mtx)
{
	free(*mtx);
	free(mtx);
}

void free2DParity(Parity **par)
{
	free(*par);
	free(par);
}

void free2DSyndrome(Syndrome **syn)
{
	free(*syn);
	free(syn);
}

void free2DCW(Codeword ****cw)
{
	//TODO
}

void fill1D(float **vect, int len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		(*vect)[i] = 2.0;
	}
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

void fill2DParity(Code *c, Parity ***par, float **mtx, int rows, int cols)
{
	alloc2DParity(par, rows, cols);
	int i = 0;
	int j = 0;
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			(*par)[i][j] = ECC_Parity_get(c, mtx[i][j]);
		}
	}
}

void fill2DSyndrome(Syndrome ***syn, Parity **org, Parity **corr, int x, int y)
{
	alloc2DSyndrome(syn, x, y);
	int i = 0;
	int j = 0;
	for(i=0; i<x; i++) {
		for(j=0; j<y; j++) {
			(*syn)[i][j] = (Syndrome)(org[i][j] ^ corr[i][j]);
		}
	}
}

void fill2DCW(Code *c, Codeword ****cw, float **mtx, int rows, int cols)
{
	int i = 0;
	int j = 0;
	alloc2DCW(cw, rows, cols);
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			(*cw)[i][j] = ECC_Codeword_create(c, (Data) mtx[i][j]);
		}
	}
}

void print1D(float *vect, int len)
{
	int i = 0;
	printf("\n");
	for(i = 0; i<len; i++) {
		printf("%f ", vect[i]);
	}
	printf("\n");
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
	printf("\n");
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
	printf("\n");
}

void print2DSyndrome(Syndrome **syn, int rows, int cols)
{
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			printf("%02llx ", syn[i][j]);			
		}
		printf("\n");
	}
	printf("\n");
}



