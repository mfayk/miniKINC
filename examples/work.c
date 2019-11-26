float* elem(float* matrix[], int i, int j)
{
	return matrix[i * 2 + j];
}





void matrixAddOuterProduct(float* matrix[], float c, float* vect)
{
	elem(matrix, 0, 0) += c * vect[0] * vect[0];
	elem(matrix, 0, 1) += c * vect[0] * vect[1];
	elem(matrix, 1, 0) += c * vect[1] * vect[0];
	elem(matrix, 1, 1) += c * vect[1] * vect[1];

}
