#include "FlipIt/corrupt/corrupt.h"
#include <signal.h>
#include "../sdecc/src/ecc.h"
#include "util.h"


void matrixAddOuterProduct(float ***matrix, float c, float **vect);
void matrixAddOuterProductECC(Code *, float ***, float, float *, Parity **, Parity, Parity *);

int GLOBAL_TIMESTEP = 0;

void sigHandler(int sig)
{
	printf("Receiving Sig %d\n", sig);
	unsigned long long t = FLIPIT_GetExecutedInstructionCount();
	printf("Total Insts executed = %llu\n", FLIPIT_GetExecutedInstructionCount());
	exit(sig);
}
void mtxProductLogger(FILE* outfile)
{
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
	
/*
	int rank = 0;
	int seed = rand();

	FLIPIT_Init(rank, argc, argv, seed);	
	FLIPIT_SetCustomLogger(mtxProductLogger);
	FLIPIT_SetInjector(FLIPIT_ON);
	FLIPIT_SetInjector(FLIPIT_OFF);
*/
	/* set up code */
	int n = 39;
	int k = 32; 
	char *scheme = "hsiao";
	Code *c = ECC_Code_create(n, k, scheme);
	
	int rows = 2;
	int cols = 2;	
	int trials = 1;	
	
	printf("\nrunning trials . . .\n\n");
	int i;
	for(i=0; i<trials; i++) {
		float var = 5.0;
		float **matrix = NULL;
		float *vect = NULL;
		set1D(&vect, rows);
		set2D(&matrix, rows, cols);

		/* get parity on data values */
		Parity val_par;
		setParity(c, &val_par,  var);
		Parity *vect_par = NULL;
		set1DParity(c, &vect_par, vect, rows);
		Parity **mtx_par = NULL;
		set2DParity(c, &mtx_par, matrix, rows, cols);

/*
		FLIPIT_SetInjector(FLIPIT_ON);
*/
		matrixAddOuterProductECC(c, &matrix, var, vect, mtx_par, val_par, vect_par);
		
//		matrixAddOuterProduct(&matrix, var, &vect);

/*
		FLIPIT_SetInjector(FLIPIT_OFF);
*/
		free(vect);
		free2D(matrix);

		free1DParity(vect_par);
		free2DParity(mtx_par);

	}
	printf("\ncompleted trials!\n\n");	

	ECC_Code_destroy(c);

/*
	FLIPIT_Finalize(NULL);
*/
	return 0;
}
