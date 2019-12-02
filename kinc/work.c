#include <stdio.h>

/*
float elem(float* mtx[], int i, int j)
{
	return *mtx[i * 2 + j];
}
*/

float **matrixAddOuterProductECC(float ***prod, float **mtx, float c, float **vect)
{
	float **tmp;
	


	return tmp;
}

void matrixAddOuterProduct(float ***mtx, float c, float *vect)
{
	(*mtx)[0][0] = (*mtx)[0][0] + c * vect[0] * vect[0];
	(*mtx)[0][1] = (*mtx)[0][1] + c * vect[0] * vect[1];
	(*mtx)[1][0] = (*mtx)[1][0] + c * vect[1] * vect[0];
	(*mtx)[1][1] = (*mtx)[1][1] + c * vect[1] * vect[1];
}
/*
void matrixAddOuterProduct(float ***mtx, float c, float **vect, int x, int y)
{
	int i = 0;
	int j = 0;
	//for(i=0; i<2; i++) {
	for(i=0; i<x; i++) {
		//for(j=0;j<2;j++) {
		for(j=0; j<y; j++) {
			(*mtx)[i][j] = (*mtx)[i][j] + c * (*vect)[i] * (*vect)[j];
		}
	}
//	(*mtx)[0][0] = (*mtx)[0][0] + c * (*vect)[0] * (*vect)[0];
//	(*mtx)[0][1] = (*mtx)[0][1] + c * (*vect)[0] * (*vect)[1];
//	(*mtx)[1][0] = (*mtx)[1][0] + c * (*vect)[1] * (*vect)[0];
//	(*mtx)[1][1] = (*mtx)[1][1] + c * (*vect)[1] * (*vect)[1];
}
*/
