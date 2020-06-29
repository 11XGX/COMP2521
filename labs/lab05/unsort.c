// unsort.c ... make a sequence of numbers not sorted
// Usage: unsort [FileName]
// If no file name supplied, unsorts stdin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

int main (int argc, char *argv[])
{
   FILE *in;

   if (argc == 1) 
      in = stdin;
   else {
      if ((in = fopen(argv[1],"r")) == NULL) {
         fprintf(stderr, "Can't open file '%s'\n",argv[1]);
         exit(1);
      }
   }
  
   // Put code here read numbers and "unsort" them
   // Hint: for reading the input
   srand(time(NULL));
   
   int counter1 = 0, counter2 = 0, randomIndex = 0, temp = 0;
   int array[100000] = {0};
   
   while (fscanf(in, "%d", &array[counter1]) != EOF) {
      randomIndex = rand()%(counter1+1);                                      // Range: [0,n]
      temp = array[counter1];
      array[counter1] = array[randomIndex];
      array[randomIndex] = temp;
      counter1++;
   }
   array[counter1] = -1;

   while (array[counter2] != -1) {
      printf("%d\n", array[counter2]);
      counter2++;
   }

   return 0;
}      
