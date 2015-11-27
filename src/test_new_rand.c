#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


int main() {

int hist[4]={0};
int test_num;
int counter=0;
int new_rand() {
if(counter>30) {counter=0;}
if(counter==0) {int test_num=rand();}


int lsb=counter;
int msb=lsb+0;

int result=(test_num>>lsb) &~(~0<<(msb-lsb+1));
counter++;
return result;

}

int i;

for(i=0; i<10000000;i++){
int r=new_rand();

hist[r]++;

}

for(i=0; i<4;i++){

printf("\nhist[%i]: %i", i, hist[i]);

}


printf("\n");


}
