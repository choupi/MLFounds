#include <stdio.h>
#include <stdlib.h>
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

void pseudoInv(int m, int n, float* A, float* AA)
{
    int dS=min(m,n);
    float* S=(float*)malloc(dS*sizeof(float));
    float* U=(float*)malloc(m*m*sizeof(float));
    float* V=(float*)malloc(n*n*sizeof(float));
    //float* AA=(float*)malloc(m*n*sizeof(float));
    float* ftmp=(float*)malloc(m*n*sizeof(float));
    float eps=10e-8, tmp;
    int InfoSVD=0;
    int i, j, lda=n, ldu=m, ldv=n;
    InfoSVD=LAPACKE_sgesvd(LAPACK_ROW_MAJOR, 'A', 'A', m, n, A, lda, S, U, ldu, V, ldv, ftmp);

    //printMatrix('S', S, dS, 1, 1);
    //printMatrix('U', U, m, dS, ldu);
    //printMatrix('V', V, dS, n, ldv);

    for(i=0;i<dS;i++) {
        if(S[i]>eps) S[i]=1.0/S[i];
	else S[i]=0;
    }
    for(i=0;i<m;i++) for(j=0;j<dS;j++) U[i*ldu+j]*=S[j];
    for(i=0;i<m;i++) for(j=dS;j<m;j++) U[i*ldu+j]=0;
    //printMatrix('U', U, m, dS, ldu);

    //transMatrix(U, m, m, ldu);
    //printMatrix('U', U, dS, m, ldu);
    //transMatrix(V, n, n, ldv);
    //printMatrix('V', V, dS, n, ldv);

    //cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, m, dS, 1.0, V, ldv, U, ldu, 0.0, AA, ldu);
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasTrans, n, m, dS, 1.0, V, ldv, U, ldu, 0.0, AA, ldu);
    free(S); free(U); free(V); free(ftmp);
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
    int i, N, k, d=3;
    float* A=(float*)malloc(MAXN*d*sizeof(float));
    float* AA=(float*)malloc(MAXN*d*sizeof(float));
    float* w=(float*)malloc(d*sizeof(float));
    float* y=(float*)malloc(MAXN*sizeof(float));
    float* yy=(float*)malloc(MAXN*sizeof(float));

    while(EOF!=scanf(" %f %f %f %f ", A+i*d, A+i*d+1, A+i*d+2, y+i)) {
        i++;
    }
    N=i;
    //printf("%d\n", N);
    //printMatrix('A', A, N, 2, 2);
    //printMatrix('y', y, N, 1, 1);
    pseudoInv(N,d,A,AA);
    //printMatrix('A', AA, 2, N, N);
    linearRegW(N,d,AA,y,w);
    //printMatrix('w', w, d, 1, 1);
    linearRegPred(N,d,A,w,yy);
    //printMatrix('y', yy, N, 1, 1);
    k=verify(N, y, yy);
    printf("%d %d %f\n", k, N, 1-(float)k/N);
}
