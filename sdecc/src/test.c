#include "ecc.h"

void code_create_test(void);

void code_create_test()
{
	int i;
    int n = 39; 
    int k = 32;
   	char *scheme = "hsiao";	
	Code *c = ECC_Code_create(n, k, scheme);
	
    for(i=0; i<c->n; i++) {
        Codeword *cw = ECC_Codeword_create(c, (Data) 0);
        if(i < c->k) {
            cw->dat = cw->dat ^ ((Data)1<<(i));
        }
        else {
            cw->par = cw->par ^ ((Parity)1<<(i-(c->k)));
        }
        Syndrome syn = ECC_Codeword_detect(c, cw);
        if(syn != 0) {
            ECC_Codeword_correct(c, cw, syn);
        }
        else {
            printf("no error detected!\n");
        }
        ECC_Codeword_destroy(cw);
    }
    ECC_Code_destroy(c);
}


int main(int argc, char *argv[])
{
	code_create_test();
	return 0;
}


