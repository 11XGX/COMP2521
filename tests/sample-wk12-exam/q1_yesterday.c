#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "countEven" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/

static int leaves;

int countLeaves(BSTree t){

	if (t == NULL) return 0;
	
	if (t->right == NULL && t->left == NULL) {
		count = 1;
	} else {
	    count = 0;
	}

	return count + countLeaves(t->left) + countLeaves(t->right);

}



