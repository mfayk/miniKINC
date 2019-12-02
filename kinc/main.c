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
	printf("Total Insts executed = %llu\n", FLIPIT_GetExecutedInstructionCount());
	exit(sig);
}
void mtxProductLogger(FILE* outfile)
{
	int r;
	fprintf(outfile, "\nInjection in Iteration = %d\n", GLOBAL_TIMESTEP);
	unsigned long long t = FLIPIT_GetExecutedInstructionCount();
	fprintf(outfile, "Total Insts executed = %llu\n", t);
}

void matrixAddOuterProduct(float ***matrix, float c, float **vect, int x, int y);

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
//	FLIPIT_SetCustomLogger(mtxProductLogger);
	FLIPIT_SetInjector(FLIPIT_ON);
	FLIPIT_SetInjector(FLIPIT_OFF);
	
	srand(time(NULL));

	int rows = 10000;
	int cols = 10000;	

	int n = 39;
	int k = 32; 
	char *scheme = "hamming";
	Code *c = ECC_Code_create(n, k, scheme);
	Parity **par;

	float **matrix = NULL;
	float *vect = NULL;
	
	vect = malloc(rows * sizeof(vect));
	fill1D(&vect, rows);	
	
	alloc2D(&matrix, rows, cols);
	fill2D(&matrix, rows, cols); 
//	print2D(matrix, rows, cols); 
	
	fill2DParity(c, &par, matrix, rows, cols);
//	print2DParity(par, rows, cols);

	FLIPIT_SetInjector(FLIPIT_ON);
//	matrixAddOuterProduct(&matrix, 5, &vect);
	matrixAddOuterProduct(&matrix, 5, &vect, rows, cols);
	FLIPIT_Finalize(NULL);
	
//	print2D(matrix, rows, cols);
	
	free(vect);
	free2D(matrix);
	free2DParity(par);
	ECC_Code_destroy(c);

	return 0;
}
