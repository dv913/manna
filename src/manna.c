#include <iostream>
#include<random>
#include<math.h>

#include<MT19937.h>


#define L 100 // length of the lattice
#define N_ROLLS 100000  // number of experiments -- balls to drop




int main()
{
  using namespace std;
  srand((unsigned)time(NULL));
  int lattice[L-1] = {0};
 // timer

int run_count = 1;
while (run_count == 0 ) {
  for (i = 0; i = L; i++) {



    if lattice[i] > 1 {//check slots > 1
  // draw 2 rand nums
  // convert to distr
  // define direction
  // shoot 2 balls
      lattice[i] = lattice[i] - 2;// decrease initial slot by 2
      run_count = 1; // needs additional run


    else {run_count = 0};// ELSE


    }
  }
}
  // if CENTRE >1
  // shoot 2 balls from centre
//print timer value
} 
