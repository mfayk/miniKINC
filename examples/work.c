#include <stdio.h>

/*
float elem(float* matrix[], int i, int j)
{
	return *matrix[i * 2 + j];
}
*/




void matrixAddOuterProduct(float** matrix, float c, float* vect)
{
	int i,j;
	for( i=0; i<2; i++) {
                j=0;
                for(j=0;j<2;j++) {
                        printf("%f ", matrix[i][j]);
                        if(j==1){
                                printf("\n");
                        }
                }
        }
	matrix[0][0] = matrix[0][0] + c * vect[0] * vect[0];
	matrix[0][1] = matrix[0][1] + c * vect[0] * vect[1];
	matrix[1][0] = matrix[1][0] + c * vect[1] * vect[0];
	matrix[1][1] = matrix[1][1] + c * vect[1] * vect[1];

}
