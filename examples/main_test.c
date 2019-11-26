
#include <stdio.h>
#include "/scratch1/mfaykus/FlipIt/include/FlipIt/corrupt/corrupt.h"

int work(int a, int b);

int main(int argc, char** argv)
{
	int a = 2, b=2;
	int rank = 0;
	int seed = 7;
	FLIPIT_Init(rank, argc, argv, seed);
 	printf("Should be corrupted: %d + %d = %d\n", a, b, work(a, b));
	FLIPIT_Finalize(NULL);
	return 0;
}
