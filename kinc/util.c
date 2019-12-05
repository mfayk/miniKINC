#include <stdio.h>
#include <stdlib.h>
#include "../sdecc/src/ecc.h"

void fill1D(float **vect, int len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		(*vect)[i] = 2.0;
//		(*vect)[i] = (float)rand()/RAND_MAX;
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

void free1DParity(Parity *par)
{
	free(par);
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
		(*par)[i] = ECC_Parity_get(c, vect[i]); }
}

void print1DParity(Parity *par, int len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		printf("%02llx ", par[i]);
	}
	printf("\n");
}

void alloc2DParity(Parity ***par, int rows, int cols)
{	
	int i;
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
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			printf("%02llx ", par[i][j]);
		}
		printf("\n");
	}
}

