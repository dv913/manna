#include <stdio.h>
#include<time.h>
#include<math.h>

//#include<signal.h>

#include<mt.h>

//globals

double X[] = {0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125};  //
int Y[] = {1, 2, 3, 4, 5, 6, 7, 8};
//int tree

/*******************************arrays_to_tree*******************************/

double arrays_to_tree()  {

int x_n = (int)(sizeof(X)/sizeof(*X)); 
int y_n = (int)sizeof(Y)/sizeof(int);

// some quick checks
// 1. sizes are equal
//if(x_n =! y_n) {printf("\nArrays must be of equal sizes\n");}

//2. probabilities in X add to 1
// ...
//3. X and Y are of size log(2)
// ...
//4. X is sorted ascending
// ...

int depth = (int) (log(x_n)/log(2)); 
double tree[depth][x_n];

int k;
for(k = 0; k < depth; k++)  {
//printf("\nnow at level %i: ", k);
}



return depth;}

/*******************************end of arrays_to_tree*****************************/


/*******************************tree_walk*******************************/

int tree_walk(double d)  {
int i;





return i;}

/*******************************end of tree_walk*************************/


//test



int main ()  {

int x_n = (int)(sizeof(X)/sizeof(double));   //JUST CHANGED   
//int y_n = (int)sizeof(Y)/sizeof(int);

int depth = (int) (log(x_n)/log(2)); 

double tree[depth][x_n];

int i, j;

//tree array initialisation to 0 and check
/*   
printf("\nArray depth:  %i\n", depth);
for ( i = 0; i < depth; i++ )
   { printf("\n");
      for ( j = 0; j < x_n/2; j++ )
      {
         r1[i][j] = 0;
         printf("r1[%d][%d] = %f  ", i,j, r1[i][j] );
      }
   } */

//tree array initialisation to tree nodes values
int kk, yi;

for ( i = 0; i < depth; i++ ) { 
      
  //printf("\ni counter: %i\n", i);
  printf("\n");
  int step_length = x_n/(pow(2, i +1)); 
  //printf("\n corresponding step_length: %i\n", step_length);
  int kkk = 0;

  for ( j = 0; j < x_n; j++ ) {
           
           if(j == step_length * kkk)  {
           //double inter_sum = 0;
           //for(kk = 0 , k<step_length; kk++) {} 
           //printf("\nkkk counter: %i\n", kkk); //UNCOMMENT
           
           //printf("\nUpdated kkk counter: %i\n", kkk); //UNCOMMENT
           
           double sum_x = 0;
           //printf("\n corresponding step_length: %i\n", step_length);
           for(yi = 0; yi < step_length*(j+1); yi++) {sum_x = sum_x + X[yi];}
           //step_length*(j+1)
           //step_length*kkk
           tree[i][j] = sum_x;
           kkk = kkk + 1;
         }
         else {tree[i][j] = 0;} 
         //tree[i][j] = 0;
         printf("T[%d][%d] = %f ", i,j, tree[i][j] );
        
      }
   } 


// walking through the tree given a (random) double number
int WalkCount;

sgenrand(time(NULL));
double TNum = genrand();
//int position = tree_walk(TNum);

int XPosition = 0, YPosition = 0;

for(YPosition = 0; YPosition < depth; YPosition++)  {
  if (TNum>tree[YPosition][XPosition]) 
    {XPosition = XPosition * 2; } 
  printf("\nThe current position is : %i, %i", YPosition, XPosition);
  }

printf("\nThe drawn number is: %f", TNum);
printf("\nThe corresponding dislocation is: %i", Y[XPosition]);
printf("\n");
}
