#include <stdio.h>
#include<time.h>
#include<math.h>

#include<mt.h>

#define L 5 // length of the lattice minus 1
#define C 2 // top up cell number in array count
#define N_ROLLS 10  // number of experiments -- balls to drop

int main()  {
 
  int lattice[L] = {[0 ... L-1] = 0};
  int i, drop;
  int k;
  for(k = 0; k<L; k++) {printf("%i", lattice[k]); }
  printf(" --- End of initialisation\n");   

  sgenrand(time(NULL));

  for (drop = 0; drop < N_ROLLS; drop++) {  // big droppping cycle

  lattice[C] = lattice[C] + 1;  //actual drop in the drop location

  printf("\n");
  for(k = 0; k<L; k++) {printf("%i", lattice[k]); } // check after initial drop
  printf( " --- After %i drops************************************", drop+1);  

  for (i = 0; i < L; i++) {

    if (lattice[i] > 1) //check slots > 1
     {  
      // draw 2 rand nums
      int dist1 = genrand()*2; 
      int dist2 = genrand()*2;
      
       // convert to distr

       // define direction
      double  dir1 = genrand();
      double  dir2 = genrand();
      if(dir1 < 0.5) {dir1 = (int)-1;} else {dir1 = (int)1;}
      if(dir2 < 0.5) {dir2 = (int)-1;} else {dir2 = (int)1;}

      printf("\nBall 1 from cell %i moves: %i (%i,%i)", i, (int)dist1*(int)dir1, (int)dist1, (int)dir1);
      printf("\nBall 2 from cell %i moves: %i  (%i,%i)\n", i, (int)dist2*(int)dir2, (int)dist2,(int)dir2);

      // shoot 2 balls
      if(i+dist1*dir1 < L && i+dist1*dir1 >= 0) {lattice[i+(int)dist1*(int)dir1] = lattice[i+(int)dist1*(int)dir1] + 1;}
      if(i+dist2*dir2 < L && i+dist2*dir1 >= 0) {lattice[i+(int)dist2*(int)dir2] = lattice[i+(int)dist2*(int)dir2] + 1;}
      // decrease initial slot by 2
      lattice[i] = lattice[i] - 2;
      
      printf("Final standing after shooting:  ");
      for(k = 0; k<L; k++) {printf("%i", lattice[k]); } 

      // restart array check from beginning
      i = -1 ;  // account for autoincrement
      }  

    else {printf("\nNothing to shoot from cell %i", i); }  

    }
  } 
}

