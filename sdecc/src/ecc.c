#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ecc.h"

Code *ECC_Code_init(void);
ECC_LUT *ECC_LUT_init(void);
int ECC_Matrix_load(Code *);
void ECC_LUT_generate(Code *);
void ECC_LUT_destroy(Code *);

static inline Parity ECC_Parity_calculate(Code *c, Data dat)
{
	Data par[c->par];
	Parity p = 0;
	int i;
	int j;
	for(i=0; i<c->par; i++) {
		par[i] = dat & c->matrix[i];
		for(j=0; j<c->par-2; j++) {
			par[i] = par[i] ^ (par[i]>>(1<<j));
		}
		par[i] = par[i] & 1;
		p = p ^ (par[i] << i);
	}
	return p;
}


Code *ECC_Code_create(int n, int k, char *scheme)
{
  	Code *c = malloc(sizeof(Code));
	c->n = n;
    c->k = k;
    c->par = n - k;
    c->scheme = strdup(scheme);
    
	c->matrix = malloc(sizeof(Data) * (c->n - c->k));
    int res = ECC_Matrix_load(c);
    if(res < 0) {
        c = NULL;
    }
    else {
        ECC_LUT_generate(c);
    }
    return c;
}

void ECC_Code_destroy(Code *c)
{
    if(c) {
    	free(c->scheme);
		if(c->matrix) { 
			free(c->matrix); 
		}
		if(c->lut) {
			ECC_LUT_destroy(c);
		}
        free(c);
    }
}

void ECC_LUT_generate(Code *c)
{
    int i;
  	ECC_LUT *lut = malloc(sizeof(ECC_LUT));
	lut->syn = malloc(sizeof(Syndrome) * c->n);
    lut->cw = malloc(sizeof(Codeword*) * c->n);

    for(i=0; i<c->n; i++) {
  		lut->cw[i] = ECC_Codeword_create(c, 0);
		if(i < c->k) {
            lut->cw[i]->dat = lut->cw[i]->dat ^ ((Data)1<<(i));
        }
        else {
            lut->cw[i]->par = lut->cw[i]->par ^ ((Parity)1<<(i - (c->k)));
        }
		lut->syn[i] = ECC_Codeword_detect(c, lut->cw[i]);
	}
    c->lut = lut;
}

void ECC_LUT_destroy(Code *c)
{
    int i;
    for(i=0; i<c->n; i++) {
        ECC_Codeword_destroy(c->lut->cw[i]); 
    }
    free(c->lut->cw);
    free(c->lut->syn);
    free(c->lut);
}

void ECC_LUT_print(Code *c)
{
    int i;
    for(i=0; i<c->n; i++) {
        printf("%d\t", c->lut->syn[i]);
        ECC_Codeword_print(c->lut->cw[i]);
        printf("\n");
    }
}

void ECC_Matrix_print(Code *c)
{
    int i;
    for(i=0; i<(c->n - c->k); i++) {
        printf("%08X\n", c->matrix[i]);
    }
}

int ECC_Matrix_load(Code *c)
{
    int res = 0;
    int len = strlen("res/") + strlen(c->scheme) + 1;
    len += snprintf(0,0,"%+d", c->k);   // no -1 to account for extra '/'
    char *fname = malloc(sizeof(char) * len);
    snprintf(fname, len, "res/%d/%s", c->k, c->scheme);
    FILE *ifile;
    if((ifile=fopen(fname, "r")) == NULL) {
        printf("error loading matrix file %s\n", fname);
        res = -1;
    }
    else {
        int i;
        for(i=0; i<(c->n - c->k); i++) {
            fscanf(ifile, "%08x", &(c->matrix[i]));
        }
    }
    free(fname);
	fclose(ifile);
	return res;
}

Parity ECC_Parity_get(Code *c, float val)
{
	Data dat = *(uint32_t *)&val;
	return ECC_Parity_calculate(c, dat);
}

Codeword *ECC_Codeword_create(Code *c, Data dat)
{
   	Codeword *cw = malloc(sizeof(Codeword));
	cw->dat = dat;
	cw->par = ECC_Parity_calculate(c, dat);

    return cw;
}

void ECC_Codeword_destroy(Codeword *cw)
{
    if(cw) {
        free(cw);
    }
}

void ECC_Codeword_print(Codeword *cw)
{
    printf("%02hhx %08x ", cw->par, cw->dat);
}

void ECC_Codeword_encode(Code *c, Codeword *cw)
{
	cw->par = ECC_Parity_calculate(c, cw->dat);
}

Syndrome ECC_Codeword_detect(Code *c, Codeword *cw) 
{
    Parity par = ECC_Parity_calculate(c, cw->dat);
	return (Syndrome) (cw->par ^ par);
}

int ECC_Codeword_correct(Code *c, Codeword *cw, Syndrome syn)
{
    int i = 0;
    int signal = -1;
    while((i<c->n) && (signal < 0)) {
        if(c->lut->syn[i] == syn) {
			cw->dat = cw->dat ^ c->lut->cw[i]->dat;
            cw->par = cw->par ^ c->lut->cw[i]->par;
            signal = 0;
            break;
        }
        i++;
    }
	return signal;
}

Syndrome ECC_Parity_detect(Code *c, Parity sent, float dat)
{
	Codeword *cw = ECC_Codeword_create(c, dat);
	Syndrome syn = sent ^ cw->par;
	return syn;
}

int ECC_Parity_EDAC(Code *c, Parity *sent, float *dat)
{
	int signal = -1;
	Data tmp = *(Data *)&(*dat);
	Codeword *cw = ECC_Codeword_create(c, tmp);
	Syndrome syn = *sent ^ cw->par;
	if(syn != 0) {
		cw->par = *sent;
		int res = ECC_Codeword_correct(c, cw, syn);
		if(res != 0) {
			printf("encountered DUE. cannot correct.\n\n");
		}
		else 
		{
			*dat = *(float *)&(cw->dat);
			signal = 1;
		}
	}
	else {
		signal = 0;
	}
	ECC_Codeword_destroy(cw);
	return signal;
}






