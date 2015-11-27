#include <stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#include<mt.h>

#define LENGTH 10UL // length of the lattice
#define DROP_LOCAT 5UL // top up cell number in array count
#define N_ROLLS 15000UL  // number of experiments -- balls to drop

//globals

int lattice[LENGTH] = {[0 ... LENGTH-1] = 0};

int i, ii, k, drop;


//test function and array
int rand_count[LENGTH] = {[0 ... LENGTH-1] = 0};


double rand_call(int cell_num) {
int seed = cell_num*100000 + rand_count[cell_num];
rand_count[cell_num]++;
srand(seed);
double rand_test = rand();
return rand_test/RAND_MAX;
}
// end of test fun and array

int main()  {


//srand_call(time(NULL));
int count_full = 0;
int array_full[LENGTH];
int position;
int check;
/*
  for(k = 0; k<LENGTH; k++) {
    printf("%i", lattice[k]); 
    }
  printf(" --- End of initialisation\n");   */

  for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle
 
  //printf("\n\n\n");
 for(k = 0; k<LENGTH; k++) {
    printf("\%i", lattice[k]); 
    }
  printf(" \n");   

  lattice[DROP_LOCAT] = lattice[DROP_LOCAT] + 1;  //actual drop in the drop location
  
  //printf("\n %i Ball dropped\n", drop);  
 /*
  for(k = 0; k<LENGTH; k++) {
    printf("%i", lattice[k]); 
    } */

check = 1;

while (check != 0) {
count_full = 0;
for (k = 0; k<LENGTH; k++) {
    if (lattice[k] > 1) {
    //printf("\nDouble found in %i cell", k);
    array_full[count_full] = k;
    count_full++;
    check = 1;
    }
   else {
    check = 0;}
   }

for (i = 0; i < count_full; i++) {
      /*
      printf("\nEnter the shooting cycle, balls to shoot from:");
      for ( ii = 0; ii < count_full; ii++) {printf("  %i", array_full[ii]);} */
      // draw 2 rand nums
      int dist1 = rand_call(i)*2; 
      int dist2 = rand_call(i)*2;
      
       // convert to distr

       // define direction
      double  dir1 = rand_call(i)*2;
      double  dir2 = rand_call(i)*2;
      if(dir1 < 0.5) {dir1 = (int)-1;} else {dir1 = (int)1;}
      if(dir2 < 0.5) {dir2 = (int)-1;} else {dir2 = (int)1;}

      //printf("\nBall 1 from cell %i moves: %i (%i,%i)", array_full[i], (int)dist1*(int)dir1, (int)dist1, (int)dir1);
      //printf("\nBall 2 from cell %i moves: %i  (%i,%i)\n", array_full[i], (int)dist2*(int)dir2, (int)dist2,(int)dir2);

      // shoot 2 balls
      if(array_full[i]+dist1*dir1 < LENGTH && array_full[i]+dist1*dir1 >= 0) {
         lattice[array_full[i]+(int)dist1*(int)dir1] = lattice[array_full[i]+(int)dist1*(int)dir1] + 1;
         }
      if(array_full[i]+dist2*dir2 < LENGTH && array_full[i]+dist2*dir1 >= 0) {
         lattice[array_full[i]+(int)dist2*(int)dir2] = lattice[array_full[i]+(int)dist2*(int)dir2] + 1;
         }
      // decrease initial slot by 2
      lattice[array_full[i]] = lattice[array_full[i]] - 2;
/*      
      printf("Final standing after %i shooting:  ", array_full[i]);
      for(k = 0; k<LENGTH; k++) {printf("%i", lattice[k]); } 
*/
      check = 1;}
    }
  } 

 
}


