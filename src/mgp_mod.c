#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
/* Had to change this to compile. 
 cc -Wall -o manna_stack_clean_edited manna_stack_clean_edited.c mt19937ar_clean_bkp.c

 *
 * */
#include "mt19937ar_clean_bkp.h"


#define SEED (5UL)
#define LENGTH (10UL) // length of the lattice
#define DROP_LOCATION (LENGTH/2) // top up cell number in array count
#define N_ROLLS (123000UL)  // number of experiments -- balls to drop
#define NUM_CHUNKS (100)
#define GOD 1// 1 for gp, 0 for dv

//globals

int lattice[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack_used = 0;
int stop = 0;

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

// do macros

void stack_push(int cell_num) {
stack[stack_used] = cell_num;
stack_used++;
}

int stack_pop()  {
stack_used--;
return stack[stack_used];
}

int move_ball(int location) {
int dir;
int dist1 = 1; // rand_call(location)*2;  //make 1
double  dir1 = rand();  //rand_call(location);
if(dir1 < 0.5) {dir = (-1);} else {dir = 1;}
int new_location = location + dir*(int)dist1;
//printf("From %i to %i\n", location, new_location);

return new_location;
}

int check_cell(int cell_num) {
if(lattice[cell_num] == 0)  {
  lattice[cell_num] = 1;
  return 0;
  }
else  {
/* Toppling occurs. */
  size++;
  lattice[cell_num] = 0;
  return 1;
  }
}


#define MOMENTS_PREAMBLE_FMT "%lu %lu %lu %i %i " RNG_TYPE_OUT 
#define MOMENTS_PREAMBLE_ARGS LENGTH, DROP_LOCATION, N_ROLLS, chunk, NUM_CHUNKS, SEED, /* last one is the seed */

#include "gp.h"

MOMENTS_DECL(size, 8);


int main(int argc, char *argv[]) {
  //sgenrand(time(NULL));
 int k, curr_pos, check;
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

size=0;

/*
printf("(%i.)", drop);
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");
*/

#if (0)

#define PUSH(a) stack[stack_used++]=(a)
#define POP(a)  (a)=stack[--stack_used]




 if(check_cell(DROP_LOCATION) == 1) {
      PUSH(DROP_LOCATION); 
      PUSH(DROP_LOCATION);
  //    lattice[DROP_LOCATION] = 0;
 }

lattice[DROP_LOCATION] = 1 - lattice[DROP_LOCATION];

/* If validated, optimse by turning stack operations into macros, 
 * optime random number drawing (rather than having doubles in the tree
 * have integers there and draw an integer to compare against),
 * optimise the shuffling of particles. 
 *
 * I have added MOMENT macros for size. */

  while(stack_used != 0) {
    POP(curr_pos);
    stop++;


/* This code with the "check" looks clumsy. I suppose
 * you are "following through" topplings? I would think
 * there is no point doing this later. Anyway, we validate
 * this code and take it from there. */
    do {
      curr_pos = curr_pos+ ( (rand()>RAND_MAX/2) ? 1 : -1); //move_ball(curr_pos);


      if((curr_pos>=0) && (curr_pos<LENGTH)) {
      lattice[curr_pos] = 1- lattice[curr_pos];

     if(lattice[curr_pos] == 0)  {
        size++;
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
	npos=curr_pos+ ( (rand()>RAND_MAX/2) ? 1 : -1);
	if ((npos>=0) && (npos<LENGTH)) {
	  if (lattice[npos]++==1) {PUSH(npos);}
          }
        npos=curr_pos+ ( (rand()>RAND_MAX/2) ? 1 : -1);
	if ((npos>=0) && (npos<LENGTH)) {
	  if (lattice[npos]++==1) {PUSH(npos);}
	}
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

printf("Stack calls: %i", stop);
}

