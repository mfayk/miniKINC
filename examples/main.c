
#include <stdio.h>
#include <stdlib.h>
//#include "/scratch1/mfaykus/FlipIt/include/FlipIt/corrupt/corrupt.h"
#include "/home/alpoulo/install/flipit-install/FlipIt/include/FlipIt/corrupt/corrupt.h"

/*
#include <signal.h>
int GLOBAL_TIMESTEP = 0;
void sigHandler(int sig)
{
 printf("Receiving Sig %d\n", sig);
 unsigned long long t = FLIPIT_GetExecutedInstructionCount();
 int r;
 MPI_Comm_rank(MPI_COMM_WORLD, &r);
 printf("Rank %d: Total Insts executed = %llu\n", r,
FLIPIT_GetExecutedInstructionCount());
 exit(sig);
}
void hpccgLogger(FILE* outfile)
{
 int r;
 MPI_Comm_rank(MPI_COMM_WORLD, &r);
 fprintf(outfile, "\nRank %d: Injection in Iteration = %d\n", r,
GLOBAL_TIMESTEP);
 unsigned long long t = FLIPIT_GetExecutedInstructionCount();
 fprintf(outfile, "Rank %d: Total Insts executed = %llu\n", r, t);
}
*/


//float **elem(float*  matrix[], int i, int j);
void matrixAddOuterProduct(float ***matrix, float c, float **vect);


void alloc2D(float ***mtx, int rows, int cols)
{
	int i = 0;
	*mtx = malloc(sizeof(float*) * rows);
	*mtx[0] = malloc(sizeof(float) * rows * cols);
	for(i=0; i<rows; i++) {
		(*mtx)[i] = (**mtx + (cols * i));
	}
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
			(*mtx)[i][j] = 10.5;	
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
}



int main(int argc, char** argv)
{
	srand(time(NULL));
	//create test case here
	
	int rank = 1;
//	int seed = 29678;
	int seed = rand();

	int rows = 2;
	int cols = 2;	


	float **matrix;
	float *vect;
	
	int i=0;
	int j=0;

	vect = malloc(rows * sizeof(vect));
	alloc2D(&matrix, rows, cols);
	
	fill1D(&vect, rows);	
	fill2D(&matrix, rows, cols); 
	
	print1D(vect, rows);
	print2D(matrix, rows, cols); 

	FLIPIT_Init(rank, argc, argv, seed);	
	matrixAddOuterProduct(&matrix, 5, &vect);
	FLIPIT_Finalize(NULL);

	print1D(vect, rows);
	print2D(matrix, rows, cols);


	return 0;
}
