#include <stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#include<mt.h>

#define LENGTH 10UL // length of the lattice
#define DROP_LOCAT 5UL // top up cell number in array count
#define N_ROLLS 100UL  // number of experiments -- balls to drop

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

int iii;
printf("\nrand_count: ");
for(iii=0; iii<LENGTH; iii++)
{printf("%i", rand_count[iii]);}


return rand_test/RAND_MAX;
}
// end of test fun and array

int i, k, drop;

// functions

// do macros

void stack_push(int cell_num) {
  //printf("\npush init SX id:  %i  ", stack_used);
stack[stack_used] = cell_num;
stack_used++;
  //printf("\npush new SX id:  %i  ", stack_used);
/*
printf("\nSX:  ");
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", stack[k]); 
    }

printf("\nLT:  ");
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");*/
}

int stack_pop()  {
//  printf("\npop init SX id:  %i  ", stack_used);
int bu, k;
stack_used--;
bu = stack[stack_used];

// printf("\nnum to ret from pop:  %i  ", bu);
stack[stack_used] = 0;


//printf("\npop new SX id:  %i  ", stack_used);

/*
printf("\nSX:  ");
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", stack[k]); 
    }

printf("\nLT:  ");
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");*/

return bu;
}

int move_ball(int location) {
int dir;
int dist1 = rand_call(location)*2;  //make 1
double  dir1 = rand_call(location);
if(dir1 < 0.5) {dir = (-1);} else {dir = 1;}
//printf("\ndir1:  %i", dir);
int new_location = location + dir*(int)dist1;//(int) (dist1*dir1);
printf("\nnew_loc: %i= (%i+%i*%i)", new_location, location, dir, (int)dist1);
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
//printf("UPD Lattice(%i) = %i", cell_num, lattice[cell_num]);

}



int main() {
  //sgenrand(time(NULL));
 int k, curr_pos, check;

 for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle
/*
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    printf("\n lat - start of dropping");
    }
 printf("\n"); */
printf("\n %i ball dropped \n", drop);

 printf("\n lat - start of dropping:  ");
 
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

 printf("\n %i ball dropped \n", drop);

 printf("\n lat - AFTER of dropping:  ");

 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");


  while(stack_used != 0) {
    curr_pos = stack_pop();




    do {
      
      curr_pos = move_ball(curr_pos);
      printf("\nnew_pos in do cycle = %i", curr_pos);  //ERROR HERE??????
      //printf("\nUPD location:  %i", curr_pos);
      if(curr_pos < LENGTH || curr_pos >= 0)  {
        check = 0 ;
        }
      if(curr_pos < LENGTH && curr_pos >= 0) {
        check = check_cell(curr_pos);
        
        if (check == 1) {
          stack_push(curr_pos);
          }
      else {
        check = 0;

      //    printf("SX i", stack_used);}
       }

    } 
  }while(check != 0);


}
}

 printf("\n FINAL LATTICE:  ");

 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");
}

