#include <stdio.h>
#include <stdlib.h>

#define N (1000)
#define MODN (33554432)
#define SIGN2(x1,x2) ((x1*x1+x2*x2-0.6)>0?1:-1)

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
    int i, j;
    float x[N][2];
    int y[N];
    rand_seed();

    for(i=0;i<N;i++) {
        x[i][0]=rand()%MODN*2/(float)MODN-1;
        x[i][1]=rand()%MODN*2/(float)MODN-1;
	y[i]=SIGN2(x[i][0],x[i][1]);
    }
    for(i=0;i<N*0.1;i++) y[i]*=-1; 
    for(i=0;i<N;i++) printf("1 %f %f %d\n", x[i][0], x[i][1], y[i]);
}
