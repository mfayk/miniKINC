#include <stdlib.h>
#include <stdio.h>
#include "ecc.h"

Codeword *ECC_Codeword_init(void);
Code *ECC_Code_init(void);
ECC_LUT *ECC_LUT_init(void);

Codeword *ECC_Codeword_init()
{
    Codeword *cw = malloc(sizeof(Codeword));
    cw->dat = (Data)0;
    cw->par = (Parity)0;
    return cw;
}

void ECC_Codeword_encode(Code *c, Codeword *cw)
{
    int i, j;
    Parity p = 0;
    Data *par = malloc(sizeof(Data) * c->p_bits);
    
    for(i = 0; i < c->p_bits; i++) {
        par[i] = 0;
        par[i] = cw->dat & c->matrix[i];
        for(j = 0; j < c->p_bits-2; j++) {
            par[i] = par[i] ^ (par[i]>>(1<<j));
        }
        par[i] = par[i] & 1;
        p = p ^ (par[i] << i);
    }
    free(par);
    cw->par = p;
}

Data ECC_Convert_float(float val)
{
    Data dat = *(Data *)&val;
    return dat;
}

float ECC_Revert_float(Data dat)
{
	float val = *(float *)&dat;
	return val;
}

Parity ECC_Parity_get(Code *c, float val)
{
    int i, j;
	Data dat = *(uint32_t *)&val;
	Data *par = malloc(sizeof(Data) * c->p_bits);
    Parity p = 0;
    
	for(i=0; i<c->p_bits; i++) {
        par[i] = 0;
        par[i] = dat & c->matrix[i];
        for(j = 0; j < c->p_bits-2; j++) {
            par[i] = par[i] ^ (par[i]>>(1<<j));
        }
        par[i] = par[i] & 1;
        p = p ^ (par[i] << i);
	}
    free(par);

	return p;
}

Codeword *ECC_Codeword_create(Code *c, Data dat)
{
   	Codeword *cw = malloc(sizeof(Codeword));
	cw->dat = dat;
    ECC_Codeword_encode(c, cw);

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

// WORKS FOR FLOATS ONLY RIGHT NOW
void ECC_Codeword_printData(Codeword *cw)
{
	float val = ECC_Revert_float(cw->dat);
	printf("%f ", val);
}

Syndrome ECC_Codeword_detect(Code *c, Codeword *cw) 
{
    Codeword *cw_tmp; 
    cw_tmp = ECC_Codeword_create(c, cw->dat);
    Syndrome syn = cw->par ^ cw_tmp->par;
    ECC_Codeword_destroy(cw_tmp);
    return syn;
}

Syndrome ECC_Parity_detect(Code *c, Parity sent, float dat)
{
	Codeword *cw = ECC_Codeword_create(c, dat);
	Syndrome syn = sent ^ cw->par;
	return syn;
}

int ECC_Parity_EDAC(Code *c, Parity *sent, float *dat)
{
/*	
	printf("checking value\t%02hhx\t%f\n", *sent, *dat);
*/	
	int signal = -1;
	Data tmp = *(Data *)&(*dat);
	Codeword *cw = ECC_Codeword_create(c, tmp);
	Syndrome syn = *sent ^ cw->par;
	if(syn != 0) {
/*
		printf("detected error in val %f\n", *dat);
		printf("attempting to correct . . .\n");
*/		
		cw->par = *sent;
		int res = ECC_Codeword_correct(c, cw, syn);
		if(res != 0) {
			printf("encountered DUE. cannot correct.\n\n");
		}
		else 
		{
			*dat = *(float *)&(cw->dat);
/*			
			printf("corrected value:\t%f\n\n", *dat);
*/
			signal = 1;
		}
	}
	else {
		signal = 0;
	}
	ECC_Codeword_destroy(cw);
	return signal;
}

int ECC_Codeword_correct(Code *c, Codeword *cw, Syndrome syn)
{
    int i = 0;
    int signal = -1;
    while((i<c->n) && (signal < 0)) {
        if(c->lut->syn[i] == syn) {
/* 
			printf("correcting error . . .\n");
*/
			cw->dat = cw->dat ^ c->lut->cw[i]->dat;
            cw->par = cw->par ^ c->lut->cw[i]->par;
            signal = 0;
            break;
        }
        i++;
    }
    //SANITY CHECK
    if(signal == 0) {
        Syndrome syndrome = ECC_Codeword_detect(c, cw);
        if(syndrome != 0) {
            printf("SOMETHING WENT WRONG IN ECC_Codeword_correct!\n");
        }
    }
    return signal;
}

float ECC_Codeword_getData(Codeword *cw)
{
	float val = *(float *)&(cw->dat);
	return val;
}

ECC_LUT *ECC_LUT_init()
{
    ECC_LUT *lut = malloc(sizeof(ECC_LUT));
    lut->syn = NULL;
    lut->cw = NULL;
    return lut;
}

void ECC_LUT_generate(Code *c)
{
    int i;
	ECC_LUT *lut = ECC_LUT_init();
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
    return res;
}

Code *ECC_Code_init()
{
    Code *c = malloc(sizeof(Code));
    c->n = 0;
    c->k = 0;
    c->p_bits = 0;
    c->matrix = NULL;
    c->scheme = NULL;
    return c;
}

Code *ECC_Code_create(int n, int k, char *scheme)
{
//	Code *c = ECC_Code_init();
  	Code *c = malloc(sizeof(Code));
	c->n = n;
    c->k = k;
    c->p_bits = n - k;
    c->scheme = scheme;
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
        ECC_LUT_destroy(c);
        free(c->matrix);
        free(c);
    }
}





