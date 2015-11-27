#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


int main() {
srand(15UL);

int hist[4]={0};
int i, ii;


for(ii=0; ii<10000000; ii++){
int test_num=rand();

for(i=0; i<31;i++){
int lsb=i;
int msb=lsb+0;


int result=(test_num>>lsb) &~(~0<<(msb-lsb+1));
//printf("\n %i", result);
//int r=(2<<1)&test_num;
hist[result]++;

}
}

for(i=0;i<4;i++){
printf("\nhist[%i]:  %i", i, hist[i]);

}
printf("\n");
}
