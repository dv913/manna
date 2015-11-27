#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


int main() {
srand(clock());

int hist[4];
int i, ii;

for(ii=0; i<10000; i++){
int test_num=rand();

for(i=0; i<31;i++){
int lsb=i;
int msb=lsb+1;


int result=(test_num>>lsb) &~(~0<<(msb-lsb+1));
printf("\n %i", result);
//int r=(2<<1)&test_num;
hist[result]++;

}
}

for(i=0;i<4;i++){
printf("\nhist[%i]:  %i", i, hist[i]);

}
printf("\n");
}
