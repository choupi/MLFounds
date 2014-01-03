#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void logRegIter(float* X, int* Y, float* w, int N, int d, float anta)
{
    int i;
    float t, tt;
    float* s=(float*)malloc(d*sizeof(float));
    for(i=0;i<d;i++) s[i]=0.0;
    for(i=0;i<N;i++) {
        //t=-1*Y[i]*cblas_sdot(d, X+i*d, 1, w, 1);
	t=-1*Y[i]*sDot(X+i*d, w, d);
	//printVector('x', X+i*d, d);
	tt=-1*Y[i]*theta(t);
	//printf("t %f %f\n", t, tt);
	//cblas_saxpy(d, tt, X+i*d, 1, s, 1);
	sAxpy(X+i*d, s, tt, d);
	//printVector('s', s, d);
    }
    //printVector('s', s, d);
    t=-1*anta/N;
    //cblas_saxpy(d, t, s, 1, w, 1);
    sAxpy(s, w, t, d);
}

int main()
{
    float X[6]={1,2,3,4,5,6};
    int Y[3]={1,1,-1};
    float w[2]={0,0};
    int i;
    for(i=0;i<10;i++) {
	logRegIter(X, Y, w, 3, 2, 0.01);
	printVector('w', w, 2);
    }
    for(i=0;i<3;i++) printf("%f ", sDot(X+i*2, w, 2));
}

