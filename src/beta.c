#include <stdio.h>
#include<time.h>
#include<math.h>

#include<mt.h>

#define RUNS 10000000

//globals

double xxX[] = {0.25, 0.25, 0.25, 0.25};  
double xX[1<<10] = {[0 ... (1<<10)-1] = 1};  
int xxxX[] = {1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16,1, 2, 3, 4, 5, 6, 7, 8,9,10,11,12,13,14,15,16};



int main ()  {

//////////////////////////test function starts\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char buffer[1024];
FILE *fp = fopen("test.dat", "r");
int num, i;
char comment[20];
char arr_data[800];
int fin_num;
for(i=0; i<799; i++){arr_data[i] = 'x';}
int run = 0;



//read file into num of test, comments and number char array
while (fgets(buffer, sizeof(buffer), fp) != NULL) {
  
  sscanf(buffer, "%i;%s %s", &num, comment, arr_data);  
  printf( "\n%i:  %s\n", num, arr_data  );

  int k = 0;
//count the number of numbers in the char array
  int num_count = 1; //one comma less then numbers
  while(arr_data[k] != 0 ) {
    if(arr_data[k] == ',') {num_count++;}
    k++;
    }

  printf("Nums in the array: %i", num_count);
//initialise double array
  int data[num_count]; // = {[0 ... num_coun] = 0};

  //converting char array to int array
  int acc_len = 0;
  for(i=0; i<num_count; i++){
    fin_num = 0;
    int num_len = 0;
    while(arr_data[acc_len+num_len] != ',' && arr_data[acc_len+num_len] != 0){num_len++;}
    //printf("\n%i's num lenght is %i ,", i, num_len);
    acc_len = acc_len + num_len +1;
    //printf("  start of next number is %i", acc_len);
    int decim;
    for(decim = acc_len - num_len -1; decim < acc_len -1; decim++){
        int d = arr_data[decim] - '0';
        int pow_c;
        int out = 1;
           for(pow_c = 0; pow_c <acc_len-decim-2; pow_c++) {out = out*10;}
        //printf("\nNumber %i for %i", out*d, d);  //(acc_len-decim-2)
        fin_num = fin_num + out*d;
        //printf("\nResulting number:  \n%i on inter %i", fin_num, decim);
        if(decim == acc_len -2) {
          data[i] = fin_num; 
          //printf("NUM FROM ARRAY: %i", data[i]);
          }
       }
      //printf("\n");
      }
  printf("\nPrinting array as int array: ");
  
    printf("\n");
//transferring data to X array
int X[num_count];

  for(i=0; i<num_count; i++){
    X[i] = data[i];}
//////////////////////////test function ends\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


int x_n = (int)(sizeof(X)/sizeof(*X));   
int depth = (int) ((log(x_n)+0.1)/log(2)); 

double tree[depth][x_n];
double cdf[x_n];
int histogram[sizeof(X)/sizeof(*X)] ;  //={0}
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
printf("cdf: ");
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


// tree walk
int err_count = 0;

int jj;
sgenrand(5UL);
clock_t start = clock(), diff;
for(jj=0; jj<RUNS; jj++) {  //TEST START  
double test_num = genrand() * cdf[x_n - 1];

//tree walk

int x_pos = 0, y_pos = 0;

//if (0) {
for(y_pos = 0; y_pos < depth ; y_pos++)  {
  if (test_num > tree[y_pos][x_pos])  {x_pos = (x_pos+1) * 2 - 1; } else {x_pos = x_pos * 2;}
  //printf("\nThe current position is : %i, %i", y_pos, x_pos);
  }
histogram[x_pos]++;
//}

}

clock_t start_w = clock(), diff_w;
int msec = diff*1000/CLOCKS_PER_SEC;
printf("\nThe tree cycle timing: %d seconds and %d milsec", msec/1000, msec%1000);

//printf("testnum %g\n", test_num);

// check using scan of the cdf array -- TEST
sgenrand(5UL);
 start = clock();
for(jj=0; jj<RUNS; jj++) { 
int cluster = 0;
double test_num = genrand() * cdf[x_n - 1];

//if (1) {
while(test_num > cdf[cluster]) {cluster++;}
histogram[cluster]++;
//}
}

diff_w = clock() - start_w;
int msec_w;
msec_w = diff_w*1000/CLOCKS_PER_SEC;
printf("\nThe while cycle timing: %d seconds and %d milsec", msec_w/1000, msec_w%1000);



//printf("cluster: %i\n", cluster);

/*if(0)
if(cluster != x_pos) {

printf("\nThe drawn number is: %f", test_num);
printf("\nTree dislocation is: %i", x_pos );
printf("\nTest dislocation: %i \n", cluster );
err_count++;
}*/



printf("ERRORS: %i \n", err_count);

//for (i=0; i<x_n; i++) 
//  printf("histogram[%i] %i\n", i, histogram[i]);
///////////////////////////test function starts \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    

  for(i=0; i<799; i++){arr_data[i] = 'x';}  //clean up the arr_data
  printf("\n");
  run++;
 }

//////////////////////////test function ends\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  fclose(fp);
}  // MAIN END

