// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



void removeValue(DLList L, int value)
{
    L->curr = L->first;
    while (L->curr != NULL) {
        if (L->curr->value == value) {
            DLListNode *delNode = L->curr;
            if (L->first == L->last) {
                L->first = L->last = L->curr = NULL;
                free(delNode);
                L->nitems--;
                break;
            } else if (L->curr == L->first) {
                L->first = L->first->next;
                L->first->prev = NULL;
            } else if (L->curr == L->last) {
                L->last = L->last->prev;
                L->last->next = NULL;
            } else {
                L->curr->prev->next = L->curr->next;
                L->curr->next->prev = L->curr->prev;
            }
            free(delNode);
            L->nitems--;
        }
        L->curr = L->curr->next;
    }
    L->curr = L->first;

}



