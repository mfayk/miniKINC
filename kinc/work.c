#include <stdio.h>
#include <math.h>
#include "../sdecc/src/ecc.h"
#include "util.h"

void matrixAddOuterProduct(float ***mtx, float c, float **vect)
{
	(*mtx)[0][0] = (*mtx)[0][0] + c * (*vect)[0] * (*vect)[0];
	(*mtx)[0][1] = (*mtx)[0][1] + c * (*vect)[0] * (*vect)[1];
	(*mtx)[1][0] = (*mtx)[1][0] + c * (*vect)[1] * (*vect)[0];
	(*mtx)[1][1] = (*mtx)[1][1] + c * (*vect)[1] * (*vect)[1];
}

void matrixAddOuterProductECC(Code *c, float ***mtx, float val, float *vect, Parity **mtx_par, Parity val_par, Parity *vect_par)
{
	int i;
	int j;
	int res = 0;

	res = ECC_Parity_EDAC(c, &val_par, &val);
	if(res < 0) {
		printf("DUE encoutered. cannot correct.\n");
	}
	for(i=0; i<2; i++) {
		res = ECC_Parity_EDAC(c, &vect_par[i], &vect[i]);
		if(res < 0) {
			printf("DUE encoutered. cannot correct.\n");
		}
	}
	
	for(i=0; i<2; i++) {
		for(j=0; j<2; j++) {
			res = ECC_Parity_EDAC(c, &mtx_par[i][j], &(*mtx)[i][j]);
			if(res != 0) {
				printf("DUE encountered. cannot correct.\n");
			}
		}
	}
	(*mtx)[0][0] = (*mtx)[0][0] + val * vect[0] * vect[0];
	(*mtx)[0][1] = (*mtx)[0][1] + val * vect[0] * vect[1];
	(*mtx)[1][0] = (*mtx)[1][0] + val * vect[1] * vect[0];
	(*mtx)[1][1] = (*mtx)[1][1] + val * vect[1] * vect[1];
}


