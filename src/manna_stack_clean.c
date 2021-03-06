#include <stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#include<mt.h>

#define LENGTH 100UL // length of the lattice
#define DROP_LOCAT 49UL // top up cell number in array count
#define N_ROLLS 200UL  // number of experiments -- balls to drop

//globals

int lattice[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack[LENGTH] = {[0 ... LENGTH-1] = 0};
int stack_used = 0;

//test function and array
int rand_count[LENGTH] = {[0 ... LENGTH-1] = 0};


double rand_call(int cell_num) {
int seed = cell_num*10000 + rand_count[cell_num];
rand_count[cell_num]++;
srand(seed);
double rand_test = rand();
return rand_test/RAND_MAX;
}

int i, k, drop;

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
int dist1 = rand_call(location)*2;  //make 1
double  dir1 = rand_call(location);
if(dir1 < 0.5) {dir = (-1);} else {dir = 1;}
int new_location = location + dir*(int)dist1;//(int) (dist1*dir1);

return new_location;
}

int check_cell(int cell_num) {
if(lattice[cell_num] == 0)  {
  lattice[cell_num] = 1;
  return 0;
  }
else  {
  lattice[cell_num] = 0;
  return 1;
  }
}



int main() {
  //sgenrand(time(NULL));
 int k, curr_pos, check;

for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle

printf("(%i.)", drop);
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");

 if(check_cell(DROP_LOCAT) == 0) {
      lattice[DROP_LOCAT] = 1;
      }
 else {
      stack_push(DROP_LOCAT); 
      stack_push(DROP_LOCAT);
      lattice[DROP_LOCAT] = 0;
 }

  while(stack_used != 0) {
    curr_pos = stack_pop();

    do {
      curr_pos = move_ball(curr_pos);

      if(curr_pos >= LENGTH || curr_pos < 0)  {
        check = 0 ;
        }
      if(curr_pos < LENGTH && curr_pos >= 0) {
        check = check_cell(curr_pos);
        
        if (check == 1) {
          stack_push(curr_pos);
          }
      else {
        check = 0;
        }

    } 
  }while(check != 0);


  }
}
}

