#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MODN (33554432)
#define SIGN(x) (x>0?1:-1)

int cmp_d=0;
int cmp_fv(const void * a, const void * b)
{
  if(*((float*)a+cmp_d) == *((float*)b+cmp_d)) return 0;
  return (*((float*)a+cmp_d) - *((float*)b+cmp_d))>0?1:-1;
}
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

int main(int argc, char* argv[])
{
    FILE* test=fopen(argv[1], "r");
    int i, j, q, k, mk, s, N, mq, p;
    float x[100][10];
    float tx[100];
    int y[100];
    float theta, mt;
    rand_seed();

    i=0;
    while(EOF!=scanf(" %f %f %f %f %f %f %f %f %f %d", x[i],x[i]+1,x[i]+2,x[i]+3,x[i]+4,x[i]+5,x[i]+6,x[i]+7,x[i]+8,y+i)) {
	i++;
    }
    N=i;

    mk=0;
    for(q=0;q<9;q++) {
        for(i=0;i<N;i++) tx[i]=x[i][q];
	qsort(tx, N, sizeof(float), cmp_f);
    //for(i=0;i<N;i++) printf("%f %d\n", x[i], y[i]);
    //for(i=0;i<N;i++) printf("%f\n", tx[i]);
    //printf("===\n");

	for(i=0;i<N-1;i++) {
	    theta=(tx[i+1]+tx[i])/2;
	    k=0;
	    for(j=0;j<N;j++) 
		if(SIGN(x[j][q]-theta)*y[j] >0) k++;
	    if(k>mk) { mt=theta; mk=k; s=1; mq=q; }
	    else if(N-k>mk) { mt=theta; mk=N-k; s=-1; mq=q; }
	}
    }
    printf("%f %d %d %d\n", mt, s, mq, mk);
    printf("%f %f\n", 1-(float)mk/N, 0.5+0.3*s*(fabs(mt)-1));
    k=0; i=0;
    while(EOF!=fscanf(test, " %f %f %f %f %f %f %f %f %f %d", tx,tx+1,tx+2,tx+3,tx+4,tx+5,tx+6,tx+7,tx+8,&p)) {
	i++;
        if(SIGN(tx[mq]-mt)*s*p >0) k++;
    }
    N=i;
    printf("%f %d\n", 1-(float)k/N, k);
}
