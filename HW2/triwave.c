#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(x) (fabs(fmod(x,4)-2)-1)
#define SIGN(x) (x>0?1:-1)
#define N (5)

int main()
{
    int x[5]={1,2,4,8,16};
    float a;
    int i;
    for(a=0.1;a<10;a+=0.101) {
        printf("RESULT %.2f ",a);
        for(i=0;i<N;i++) printf("%f ", f(x[i]*a));
        printf("\n");
        for(i=0;i<N;i++) printf("%d ", SIGN(f(x[i]*a)));
        printf("\n");
    }
}

