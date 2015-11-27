#include <stdio.h>
#include<time.h>
#include<math.h>

//#include<signal.h>

#include<mt.h>

//globals

double xX[] = {0.25, 0.25, 0.25, 0.25};  //
double X[] = {8,7,6,5,4,3,2,1};  //
int Y[] = {1, 2, 3, 4, 5, 6, 7, 8};
//int tree


int main ()  {

int x_n = (int)(sizeof(X)/sizeof(double));   //JUST CHANGED   
//int y_n = (int)sizeof(Y)/sizeof(int);

int depth = (int) ((log(x_n)+0.1)/log(2)); 

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

int d, width=1;
int factor_over_2=x_n;

for (d=0; d<depth; d++) {
  factor_over_2/=2;
 
  for (i=0; i<width; i++) {
    tree[d][i]=0;
    for (j=(i*2+1)*factor_over_2; j<(i*2+2)*factor_over_2; j++) 
      tree[d][i]+=X[j];
  }
  width*=2;
}

width=1;
for (d=0; d<depth; d++) {
  printf("row %i: ", d);
  for (i=0; i<width; i++) 
    printf("%g ", tree[d][i]);
  printf("\n");
  width*=2;
}

/* In post processing, we go from bottom
 * to top, starting at depth-2, each node passes 
 * its value (passes=adding) to all its right subnodes.
 */

int first, last, below;
width=x_n;
for (d=depth-2; d>=0; d--) {
  width/=2;
  for (i=0; i<width; i++) {
    for (first=i*2+1, last=i*2+2, below=d+1; below<depth; below++) {  
      for (j=first; j<last; j++) {
        tree[below][j]+=tree[d][i];
      }
      first*=2;
      last*=2;
    }
  }
}


width=1;
for (d=0; d<depth; d++) {
  printf("row %i: ", d);
  for (i=0; i<width; i++) 
    printf("%g ", tree[d][i]);
  printf("\n");
  width*=2;
}
  
}
