#include <stdio.h>
#include<time.h>
#include<math.h>

#include<mt.h>

//globals

double xX[] = {0.25, 0.25, 0.25, 0.25};  
double X[1<<10] = {[0 ... (1<<10)-1] = 1};  
int xxxX[] = {1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16};



int main ()  {

int x_n = (int)(sizeof(X)/sizeof(*X));   
int depth = (int) ((log(x_n)+0.1)/log(2)); 

double tree[depth][x_n];
double cdf[x_n];
int histogram[sizeof(X)/sizeof(*X)] ={0};
int step_size;
int num_of_points;
int position_num;

int i, j;

//pdf to cdf

cdf[0] = X[0];
for (i = 1; i < x_n; i++)  {
cdf[i] = cdf[i - 1] + X[i]; 
}

//print cdf

for(i = 0; i < x_n; i++) { printf("%g ",  cdf[i]); }
printf("\n");

// cdf to tree array

for(i = 0; i < depth; i++)  {

  step_size = x_n/pow(2, i);
  num_of_points = pow(2, i);
  position_num;

  for(j = 0; j < num_of_points; j++)  {
    if(j == 0) {position_num = step_size *(j + 1)* 0.5 - 1;} 
    else {position_num = step_size *j + step_size * 0.5 - 1;}  
    tree[i][j] = cdf[position_num];
    printf(" %g |", tree[i][j]);
  }
printf("\n");

}

printf("\n");

//tree array check
/*
for ( i = 0; i < depth; i++ ) { 
  printf("\n");
  for ( j = 0; j < x_n; j++ )  {  
    printf("T[%d][%d] = %f  ", i,j, tree[i][j] );
    }
}  */


// random number draw

sgenrand(5UL);
int err_count = 0;

int jj;

for(jj=0; jj<10000000; jj++) {  //TEST START
double test_num = genrand() * cdf[x_n - 1];

//tree walk

int x_pos = 0, y_pos = 0;

if (0) {
for(y_pos = 0; y_pos < depth ; y_pos++)  {
  if (test_num > tree[y_pos][x_pos])  {x_pos = (x_pos+1) * 2 - 1; } else {x_pos = x_pos * 2;}
  //printf("\nThe current position is : %i, %i", y_pos, x_pos);
  }
histogram[x_pos]++;
}

//printf("testnum %g\n", test_num);

// check using scan of the cdf array -- TEST
 int cluster = 0;
if (1) {
while(test_num > cdf[cluster]) {cluster++;}
histogram[cluster]++;
}



//printf("cluster: %i\n", cluster);

if(0)
if(cluster != x_pos) {

printf("\nThe drawn number is: %f", test_num);
printf("\nTree dislocation is: %i", x_pos );
printf("\nTest dislocation: %i \n", cluster );
err_count++;


}

}

printf("ERRORS: %i \n", err_count);

for (i=0; i<x_n; i++) 
  printf("histogram[%i] %i\n", i, histogram[i]);

}  // MAIN END
