#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>

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

    printMatrix('S', S, dS, 1, 1);
    printMatrix('U', U, m, dS, ldu);
    printMatrix('V', V, dS, n, ldv);

    for(i=0;i<dS;i++) {
        if(S[i]>eps) S[i]=1.0/S[i];
	else S[i]=0;
    }
    for(i=0;i<m;i++) for(j=0;j<dS;j++) U[i*ldu+j]*=S[j];
    for(i=0;i<m;i++) for(j=dS;j<m;j++) U[i*ldu+j]=0;
    printMatrix('U', U, m, dS, ldu);

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

int main()
{
    float A[10]={1,2,3,4,5,6,7,8,9,10};
    float AA[10];
    float w[2];
    float y[5]={1,1,1,-1,-1};
    printMatrix('A', A, 5, 2, 2);
    pseudoInv(4,2,A,AA);
    printMatrix('A', AA, 2, 4, 4);
    linearRegW(4,2,AA,y,w);
    printMatrix('w', w, 2, 1, 1);
}
