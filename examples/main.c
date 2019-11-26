
#include <stdio.h>
#include "/scratch1/mfaykus/FlipIt/include/FlipIt/corrupt/corrupt.h"


float elem(float*  matrix[], int i, int j);
void matrixAddOuterProduct(float* matrix[], float c, float* vect);


int main(int argc, char** argv)
{

	//create test case here
	
	int a = 4, b=3;
	int rank = 0;
	int seed = 7;

	float matrix[2][2];
	float vect[2];
	
	int i, j;
	for(i=0; i<2; i++) {
	vect[i] = 1;
		for(j=0;j<2;j++) {
			matrix[i][j] = 1;
		}
	}


	FLIPIT_Init(rank, argc, argv, seed);
 	printf("Should be corrupted: %d + %d = %d\n", a, b,b);
//	matrixAddOuterProduct(matrix, 1, vect);
	FLIPIT_Finalize(NULL);
	
	matrixAddOuterProduct(matrix,1,vect);	

	return 0;
}
