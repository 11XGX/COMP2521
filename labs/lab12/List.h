// List.h ... interface to List GADT
// Written by John Shepherd, March 2013

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "Item.h"

typedef struct ListRep *List;

typedef struct ListNode {
	Item value;
	struct ListNode *next;
} ListNode;

typedef struct ListRep {
	ListNode *first;  // ptr to first node
	ListNode *last;   // ptr to last node
} ListRep;

List newList(); // create new empty list
void dropList(List); // free memory used by list
void showList(List); // display as [1,2,3...]
void ListInsert(List,Item); // add item into list
void ListDelete(List,Key); // remove item
Item *ListSearch(List,Key); // return item with key
int  ListLength(List); // # items in list

#endif
