#include <stdio.h>
#include<stdlib.h>

/*
void foo(char *line){
int num, i=0, len;
while (scanf(line, "%d,", &num, &len) == 1){
  printf("Number %d is %d\n", i, num);
  line+=len;
  i++;
  }
}*/

int main () {

char buffer[1024];
FILE *fp = fopen("test.dat", "r");
int num, i;
char comment[20];
char arr_data[800];
for(i=0; i<799; i++){arr_data[i] = 'x';}


//read file into num of test, comments and number char array
while (fgets(buffer, sizeof(buffer), fp) != NULL) {
  sscanf(buffer, "%i;%s %s", &num, comment, arr_data);  
  printf( "\n%i:  %s\n", num, arr_data  );

  int k = 0;
//count the number of numbers in the char array
  int num_count = 1; //one comma less then numbers
  while(arr_data[k] != 0 ) {
    if(arr_data[k] == ',') {num_count++;}
    k++;
    }

  printf("\nNums in the array: %i\n", num_count);
//initialise double array
  double data[num_count];

  int acc_len = 0;
  for(i=0; i<num_count; i++){
    int num_len = 0;
    while(arr_data[acc_len+num_len] != ',' && arr_data[acc_len+num_len] != 0){num_len++;}
    printf("\n%i's num lenght is %i ,", i, num_len);
    acc_len = acc_len + num_len +1;
    printf("  start of next number is %i", acc_len);
    int decim = 0;
    
    }
    
  /*
  for(i=0; i<15; i++){
    if(arr_data[i] != 'x' ) {printf("%c ", arr_data[i]);}
    } */
  for(i=0; i<799; i++){arr_data[i] = 'x';}  //clean up the arr_data
  printf("\n");
 }


  printf("\n");
  
fclose(fp);
}


