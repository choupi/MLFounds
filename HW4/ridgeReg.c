#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lapacke.h>
#include <cblas.h>

#define MAXN (1000)
#define min(a,b) ((a)>(b)?(b):(a))

void printMatrix(char MN, float* M, int m, int n, int ld)
{
    int i, j;
    printf("%c:\n", MN);
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) printf("%f ", M[i*ld+j]);
	printf("\n");
    }
    printf("\n");
}

void transMatrix(float* M, int m, int n, int ld)
{
    int i, j;
    float tmp;
    for(i=0;i<m;i++) {
        for(j=0;j<i;j++) {
	    tmp=M[i*ld+j];
	    M[i*ld+j]=M[j*ld+i];
	    M[j*ld+i]=tmp;
        }
    }
}

void ridgeInv(int m, int n, float* A, float* AA, float lamda)
{
    float* AT=(float*)malloc(m*n*sizeof(float));
    float* ftmp=(float*)malloc(n*n*sizeof(float));
    lapack_int* ipiv = (lapack_int *)malloc(n*sizeof(lapack_int));
    float eps=10e-8, tmp;
    int i, j;

    memcpy(AT, A, m*n*sizeof(float));
    memcpy(AA, A, m*n*sizeof(float));
    for(i=0;i<n;i++) for(j=0;j<n;j++) ftmp[i*n+j]=(i==j?1:0);
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, m, 1.0, AT, n, AA, n, lamda, ftmp, n);
    //printMatrix('t', ftmp, n, n, n);

    LAPACKE_sgetrf(LAPACK_ROW_MAJOR, n, n, ftmp, n, ipiv);
    LAPACKE_sgetri(LAPACK_ROW_MAJOR, n, ftmp, n, ipiv);
    //printMatrix('t', ftmp, n, n, n);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, n, m, n, 1.0, ftmp, n, A, n, 0.0, AA, m);
    //printMatrix('A', AA, n, m, m);

    free(AT); free(ftmp);
}

void linearRegW(int m, int n, float* AA, float* y, float* w)
{
    cblas_sgemv(CblasRowMajor, CblasNoTrans, n, m, 1.0, AA, m, y, 1, 0.0, w, 1);
}

void linearRegPred(int m, int n, float* A, float* w, float* y)
{
    cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, 1.0, A, n, w, 1, 0.0, y, 1);
}

int verify(int m, float* y, float* yy) 
{
    int i, k=0;
    for(i=0;i<m;i++) if(y[i]*yy[i]>0) k++;
    return k;
}

int main(int argc, char*argv[])
{
    FILE* test=fopen(argv[3], "r");
    int i, j, N, k, d=atoi(argv[1]);
    float lamda=atof(argv[2]);
    float* A=(float*)malloc(MAXN*d*sizeof(float));
    float* TA=(float*)malloc(MAXN*d*sizeof(float));
    float* AA=(float*)malloc(MAXN*d*sizeof(float));
    float* w=(float*)malloc(d*sizeof(float));
    float* y=(float*)malloc(MAXN*sizeof(float));
    float* yy=(float*)malloc(MAXN*sizeof(float));

    //while(EOF!=scanf(" %f %f %f %f ", A+i*d, A+i*d+1, A+i*d+2, y+i)) {
    k=0;
    while(1) {
        for(j=0;j<d;j++) {
	    if(EOF==scanf(" %f", A+i*d+j)) { k=1; break; }
	}
	if(EOF==scanf(" %f", y+i)) { k=1; break; }
	if(k) break;
        i++;
    }
    N=i;
    memcpy(TA, A, N*d*sizeof(float));
    //printf("%d\n", N);
    //printMatrix('A', A, N, d, d);
    //printMatrix('y', y, N, 1, 1);
    ridgeInv(N,d,TA,AA,lamda);
    //printMatrix('A', AA, 2, N, N);
    linearRegW(N,d,AA,y,w);
    printMatrix('w', w, d, 1, 1);
    linearRegPred(N,d,A,w,yy);
    //printMatrix('y', yy, N, 1, 1);
    k=verify(N, y, yy);
    printf("lamda:%f\n", lamda);
    printf("Ein: %d %d %f\n", k, N, 1-(float)k/N);
    i=0; k=0;
    while(1) {
        for(j=0;j<d;j++) {
            if(EOF==fscanf(test, " %f", A+i*d+j)) { k=1; break; }
        }
        if(EOF==fscanf(test, " %f", y+i)) { k=1; break; }
        if(k) break;
        i++;
    }
    N=i;
    //printMatrix('A', A, N, d, d);
    //printMatrix('y', y, N, 1, 1);
    linearRegPred(N,d,A,w,yy);
    k=verify(N, y, yy);
    printf("Eout: %d %d %f\n", k, N, 1-(float)k/N);
}
