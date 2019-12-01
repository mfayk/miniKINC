#include "ecc.h"

int main(int argc, char *argv[])
{
    int n = 39; 
    int k = 32;
   	char *scheme = "hamming";	//or "hsiao"
	Code *c = ECC_Code_create(n, k, scheme);

    int i;
    for(i=0; i<n; i++) {
        Codeword *cw = ECC_Codeword_create(c, (Data) 0);
        if(i < c->k) {
            cw->dat = cw->dat ^ ((Data)1<<(i));
        }
        else {
            cw->par = cw->par ^ ((Parity)1<<(i-(c->k)));
        }
        Syndrome syn = ECC_Codeword_detect(c, cw);
        if(syn != 0) {
            printf("error detected!\t");
            ECC_Codeword_print(cw);
            printf("\t");
            ECC_Codeword_correct(c, cw, syn);
            ECC_Codeword_print(cw);
            printf("\n");
        }
        else {
            printf("no error detected!\n");
        }
        ECC_Codeword_destroy(cw);
    }
    ECC_Code_destroy(c);
    return 0;
}


