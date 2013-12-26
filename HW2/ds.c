#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MODN (33554432)
#define SIGN(x) (x>0?1:-1)

int cmp_f(const void * a, const void * b)
{
  if(*(float*)a == *(float*)b) return 0;
  return (*(float*)a - *(float*)b)>0?1:-1;
}

void rand_seed() {
    struct timeval tt;
    unsigned int t;
    gettimeofday(&tt, NULL);
    t=tt.tv_sec*1000+tt.tv_usec/1000;
    //printf("%u\n", t);
    //srand(time(NULL));
    srand(t);
}

int main()
{
    int i, j, k, mk, s, N=20;
    float x[200];
    float tx[200];
    int y[200];
    float theta, mt;
    rand_seed();

    for(i=0;i<N;i++) {
        x[i]=rand()%MODN*2/(float)MODN-1;
	y[i]=SIGN(x[i]);
	if(rand()%5==0) y[i]*=-1;
	tx[i]=x[i];
    }
    qsort(tx, N, sizeof(float), cmp_f);
    //for(i=0;i<N;i++) printf("%f %d\n", x[i], y[i]);
    //for(i=0;i<N;i++) printf("%f\n", tx[i]);

    mk=0;
    for(i=0;i<N-1;i++) {
        theta=(tx[i+1]+tx[i])/2;
	k=0;
	for(j=0;j<N;j++) 
	    if(SIGN(x[j]-theta)*y[j] >0) k++;
	if(k>mk) { mt=theta; mk=k; s=1; }
	else if(N-k>mk) { mt=theta; mk=N-k; s=-1; }
    }
    //printf("%f %d %d\n", mt, s, mk);
    printf("%f %f\n", 1-(float)mk/N, 0.5+0.3*s*(fabs(mt)-1));
}
