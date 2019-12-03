#include <stdio.h>
#include <math.h>
#include "../sdecc/src/ecc.h"
#include "util.h"

void matrixAddOuterProduct(float ***mtx, float c, float **vect)
{
	printf("\nc: %f\n", c);
	(*mtx)[0][0] = (*mtx)[0][0] + c * (*vect)[0] * (*vect)[0];
	(*mtx)[0][1] = (*mtx)[0][1] + c * (*vect)[0] * (*vect)[1];
	(*mtx)[1][0] = (*mtx)[1][0] + c * (*vect)[1] * (*vect)[0];
	(*mtx)[1][1] = (*mtx)[1][1] + c * (*vect)[1] * (*vect)[1];
}

void matrixAddOuterProductECC(Code *c, Parities **pars, float ***mtx, float val, 
							  float *vect)
{
	int i;
	int j;
	
	printf("\nreceived values:\n\n");
	
	printf("cval:\n%f\n", val);
	printf("\nvect:\n");
	print1D(vect, 2);
	printf("\nmatrix:");
	print2D(*mtx, 2, 2);
	printf("\n");
	printf("checking for errors . . .\n\n");
	
	ECC_Parity_EDAC(c, &((*pars)->cval), &val);

	for(i=0; i<2; i++) {
		ECC_Parity_EDAC(c, &((*pars)->vect[i]), &vect[i]);
	}

	for(i=0; i<2; i++) {
		for(j=0; j<2; j++) {
			/* something weird is happening here . . . */
//			ECC_Parity_EDAC(c, &((*pars)->mtx[i][j]), mtx[i][j]); 
		}
	}

	(*mtx)[0][0] = (*mtx)[0][0] + val * vect[0] * vect[0];
	(*mtx)[0][1] = (*mtx)[0][1] + val * vect[0] * vect[1];
	(*mtx)[1][0] = (*mtx)[1][0] + val * vect[1] * vect[0];
	(*mtx)[1][1] = (*mtx)[1][1] + val * vect[1] * vect[1];
}

