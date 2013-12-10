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

int main(int argc, char* argv[])
{
    //FILE* train=fopen(argv[1], "r");
    FILE* test=fopen(argv[1], "r");
    int i, j, k, n, p, d, bd, flag;
    float x[1000][4];
    int y[1000];
    float w[5]={0.0};
    float bw[5]={0.0};
    float s;
    float x1, x2, x3, x4;
    int nn[1000];
    srand(time(NULL));

    i=0;
    while(EOF!=scanf(" %f %f %f %f %d", x[i],x[i]+1,x[i]+2,x[i]+3,y+i)) {
        //printf("%f %f %f %f %d\n", x[i][0], x[i][1], x[i][2], x[i][3], y[i]);
        i++;
    }
    n=i;
    for(i=0;i<n;i++) nn[i]=i;
//    shuf(nn, n);
    k=0;
    flag=1;
    bd=0;
    while(flag && k<100) {
//      flag=0;
//      shuf(nn, n);
//      for(i=0;i<n;i++) {
//        p=nn[i];
        p=rand()%n;
        s=w[4];
	for(j=0;j<4;j++) s+=x[p][j]*w[j];
	if(s==0) s=-1;
	if(s*y[p]>0) continue;
	//printf("%d %f %f\n", y[i], s, s*y[i]);
//	flag=1;
	k++;
	for(j=0;j<4;j++) w[j]+=y[p]*x[p][j];
	w[4]+=y[p];

        d=0;
	for(i=0;i<n;i++) {
	    s=w[4];
	    for(j=0;j<4;j++) s+=x[i][j]*w[j];
	    if(s==0) s=-1;
	    if(s*y[i]>0) d++;
	}
	if(d>bd) {
	    for(j=0;j<5;j++) bw[j]=w[j];
	    bd=d;
	}
//	if(k>=50) break;
//      }
    }
//    for(j=0;j<5;j++) printf("%f ", bw[j]);
//    printf("%d\n",bd);
    //printf("\nupdate=%d\n",k);
    n=0; k=0;
    while(EOF!=fscanf(test, " %f %f %f %f %d", &x1, &x2, &x3, &x4, &p)) {
        n++;
	s=x1*w[0]+x2*w[1]+x3*w[2]+x4*w[3]+w[4];
	//s=x1*bw[0]+x2*bw[1]+x3*bw[2]+x4*bw[3]+bw[4];
	if(s==0) s=-1;
	if(s*p>0) k++;
    }
    printf("%f\n", (float)k/n);
}
