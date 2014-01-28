#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lapacke.h>
#include <cblas.h>

#define MAXN (1000)
#define min(a,b) ((a)>(b)?(b):(a))

void printMatrix(char MN, double* M, int m, int n, int ld)
{
    int i, j;
    printf("%c:\n", MN);
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) printf("%lf ", M[i*ld+j]);
	printf("\n");
    }
    printf("\n");
}

void transMatrix(double* M, int m, int n, int ld)
{
    int i, j;
    double tmp;
    for(i=0;i<m;i++) {
        for(j=0;j<i;j++) {
	    tmp=M[i*ld+j];
	    M[i*ld+j]=M[j*ld+i];
	    M[j*ld+i]=tmp;
        }
    }
}

void ridgeInv(int m, int n, double* A, double* AA, double lamda)
{
    double* AT=(double*)malloc(m*n*sizeof(double));
    double* ftmp=(double*)malloc(n*n*sizeof(double));
    lapack_int* ipiv = (lapack_int *)malloc(n*sizeof(lapack_int));
    double eps=10e-8, tmp;
    int i, j;

    memcpy(AT, A, m*n*sizeof(double));
    memcpy(AA, A, m*n*sizeof(double));
    for(i=0;i<n;i++) for(j=0;j<n;j++) ftmp[i*n+j]=(i==j?1:0);
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, m, 1.0, AT, n, AA, n, lamda, ftmp, n);
    //printMatrix('t', ftmp, n, n, n);

    LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, ftmp, n, ipiv);
    LAPACKE_dgetri(LAPACK_ROW_MAJOR, n, ftmp, n, ipiv);
    //printMatrix('t', ftmp, n, n, n);
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, n, m, n, 1.0, ftmp, n, A, n, 0.0, AA, m);
    //printMatrix('A', AA, n, m, m);

    free(AT); free(ftmp);
}

void linearRegW(int m, int n, double* AA, double* y, double* w)
{
    cblas_dgemv(CblasRowMajor, CblasNoTrans, n, m, 1.0, AA, m, y, 1, 0.0, w, 1);
}

void linearRegPred(int m, int n, double* A, double* w, double* y)
{
    cblas_dgemv(CblasRowMajor, CblasNoTrans, m, n, 1.0, A, n, w, 1, 0.0, y, 1);
}

int verify(int m, double* y, double* yy) 
{
    int i, k=0;
    for(i=0;i<m;i++) if(y[i]*yy[i]>0) k++;
    return k;
}

int main(int argc, char*argv[])
{
    FILE* test=fopen(argv[3], "r");
    FILE* val=fopen(argv[4], "r");
    int i, j, N, k, d=atoi(argv[1]);
    double lamda=atof(argv[2]);
    double* A=(double*)malloc(MAXN*d*sizeof(double));
    double* TA=(double*)malloc(MAXN*d*sizeof(double));
    double* AA=(double*)malloc(MAXN*d*sizeof(double));
    double* w=(double*)malloc(d*sizeof(double));
    double* y=(double*)malloc(MAXN*sizeof(double));
    double* yy=(double*)malloc(MAXN*sizeof(double));

    //while(EOF!=scanf(" %lf %lf %lf %lf ", A+i*d, A+i*d+1, A+i*d+2, y+i)) {
    k=0;
    while(1) {
        for(j=0;j<d;j++) {
	    if(EOF==scanf(" %lf", A+i*d+j)) { k=1; break; }
	}
	if(EOF==scanf(" %lf", y+i)) { k=1; break; }
	if(k) break;
        i++;
    }
    N=i;
    memcpy(TA, A, N*d*sizeof(double));
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
    printf("lamda:%.10f\n", lamda);
    printf("Ein: %d %d %lf\n", k, N, 1-(double)k/N);

    i=0; k=0;
    while(1) {
        for(j=0;j<d;j++) {
            if(EOF==fscanf(val, " %lf", A+i*d+j)) { k=1; break; }
        }
        if(EOF==fscanf(val, " %lf", y+i)) { k=1; break; }
        if(k) break;
        i++;
    }
    N=i;
    linearRegPred(N,d,A,w,yy);
    k=verify(N, y, yy);
    printf("Eval: %d %d %lf\n", k, N, 1-(double)k/N);

    i=0; k=0;
    while(1) {
        for(j=0;j<d;j++) {
            if(EOF==fscanf(test, " %lf", A+i*d+j)) { k=1; break; }
        }
        if(EOF==fscanf(test, " %lf", y+i)) { k=1; break; }
        if(k) break;
        i++;
    }
    N=i;
    //printMatrix('A', A, N, d, d);
    //printMatrix('y', y, N, 1, 1);
    linearRegPred(N,d,A,w,yy);
    k=verify(N, y, yy);
    printf("Eout: %d %d %lf\n", k, N, 1-(double)k/N);
}
