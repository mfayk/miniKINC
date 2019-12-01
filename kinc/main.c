
//#include "/scratch1/mfaykus/FlipIt/include/FlipIt/corrupt/corrupt.h"
//#include "/home/alpoulo/install/flipit-install/FlipIt/include/FlipIt/corrupt/corrupt.h"
#include "FlipIt/corrupt/corrupt.h"
#include <signal.h>
#include "../sdecc/src/ecc.h"
#include "util.h"


int GLOBAL_TIMESTEP = 0;

void sigHandler(int sig)
{
	printf("Receiving Sig %d\n", sig);
	unsigned long long t = FLIPIT_GetExecutedInstructionCount();
	int r;
//	MPI_Comm_rank(MPI_COMM_WORLD, &r);
//	printf("Rank %d: Total Insts executed = %llu\n", r, FLIPIT_GetExecutedInstructionCount());
	printf("Total Insts executed = %llu\n", FLIPIT_GetExecutedInstructionCount());
	exit(sig);
}
void mtxProductLogger(FILE* outfile)
{
	int r;
//	MPI_Comm_rank(MPI_COMM_WORLD, &r);
//	fprintf(outfile, "\nRank %d: Injection in Iteration = %d\n", r, GLOBAL_TIMESTEP);
	fprintf(outfile, "\nInjection in Iteration = %d\n", GLOBAL_TIMESTEP);
	unsigned long long t = FLIPIT_GetExecutedInstructionCount();
//	fprintf(outfile, "Rank %d: Total Insts executed = %llu\n", r, t);
	fprintf(outfile, "Total Insts executed = %llu\n", t);
}

void matrixAddOuterProduct(float ***matrix, float c, float **vect);

int main(int argc, char** argv)
{
	if (signal (SIGSEGV, sigHandler) == SIG_ERR)
		printf("Error setting segfault handler...\n");
	if (signal (SIGBUS, sigHandler) == SIG_ERR)
		printf("Error setting bus error handler...\n");

	int rank = 0;
	int seed = 29678;
//	int seed = rand();
	
	FLIPIT_Init(rank, argc, argv, seed);	
	//FLIPIT_SetCustomLogger(mtxProductLogger);
	FLIPIT_SetInjector(FLIPIT_ON);
	FLIPIT_SetInjector(FLIPIT_OFF);
	
	srand(time(NULL));

	int rows = 2;
	int cols = 2;	

	int n = 39;
	int k = 32; 
	char *scheme = "hamming";
	Code *c = ECC_Code_create(n, k, scheme);
	Parity **par;

	float **matrix;
	float *vect;
	
		
	int i=0;
	int j=0;

	vect = malloc(rows * sizeof(vect));
	fill1D(&vect, rows);	
	
	alloc2D(&matrix, rows, cols);
	fill2D(&matrix, rows, cols); 
	print2D(matrix, rows, cols); 
	
	fill2DParity(c, &par, matrix, rows, cols);
//	print2DParity(par, rows, cols);

	FLIPIT_SetInjector(FLIPIT_ON);
	matrixAddOuterProduct(&matrix, 5, &vect);
	FLIPIT_Finalize(NULL);
	
	print2D(matrix, rows, cols);
	
	free(vect);
	free2D(matrix);
	free2DParity(par);

	return 0;
}
