/*
  testListIteratorG.c ... client to test Generic List Iterator 
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 5

void printdecimallist(IteratorG list) {
  // list all the elements (forward)
  printf("List elements:\n");
  reset(list);
  int *d = next(list);
  while(d != NULL){
    printf("\t\t%d\n",*d);
    d = next(list);
  }
  
  //list backward (assumes cursor is at end of list already)
  printf("List backwards:\n");
  d = previous(list);
  while(d != NULL){
    printf("\t\t%d\n",*d);
    d = previous(list);
  }
  reset(list);
}



int main(int argc, char *argv[])
{
  
  /* The following code, inside the comments, may or may not be correct!
     
     It's provided in case you find it difficult to understand 
     how to create a generic list iterator, and use it's functions.
     
     Please study SetG example we discussed in the lecture in detail.

     The code below only tests basic operations, however 
     make sure that you do test all the required functions properly in
     your test file. 

  */
  
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  

  //IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  
  //int a[MAXARRAY] = { 25, 12, 6, 82 , 11};
  int dig[10] = {0,1,2,3,4,5,6,7,8,9};
  /*  
  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
*/	
	/*
	The above loop should print ... 
		Inserting 25: Success 
		Inserting 12: Success 
		Inserting 6: Success 
		Inserting 82: Success 
		Inserting 11: Success
	*/  
/*
  int one = 1;

  int *d = (int *) previous(it1);
  printf("Previous value is: %d \n", *d );  // should print "Previous value is: 11" 
  
  d = (int *) previous(it1);
  printf("Previous value is: %d \n", *d );  // should print "Previous value is: 82" 
  
  d = (int *) next(it1);
  printf("Next value is: %d \n", *d );     // should print "Next value is: 82" 
  
  *d = set(it1, &one);
  printf("Set with status: %d \n", *d );     // should print "Set with status: 1" 
  
  d = (int *) previous(it1);
  printf("Previous value is: %d \n", *d );  // should print "Previous value is: 1" 
  
  d = (int *) previous(it1);
  printf("Previous value is: %d \n", *d );  // should print "Previous value is: 6"
  
  
  printdecimallist(it1);
  */
  //d currently points to freed memory
  int ii = 0;
  int *d = &ii;
  
  //freeIt(it1);
  
  // TEST1 operate on new empty list
  
  IteratorG it3 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  *d = hasNext(it3);
  printf("hasNext: %d \n", *d );
  *d = hasPrevious(it3);
  printf("hasPrevious: %d \n", *d );
  d = next(it3);
  if(d == NULL) {  printf("No Next \n" );}
  d = previous(it3);
  if(d == NULL) {  printf("No Prev \n" );}
  d = findNext(it3, &dig[0]);
  if(d == NULL) {  printf("No Next 25\n" );}
  d = findPrevious(it3, &dig[0]);
  if(d == NULL) {  printf("No Prev 25 \n" );}
  
  //d currently points to NULL
  ii = 0;
  d = &ii;
  
  *d = delete(it3);
  printf("delete: %d \n", *d );
  *d = set(it3, &dig[0]);
  printf("set: %d \n", *d );
  reset(it3);
  
  printdecimallist(it3);
  
  // TEST2 add 1-9 to list
  
  add(it3,&dig[3]);
  add(it3,&dig[4]);
  add(it3,&dig[5]);
  previous(it3);
  findNext(it3,&dig[5]);
  add(it3,&dig[6]);
  findPrevious(it3, &dig[3]);
  add(it3,&dig[2]);
  findNext(it3,&dig[6]);
  add(it3,&dig[8]);
  findPrevious(it3,&dig[6]);
  next(it3);
  add(it3,&dig[7]);
  reset(it3);
  add(it3,&dig[1]);
  next(it3);
  next(it3);
  next(it3);
  next(it3);
  next(it3);
  next(it3);
  next(it3);
  add(it3, &dig[9]);
  
  printdecimallist(it3);
  
  // TEST3 replace odd numbers with "0"
  
  findNext(it3, &dig[1]);
  set(it3, &dig[0]);
  printf("This next bit should fail: ");
  findNext(it3, &dig[1]);
  next(it3);
  next(it3);
  next(it3);
  next(it3);
  set(it3, &dig[0]);
  previous(it3);
  previous(it3);
  previous(it3);
  set(it3, &dig[0]);
  findNext(it3, &dig[9]);
  set(it3, &dig[0]);
  findPrevious(it3, &dig[7]);
  set(it3, &dig[0]);

  printdecimallist(it3);

  //TEST4 restore odd numbers
  
  findNext(it3, &dig[0]);
  findNext(it3, &dig[0]);
  findNext(it3, &dig[0]);
  delete(it3);
  add(it3, &dig[5]);
  next(it3);
  next(it3);
  findPrevious(it3, &dig[0]);
  findPrevious(it3, &dig[0]);
  set(it3, &dig[3]);
  previous(it3);
  previous(it3);
  set(it3,&dig[1]);
  findNext(it3, &dig[0]);
  set(it3,&dig[7]);
  findNext(it3, &dig[0]);
  set(it3,&dig[9]);
  
  printdecimallist(it3);
  
  //TEST5 delete even numbers  

  next(it3);
  next(it3);
  delete(it3);
  next(it3);
  next(it3);
  next(it3);
  next(it3);
  delete(it3);
  previous(it3);
  previous(it3);
  delete(it3);
  findNext(it3, &dig[7]);
  next(it3);
  delete(it3);
  
  
  
  printdecimallist(it3);
  
  //TEST6 delete all but one and operate

  findNext(it3, &dig[5]);
  next(it3);
  delete(it3); //should delete 7
  delete(it3); //should fail
  previous(it3);
  delete(it3); //should delete 5
  next(it3);
  delete(it3); //should delete 9
  findPrevious(it3, &dig[3]);
  delete(it3);

  printdecimallist(it3);
  
  //TEST7 delete last and operate
  
  next(it3);
  delete(it3);
  add(it3, &dig[9]);
  
  printdecimallist(it3);

  next(it3);
  delete(it3);
  findNext(it3, &dig[0]);
  findPrevious(it3, &dig[0]);
  delete(it3);
  next(it3);
  set(it3, &dig[5]);
  freeIt(it3);
  
  //TEST8 add one and test single element lists
  
  /* =======================================
     --------- stringType List Iterator ----------
  */
 
 
  IteratorG it2 = IteratorGNew(stringCompare, stringNew, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby"); 
  
  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]); 
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }

	/*
	The above loop should print ... 
		Inserting john: Success 
		Inserting rita: Success 
		Inserting john: Success 
		Inserting abby: Success
	*/

  char *s = (char *) previous(it2);
  printf("Previous value is: %s \n", s );  // should print: "Previous value is: abby"
  
  s = (char *) previous(it2);
  printf("Previous value is: %s \n", s );  // should print: "Previous value is: john"
  
  s = (char *) next(it2);
  printf("Next value is: %s \n", s );      // should print: "Next value is: john"
  
  // list all the elements (forward)
  printf("List elements:\n");
  reset(it2);
  s = next(it2);
  while(s != NULL){
    printf("\t\t%s\n",s);
    s = next(it2);
  }
  
  //list backward (assumes cursor is at end of list already)
  printf("List backwards:\n");
  s = previous(it2);
  while(s != NULL){
    printf("\t\t%s\n",s);
    s = previous(it2);
  }
  
  freeIt(it2);

  free(strA[0]);
    free(strA[1]);
      free(strA[2]);
        free(strA[3]);  
  
  return EXIT_SUCCESS;
  
}
