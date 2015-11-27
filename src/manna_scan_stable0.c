#include <stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<mt.h>

#define L 100UL // length of the lattice minus 1
#define C 49UL // top up cell number in array count
#define N_ROLLS 200UL  // number of experiments -- balls to drop

//test function and array
int rand_count[L] = {[0 ... L-1] = 0};

double rand_call(int cell_num) {
int seed = cell_num*1000 + rand_count[cell_num];
rand_count[cell_num]++;
srand(seed);
double rand_test = rand();

/*int iii;
printf("\nrand_count: ");
for(iii=0; iii<L; iii++)
{printf("%i", rand_count[iii]);} */

return rand_test/RAND_MAX;
}



int main()  {
 
  int lattice[L] = {[0 ... L-1] = 0};
  int i, drop;
  int k;

/*
  for(k = 0; k<L; k++) {printf("%i", lattice[k]); }
  printf(" --- End of initialisation\n");   
*/
  //sgenrand(time(NULL));

  for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle
//  printf("*");

printf("(%i.)", drop);
 for(k = 0; k<L; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");

  lattice[C] = lattice[C] + 1;  //actual drop in the drop location

  //printf("\n");
  //for(k = 0; k<L; k++) {printf("%i", lattice[k]); } // check after initial drop
  //printf( " --- After %i drops************************************", drop+1);  

  for (i = 0; i < L; i++) {

    if (lattice[i] > 1) //check slots > 1
     {  
      // draw 2 rand nums
      int dist1 = rand_call(i)*2; 
      double  dir1 = rand_call(i);

      int dist2 = rand_call(i)*2;
      
       // convert to distr

       // define direction
      
      double  dir2 = rand_call(i);
      if(dir1 < 0.5) {dir1 = (int)-1;} else {dir1 = (int)1;}
      if(dir2 < 0.5) {dir2 = (int)-1;} else {dir2 = (int)1;}
/*if(drop == 4) {
      printf("\nBall 1 from cell %i moves: %i (%i,%i)", i, (int)dist1*(int)dir1, (int)dist1, (int)dir1);
      printf("\nBall 2 from cell %i moves: %i  (%i,%i)\n", i, (int)dist2*(int)dir2, (int)dist2,(int)dir2);
}*/
       


      // shoot 2 balls
      if(i+(int)dist1*(int)dir1 < L && i+(int)dist1*(int)dir1 >= 0) {lattice[i+(int)dist1*(int)dir1] ++;}
/*
   for(k = 0; k<L; k++) {
    printf("\%i", lattice[k]); 
    }
     printf("\n");
*/
      if(i+(int)dist2*(int)dir2 < L && i+(int)dist2*(int)dir2 >= 0) {lattice[i+(int)dist2*(int)dir2] ++;}


      // decrease initial slot by 2
      lattice[i] = lattice[i] - 2;


      //printf("Final standing after shooting:  ");
      //for(k = 0; k<L; k++) {printf("%i", lattice[k]); } 

      // restart array check from beginning
      i = -1 ;  // account for autoincrement
      }  

    //else {printf("\nNothing to shoot from cell %i", i); }  

    }
  } 

/*
 printf("\n FINAL LATTICE:  ");
*/
//int k; 
/* for(k = 0; k<L; k++) {
    printf("\%i", lattice[k]); 
    }
 printf("\n");*/


}

