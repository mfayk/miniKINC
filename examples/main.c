
#include <stdio.h>
#include "/scratch1/mfaykus/FlipIt/include/FlipIt/corrupt/corrupt.h"

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
void matrixAddOuterProduct(float** matrix, float c, float* vect);


int main(int argc, char** argv)
{

	//create test case here
	
	int a = 4, b=3;
	int rank = 0;
	int seed = 7;

	int rows = 2;
	int cols = 2;	


	float** matrix;
	float* vect;
	
	int i=0;
	int j=0;
	printf("i= %d, j= %d\nvect= ",i,j);
	

	vect = malloc(rows * sizeof(vect));
	matrix = malloc(rows * sizeof(matrix));


	for(i=0;i<rows;i++){
		matrix[i] = malloc(cols * sizeof(matrix[i]));
	}
	



	for(i=0; i<2; i++) {
	vect[i] = 2;
		for(j=0;j<2;j++) {
			matrix[i][j] = 10.5;
			if(j==i){
				printf("\n");
				}
		}
	}
	printf("\n");
	for(i=0; i<2; i++) {
		j=0;
		for(j=0;j<2;j++) {
			printf("%f ", matrix[i][j]);
			if(j==1){
				printf("\n");
			}
		}
	}




	FLIPIT_Init(rank, argc, argv, seed);
 	
	printf("Should be corrupted: %d + %d = %d\n", a, b,b);
	for(i=0; i<2; i++) {
                j=0;
                for(j=0;j<2;j++) {
                        printf("%f ", matrix[i][j]);
                        if(j==1){
                                printf("\n");
                        }
                }
        }
	
	matrixAddOuterProduct(&matrix, 5, vect);


	FLIPIT_Finalize(NULL);
	
	//matrixAddOuterProduct(matrix,1,vect);	

	printf("test\n");


	return 0;
}
