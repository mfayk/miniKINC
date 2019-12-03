#include "FlipIt/corrupt/corrupt.h"
#include <signal.h>
#include "../sdecc/src/ecc.h"
#include "util.h"

void matrixAddOuterProduct(float ***matrix, float c, float **vect);
void matrixAddOuterProductECC(Code *, Parities **, float ***, float, float *);

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

int main(int argc, char** argv)
{
	if (signal (SIGSEGV, sigHandler) == SIG_ERR) 
		printf("Error setting segfault handler...\n");
	if (signal (SIGBUS, sigHandler) == SIG_ERR) 
		printf("Error setting bus error handler...\n");
	
	srand(time(NULL));
	
	int rank = 0;
	int seed = rand();
	
	FLIPIT_Init(rank, argc, argv, seed);	
	FLIPIT_SetCustomLogger(mtxProductLogger);
	FLIPIT_SetInjector(FLIPIT_ON);
	FLIPIT_SetInjector(FLIPIT_OFF);
	
	int n = 39;
	int k = 32; 
//	char *scheme = "hamming";
	char *scheme = "hsiao";
	Code *c = ECC_Code_create(n, k, scheme);

	int rows = 2;
	int cols = 2;	
	int trials = 1;
	
	printf("\nrunning trials . . .\n");
	int i;
	for(i=0; i<trials; i++) {
		float var = 5.0;
		float **matrix = NULL;
		float *vect = NULL;
		set1D(&vect, rows);
		set2D(&matrix, rows, cols);
		
		Parities *par = malloc(sizeof(Parities));
		setParity(c, &(par->cval), var);
		set1DParity(c, &(par->vect), vect, rows);
		set2DParity(c, &(par->mtx), matrix, rows, cols);
		
		printf("\noriginal cval:\n%f\n", var);
		printf("\n");
		printf("original vect:\n");
		print1D(vect, rows);
		printf("\n");
		printf("original matrix:");
		printf("\n");
		print2D(matrix, rows, cols);

		FLIPIT_SetInjector(FLIPIT_ON);
		matrixAddOuterProductECC(c, &par, &matrix, var, vect);
		FLIPIT_SetInjector(FLIPIT_OFF);

		printf("\n(possibly) corrupted matrix:");
		print2D(matrix, rows, cols);
		
		free(vect);
		free2D(matrix);
	}
	FLIPIT_Finalize(NULL);
	
	ECC_Code_destroy(c);

	return 0;
}
