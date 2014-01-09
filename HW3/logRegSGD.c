#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXN (3000)
#define ITER (2000)
#define theta(x) (1.0/(1+exp(-1*x)))

void printVector(char vn, float* V, int n)
{
    int i;
    printf("%c: ", vn);
    for(i=0;i<n;i++) printf("%f ", V[i]);
    printf("\n");
}

float sDot(float* a, float* b, int n)
{
    int i;
    float r=0;
    for(i=0;i<n;i++) r+=a[i]*b[i];
    return r;
}

void sAxpy(float* x, float* y, float alpha, int n)
{
    int i;
    for(i=0;i<n;i++) y[i]+=alpha*x[i];
}

void logRegSGDIter(float* X, int* Y, float* w, int N, int d, float anta, int it)
{
    int i;
    float t, tt;
    float* s=(float*)malloc(d*sizeof(float));
    for(i=0;i<d;i++) s[i]=0.0;
    i=it%N;
        //t=-1*Y[i]*cblas_sdot(d, X+i*d, 1, w, 1);
	t=-1*Y[i]*sDot(X+i*d, w, d);
	//printVector('x', X+i*d, d);
	tt=-1*Y[i]*theta(t);
	//printf("t %f %f\n", t, tt);
	//cblas_saxpy(d, tt, X+i*d, 1, s, 1);
	sAxpy(X+i*d, s, tt, d);
	//printVector('s', s, d);
    //printVector('s', s, d);
    t=-1*anta;
    //cblas_saxpy(d, t, s, 1, w, 1);
    sAxpy(s, w, t, d);
}

int main(int argc, char* argv[])
{
    FILE* test=fopen(argv[1], "r");
    int i=0, j, k=0, d=20, N;
    //float X[6]={1,2,3,4,5,6};
    //int Y[3]={1,1,-1};
    float* X=(float*)malloc(MAXN*d*sizeof(float));
    int* Y=(int*)malloc(MAXN*sizeof(int));
    float* w=(float*)malloc(d*sizeof(float));
    printf("%s", argv[1]);

    while(1) {
        for(j=0;j<d;j++) {
            if(EOF==scanf(" %f", X+i*d+j)) { k=1; break; }
        }
        if(EOF==scanf(" %d", Y+i)) { k=1; break; }
        if(k) break;
        i++;
    }
    N=i;

    for(i=0;i<d;i++) w[i]=0.0;
    for(i=0;i<ITER;i++) {
	logRegSGDIter(X, Y, w, N, d, 0.001, i);
	//printVector('w', w, d);
    }
    //for(i=0;i<N;i++) printf("%f ", sDot(X+i*d, w, d));
    //printf("\n");
    printVector('w', w, d);
    i=0; k=0;
    while(1) {
        for(j=0;j<d;j++) {
            if(EOF==fscanf(test, " %f", X+i*d+j)) { k=1; break; }
        }
        if(EOF==fscanf(test, " %d", Y+i)) { k=1; break; }
        if(k) break;
        i++;
    }
    N=i;
    k=0;
    for(i=0;i<N;i++) if(sDot(X+i*d, w, d)*Y[i]>0) k++;
    printf("%d %d %f\n", k, N, 1-(float)k/N);
}

