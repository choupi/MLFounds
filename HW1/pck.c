#include <stdio.h>
#include <stdlib.h>

void shuf(int *nn, int n) {
    int i, p, t;
    for(i=0;i<n;i++) {
        p=rand()%n;
	t=nn[p];
	nn[p]=nn[i];
	nn[i]=t;
    }
}

int main()
{
    int i, j, k, n, p, flag;
    float x[1000][4];
    int y[1000];
    float w[5]={0.0};
    float s;
    int nn[1000];
    srand(time(NULL));

    i=0;
    while(EOF!=scanf(" %f %f %f %f %d", x[i], x[i]+1, x[i]+2, x[i]+3, y+i)) {
        //printf("%f %f %f %f %d\n", x[i][0], x[i][1], x[i][2], x[i][3], y[i]);
        i++;
    }
    n=i;
    for(i=0;i<n;i++) nn[i]=i;
    shuf(nn, n);
    k=0;
    flag=1;
    while(flag) {
      flag=0;
      shuf(nn, n);
      for(i=0;i<n;i++) {
        p=nn[i];
        s=w[4];
	for(j=0;j<4;j++) s+=x[p][j]*w[j];
	if(s*y[p]>0) continue;
	//printf("%d %f %f\n", y[i], s, s*y[i]);
	flag=1;
	k++;
	for(j=0;j<4;j++) w[j]+=y[p]*x[p][j];
	w[4]+=y[p];
      }
    }
    for(j=0;j<5;j++) printf("%f ", w[j]);
    printf("\nupdate=%d\n",k);
}
