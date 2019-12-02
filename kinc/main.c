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

void matrixAddOuterProduct(float ***matrix, float c, float *vect);
//void matrixAddOuterProduct(float ***matrix, float c, float **vect, int x, int y);

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
	FLIPIT_SetCustomLogger(mtxProductLogger);
	FLIPIT_SetInjector(FLIPIT_ON);
	FLIPIT_SetInjector(FLIPIT_OFF);
	
	int n = 39;
	int k = 32; 
	char *scheme = "hamming";
	Code *c = ECC_Code_create(n, k, scheme);
	Parity **par;

	srand(time(NULL));

	int rows = 2;
	int cols = 2;	

	int i;

	for(i=0; i<1000000; i++) {
		float **matrix = NULL;
		float *vect = NULL;
		
		vect = malloc(rows * sizeof(vect));
		fill1D(&vect, rows);	
	
		alloc2D(&matrix, rows, cols);
		fill2D(&matrix, rows, cols); 
	
		FLIPIT_SetInjector(FLIPIT_ON);
		matrixAddOuterProduct(&matrix, 5, vect);
		FLIPIT_SetInjector(FLIPIT_OFF);
		
		free(vect);
		free2D(matrix);
	}
//	matrixAddOuterProduct(&matrix, 5, &vect, rows, cols);
	FLIPIT_Finalize(NULL);
	
	ECC_Code_destroy(c);

	return 0;
}
