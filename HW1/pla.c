#include <stdio.h>

int main()
{
    int i, j, k, n, flag;
    float x[1000][4];
    int y[1000];
    float w[5]={0.0};
    float s, delta=1.0;

    i=0;
    while(EOF!=scanf(" %f %f %f %f %d", x[i], x[i]+1, x[i]+2, x[i]+3, y+i)) {
        //printf("%f %f %f %f %d\n", x[i][0], x[i][1], x[i][2], x[i][3], y[i]);
        i++;
    }
    n=i;
    k=0;
    flag=1;
    while(flag) {
      flag=0;
      for(i=0;i<n;i++) {
        s=w[4];
	for(j=0;j<4;j++) s+=x[i][j]*w[j];
	if(s*y[i]>0) continue;
	//printf("%d %f %f\n", y[i], s, s*y[i]);
	flag=1;
	k++;
	for(j=0;j<4;j++) w[j]+=y[i]*x[i][j]*delta;
	w[4]+=y[i]*delta;
      }
    }
    for(j=0;j<5;j++) printf("%f ", w[j]);
    printf("\nupdate=%d\n",k);
}
