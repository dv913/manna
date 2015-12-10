/*
*DSF+stack implementation for Manna model
*for "degenerate tree" with possible LR+RL, LL, RR
*relocations of the participles
*using boolean rand from gp.h
 *As of Dec 9 2015
*/


#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
/* Had to change this to compile. 
 cc -Wall -o manna_stack_clean_edited manna_stack_clean_edited.c mt19937ar_clean_bkp.c
 */
#include "mt19937ar_clean_bkp.h"
#include "gp.h"

#include <stdbool.h>
#include "c.h"


#define SEED (5UL)
#define LENGTH (10UL) // length of the lattice
#define DROP_LOCATION (LENGTH/2) // top up cell number in array count
#define N_ROLLS (123000UL)  // number of experiments -- balls to drop
#define NUM_CHUNKS (100)


//globals

int lattice[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack_used = 0;

//test function and array
int rand_count[LENGTH] = {[0 ... LENGTH-1] = 0};

double rand_call(int cell_num) {
return ((double)rand())/((double)RAND_MAX);
int seed = cell_num*10000 + rand_count[cell_num];
rand_count[cell_num]++;
srand(seed);
double rand_test = rand();
return rand_test/RAND_MAX;
}

int i, k, drop;
long long int size;

// functions

int move_ball(int location) {
int dir;
int dist1 = 1; // rand_call(location)*2;  //make 1
double  dir1 = rand();  //rand_call(location);
if(dir1 < 0.5) {dir = (-1);} else {dir = 1;}
int new_location = location + dir*(int)dist1;
return new_location;
}

#define MOMENTS_PREAMBLE_FMT "%lu %lu %lu %i %i " RNG_TYPE_OUT 
#define MOMENTS_PREAMBLE_ARGS LENGTH, DROP_LOCATION, N_ROLLS, chunk, NUM_CHUNKS, SEED, /* last one is the seed */

MOMENTS_DECL(size, 8);


int main(int argc, char *argv[]) {



//global timing
clock_t start_g=clock(), diff_g;


//////////////////////////test function starts\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char buffer[1024];
FILE *fp = fopen("dist.in", "r");
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
  for(i=0; i<num_count; i++){
    printf("%i,", data[i]);}
    printf("\n");
//transferring data to X array
int X[num_count];

  for(i=0; i<num_count; i++){
    X[i] = data[i];}
//////////////////////////end of file to array parsing\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


int x_n = (int)(sizeof(X)/sizeof(*X));   
int depth = (int) ((log(x_n)+0.1)/log(2)); 

double tree[depth][x_n];
double cdf[x_n];
int histogram[sizeof(X)/sizeof(*X)] ;
int ddd;
for (ddd=0; ddd<x_n; ddd++) {histogram[ddd] =0;}
int hist[sizeof(X)/sizeof(*X)] ;
int step_size;
int num_of_points;
int position_num;

int i, j;

//pdf to cdf

cdf[0] = X[0];
for (i = 1; i < x_n; i++)  {
cdf[i] = cdf[i - 1] + X[i]; 
}

//normalised cdf
for (i = 0; i < x_n; i++)  {
cdf[i] = cdf[i]/cdf[x_n-1]; 
}

//print cdf
printf("cdf: ");
for(i = 0; i < x_n; i++) { printf("%g ",  cdf[i]); }
printf("\n");

// cdf to tree array
printf("TREE OUTPUT:\n ");
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
//int err_count = 0;

int jj;

//global timing






//sgenrand(time(NULL));
int curr_pos, check;
int chunk; /* Repeat experiment in chunks. */
srand(SEED);

printf("# Info: $Header: /home/ma/p/pruess/.cvsroot/manna_range/dmitry_20151021/manna_stack_clean_edited.c,v 1.2 2015/10/21 11:37:00 pruess Exp $\n");
preamble(argc, argv);

PRINT_PARAM(SEED, "%lu");
PRINT_PARAM(LENGTH, "%lu");
PRINT_PARAM(DROP_LOCATION, "%lu");
PRINT_PARAM(total_malloced, "%lli");


printf("# Info: Expected avalanche size: <s>(x) = 1+(1/2) (<s>(x+1)+<s>(x-1)), BC <s>(0)=0, <s>(L+1)=0, solved by <s>(x)=(L+1-x)x/2.\n");
printf("# Info: Here L=LENGTH=%lu and x=DROP_LOCATION+1=%lu, so expect %g\n", LENGTH, DROP_LOCATION+1, ((double)(DROP_LOCATION+1))*((double)(LENGTH-DROP_LOCATION))/2.);


for (chunk=1; ((chunk<=NUM_CHUNKS) || (NUM_CHUNKS<0)); chunk++) {
MOMENTS_INIT(size);
for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle

long long int size=0;

#if (0)

#define PUSH(a) stack[stack_used++]=(a)
#define POP(a)  (a)=stack[--stack_used]

if(lattice[DROP_LOCATION] == 0) {
      lattice[DROP_LOCATION] = 1;
      }
 else {
      PUSH(DROP_LOCATION); 
      PUSH(DROP_LOCATION);
      lattice[DROP_LOCATION] = 0;
      size++;
 }

/* If validated, optimse by turning stack operations into macros, 
 * optime random number drawing (rather than having doubles in the tree
 * have integers there and draw an integer to compare against),
 * optimise the shuffling of particles. 
 *
 * I have added MOMENT macros for size. */

  while(stack_used != 0) {
    POP(curr_pos);
/* This code with the "check" looks clumsy. I suppose
 * you are "following through" topplings? I would think
 * there is no point doing this later. Anyway, we validate
 * this code and take it from there. */
    do {

double test_num = ((double)rand())/((double)RAND_MAX);

//tree walk
int x_pos = 0, y_pos = 0;

for(y_pos = 0; y_pos < depth ; y_pos++)  {
  if (test_num > tree[y_pos][x_pos])  {x_pos = (x_pos+1) * 2 - 1; } else {x_pos = x_pos * 2;}
  //printf("\nThe current position is : %i, %i", y_pos, x_pos);
  }

      curr_pos = curr_pos+ x_pos-1; //move_ball(curr_pos);
      //printf("\nshift: %i, RAND: %f", x_pos-1, test_num);
 
      if((curr_pos>=0) && (curr_pos<LENGTH)) {
        if(lattice[curr_pos] == 0)  {
          lattice[curr_pos] = 1;
          }
        else  {
          size++;
          lattice[curr_pos] = 0;
          PUSH(curr_pos);
        }
    } 
    else {break;}
  }while( (lattice[curr_pos] != 1));
}/* end of while(stack_used != 0) look */
#endif

#if (1)
{
int npos;

#define PUSH(a) stack[stack_used++]=(a)
#define POP(a)  (a)=stack[--stack_used]

if (lattice[DROP_LOCATION]++==1) {
  PUSH(DROP_LOCATION);

    while(stack_used) {
      POP(curr_pos);
      do {
        size++;
	lattice[curr_pos]-=2;
	//bool t= RNG_MT_BOOLEAN;
	if (RNG_MT_BOOLEAN==0) {  //rand()>RAND_MAX/2
	npos=curr_pos+1;
	if ( (npos<LENGTH)) {
	  	if (lattice[npos]++==1) {PUSH(npos);}
		}
	npos=curr_pos-1;
	if ((npos>=0) ) {
	  	if (lattice[npos]++==1) {PUSH(npos);}
		}
	}
	else {
		if (RNG_MT_BOOLEAN==0) {
			npos=curr_pos+1;
			if ( (npos<LENGTH)) {
	  			if (lattice[npos]++==1) {PUSH(npos);}
				if (lattice[npos]++==1) {PUSH(npos);}
				//PUSH(npos);
			}
		}
		else {
			npos=curr_pos-1;
			if ((npos>=0) ) {
	  			if (lattice[npos]++==1) {PUSH(npos);}
				if (lattice[npos]++==1) {PUSH(npos);}
				//PUSH(npos);
			}
		}
	
	}
// start of modified piece
/*
	npos=curr_pos+ ( (rand()>RAND_MAX/2) ? 1 : -1);
	if ((npos>=0) && (npos<LENGTH)) {
	  if (lattice[npos]++==1) {PUSH(npos);}
	}
        npos=curr_pos+ ( (rand()>RAND_MAX/2) ? 1 : -1);
	if ((npos>=0) && (npos<LENGTH)) {
	  if (lattice[npos]++==1) {PUSH(npos);}
	}
*/
// end of modified piece
      } while (lattice[curr_pos]>1);
    }
  }
}
#endif

//printf("size is %i\n", size);
MOMENTS(size,size);
} /* end of iterations loop */
MOMENTS_OUT(size);

} /* chunk */
postamble();
}
}

