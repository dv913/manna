#include <stdio.h>
#include<stdlib.h>
#include<math.h>
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
int fin_num;

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

  printf("Nums in the array: %i", num_count);
//initialise double array
  int data[num_count]; // = {[0 ... num_coun] = 0};

  //converting char array to int array
  int acc_len = 0;
  for(i=0; i<num_count; i++){
    fin_num = 0;
    int num_len = 0;
    while(arr_data[acc_len+num_len] != ',' && arr_data[acc_len+num_len] != 0){num_len++;}
    //printf("\n%i's num lenght is %i ,", i, num_len);
    acc_len = acc_len + num_len +1;
    //printf("  start of next number is %i", acc_len);
    int decim;
    for(decim = acc_len - num_len -1; decim < acc_len -1; decim++){
        int d = arr_data[decim] - '0';
        int pow_c;
        int out = 1;
           for(pow_c = 0; pow_c <acc_len-decim-2; pow_c++) {out = out*10;}
        //printf("\nNumber %i for %i", out*d, d);  //(acc_len-decim-2)
        fin_num = fin_num + out*d;
        //printf("\nResulting number:  \n%i on inter %i", fin_num, decim);
        if(decim == acc_len -2) {
          data[i] = fin_num; 
          //printf("NUM FROM ARRAY: %i", data[i]);
          }
       }
      //printf("\n");
      }
  printf("\nPrinting array as int array: ");
  for(i=0; i<num_count; i++){
    printf("%i,", data[i]);
    }

  for(i=0; i<799; i++){arr_data[i] = 'x';}  //clean up the arr_data
  printf("\n");
 }


  printf("\n");
  
  fclose(fp);
  }


