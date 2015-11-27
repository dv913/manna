#include <stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#include<mt.h>

#define LENGTH 10UL // length of the lattice
#define DROP_LOCAT 5UL // top up cell number in array count
#define N_ROLLS 10UL  // number of experiments -- balls to drop

//globals

int lattice[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack_used = 0;

//test function and array
int rand_count[LENGTH] = {[0 ... LENGTH-1] = 0};


double rand_call(int cell_num) {
int seed = cell_num*100000 + rand_count[cell_num];
rand_count[cell_num]++;
srand(seed);
double rand_test = rand();
return rand_test;
}
// end of test fun and array

int i, k, drop;

// functions



void stack_push(int cell_num) {
stack[stack_used] = cell_num;
stack_used++;
}

int stack_pop()  {
stack_used--;
return stack[stack_used];
}

int move_ball(int location) {
int dist1 = genrand()*2; 
double  dir1 = genrand();
if(dir1 < 0.5) {dir1 = (int)-1;} else {dir1 = (int)1;}
int new_location = location + (int) (dist1*dir1);
return new_location;
}

int check_cell(int cell_num) {
if(lattice[cell_num] == 0)
  return 0;
else
  return 1;
}



int main() {
  //sgenrand(time(NULL));
  int k, curr_pos;

  for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle

 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
printf("\n");

    if(check_cell(DROP_LOCAT) == 0){
      lattice[DROP_LOCAT] = 1;
      }
    else {
      stack_push(DROP_LOCAT); 
      stack_push(DROP_LOCAT);
      lattice[DROP_LOCAT] = 0;}

 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
printf("\n");
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", stack[k]); 
    }
printf("\nstack ind %i", stack_used);

printf("\n");

  while(stack_used != 0) {
    curr_pos = stack_pop();
    int check = 1;

    while(check != 0){
      curr_pos = move_ball(curr_pos);

      if(curr_pos < LENGTH && curr_pos >= 0) {
        check = check_cell(curr_pos);

        if (check == 0){
          lattice[curr_pos] = 1;
           }
        if (check == 1) {
          stack_push(curr_pos);
          lattice[curr_pos] = 0;
printf("\nstack ind %i, state:", stack_used);
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", stack[k]); 
    }

          }
       }
      else {
        check = 0;}
   }
  }


}
}

