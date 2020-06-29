// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){
	DLList peaksL = newDLList();
	
	if (L->first == L->last) return peaksL;     // Only one item
	
	L->curr = L->first->next;                   // start at item 1
	
	while (L->curr->next != NULL) {             // check [1:-1]
	    if (L->curr->value > L->curr->prev->value && L->curr->value > L->curr->next->value) { // isPeak
	        DLListNode *newNode = newDLListNode(L->curr->value);                              // make new node with val
	        if (peaksL->first == NULL) {                                                    
	            peaksL->first = peaksL->last = newNode;                                       // if first, first=last=new
	        } else {                                                                          // else, append, make last look to new
	            peaksL->last->next = newNode;
	            newNode->prev = peaksL->last;
	            peaksL->last = newNode;
	        }
	        peaksL->curr = peaksL->last;                                                      // keeps curr at end
	        peaksL->nitems++;
	    }
	    L->curr = L->curr->next;
	}
	
	peaksL->curr = peaksL->first;
	return peaksL;
}



