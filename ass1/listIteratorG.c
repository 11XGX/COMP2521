/* listIteratorG.c ... Generic List Iterator implementation
   Written by Nathan Ellis
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {
	// Each node holds a pointer to a value of an unknown type
	void *value;
	// Pointer to the previous node in the doubly-linked list
	// Node should be 'connected' to the previous value in the list
	struct Node *prev;
	// Pointer to the next node in the doubly-linked list
	// Node should be 'connected' to the next value in the list
	struct Node *next;

} Node;

typedef struct Cursor {
    // Pointer to the node to the left of the '^' cursor in the list
	Node *prev;
	// Pointer to the node to the right of the '^' cursor in the list
	Node *next;
} Cursor;

typedef struct IteratorGRep {
	// Pointer to the node at the start of the doubly-linked list
	Node *first;
	// Pointer to the node at the end of the doubly-linked list
	Node *last;
	// Current cursor pointer of doubly-linked list
	Cursor *cursor;
	// Pointer to the last accessed value from a call to next, hasNext,
	// previous or hasPrevious. If this pointer has a non-NULL value,
	// this means set or delete CAN be called.
	Node *lastAccessed;
	// Implementation of the function pointers
	ElmCompareFp cmp;
	ElmNewFp new;
	ElmFreeFp free;

} IteratorGRep;

/* Creates a new generic list iterator with given functions to handle values. */
IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp)
{
	// Create a new list iterator and ensure its memory is correctly allocated.
	IteratorG newIterator;
	if ((newIterator = malloc(sizeof(IteratorGRep))) == NULL) {
		fprintf(stderr, "Error: Not enough memory!\n");
	}

    // Create a new cursor pointer and ensure its memory is correctly allocated.
	Cursor *newCursor;
	if ((newCursor = malloc(sizeof(Cursor))) == NULL) {
	    fprintf(stderr, "Error: Not enough memory!\n");
	}

    // Set the initial values/pointers to their default, NULL states
    // for use by the program.
	newIterator->cmp = cmpFp;
	newIterator->new = newFp;
	newIterator->free = freeFp;
	newIterator->first = newIterator->last = newIterator->lastAccessed = NULL;
	newIterator->cursor = newCursor;
	newIterator->cursor->prev = newIterator->cursor->next = NULL;

	return newIterator;
}

/* Inserts the specified value poined by vp into the list iterator it. The element
is inserted immediately before the element that would be returned by next(), if any,
and after the element that would be returned by previous(), if any. (If the list
contains no elements, the new element becomes the sole element on the list.) The new
element is inserted before the implicit cursor: a subsequent call to next would be
unaffected, and a subsequent call to previous would return the new element.
Returns 1 if successful, 0 otherwise. */
int add(IteratorG it, void *vp)
{
    assert(it != NULL);
    
	// set/delete CANNOT be called after this function.
	it->lastAccessed = NULL;

    // Create a new node and ensure its memory is correctly allocated.
    Node *newNode;
    if ((newNode = malloc(sizeof(Node))) == NULL) {
        fprintf(stderr, "Error: Not enough memory!\n");
        return 0;
    }

    // Set the value of the newly-created node using the IteratorGRep's
    // function pointer to new.
    newNode->value = it->new(vp);

	// If there are no elements in list...
	if (it->cursor->prev == NULL && it->cursor->next == NULL) {
		it->first = it->last = newNode;
	}
	// If the element is being inserted as the first element...
	else if (it->cursor->prev == NULL) {
		it->first = newNode;
		it->cursor->next->prev = newNode;
	}
	// If the element is being inserted as the last element...
	else if (it->cursor->next == NULL) {
		it->last = newNode;
		it->cursor->prev->next = newNode;
	}
	// Otherwise...
	else {
		newNode->prev = it->cursor->prev;
		it->cursor->next->prev = newNode;
		it->cursor->prev->next = newNode;
	}
	// Set the newly-created node's previous and next values to that of the cursor.
	// Also, the newly-created node is inserted to the left of the cursor.
	newNode->prev = it->cursor->prev;
	newNode->next = it->cursor->next;
	it->cursor->prev = newNode;

    return 1;
}

/* Returns 1 if the given list iterator has more elements when traversing the list
in the forward direction, returns 0 otherwise. */
int hasNext(IteratorG it)
{
    assert(it != NULL);
    
	// set/delete CANNOT be called after this function.
	it->lastAccessed = NULL;

    // If there is a node to the right of the cursor, return 1.
	if (it->cursor->next != NULL) return 1;
	// Else, return 0.
	return 0;
}

/* Returns 1 if the given list iterator has more elements when traversing the list
in the reverse direction, returns 0 otherwise. */
int hasPrevious(IteratorG it)
{
    assert(it != NULL);
    
	// set/delete CANNOT be called after this function.
	it->lastAccessed = NULL;

    // If there is a node to the left of the cursor, return 1.
	if (it->cursor->prev != NULL) return 1;
	// Else, return 0.
	return 0;
}

/* Returns the pointer to the next value in the given list iterator and advances
the cursor position. This method may be called repeatedly to iterate through the
list, or intermixed with calls to previous to go back and forth. (Note that
alternating calls to next and previous will return the same element repeatedly.)
The method returns NULL if it has no next value. */
void *next(IteratorG it)
{
	assert(it != NULL);
	
	// If there is no next value...
	if (it->cursor->next == NULL) return NULL;

	// Move the cursor pointer one element forwards.
	it->cursor->prev = it->cursor->next;
	it->cursor->next = it->cursor->next->next;

	// set/delete CAN be called after this function.
	it->lastAccessed = it->cursor->prev;

	// Return the value the cursor pointer has moved past.
	return it->cursor->prev->value;
}

/* Returns the pointer to the previous value in the given list iterator and moves
the cursor position backwards. This method may be called repeatedly to iterate
through the list backwards, or intermixed with calls to next to go back and forth.
(Note that alternating calls to next and previous will return the same element
repeatedly.) The method returns NULL if it has no previous value. */
void *previous(IteratorG it)
{
	assert(it != NULL);
	
	// If there is no prevous value...
	if (it->cursor->prev == NULL) return NULL;

	// Move the cursor pointer one element backwards.
	it->cursor->next = it->cursor->prev;
	it->cursor->prev = it->cursor->prev->prev;

	// set/delete CAN be called after this function.
	it->lastAccessed = it->cursor->next;

	// Return the value the cursor pointer has moved past.
	return it->cursor->next->value;
}

/* Deletes from the list iterator the last value that was returned by next or previous
or findNext or findPrevious. (Precondition: A call to delete must be IMMEDIATELY preceded
by a successful call to one of next or previous or findNextor findPrevious.)
Returns 1 if successful, 0 otherwise (for example, invalid delete call). */
int delete(IteratorG it)
{
	assert(it != NULL);
	
	// If delete was NOT called directly after next, findNext
	// previous or findPrevious, delete cannot be called.
	if (it->lastAccessed == NULL) return 0;
	
	// If the list is empty, no nodes can be deleted.
	if (it->first == NULL) return 0;
    
    // If the 'last accessed' node is the first node in the list...
	if (it->lastAccessed->prev == NULL) {
		it->first = it->lastAccessed->next;
	}
	// Else, adjust the previous node's next to be the node after
	// the one being deleted.
	else {
	    it->lastAccessed->prev->next = it->lastAccessed->next;
	}
	
	// If the 'last accessed' node is the last node in the list...
	if (it->lastAccessed->next == NULL) {
		it->last = it->lastAccessed->prev;
	} 
	// Else, adjust the next node's previous to be the node before
	// the one being deleted.
	else {
		it->lastAccessed->next->prev = it->lastAccessed->prev;
	}

    // If the 'last accessed' node is on the cursor's right...
	if (it->cursor->next == it->lastAccessed) {
		it->cursor->next = it->lastAccessed->next;
	}
	// Else, the 'last accessed' node is on the cursor's left.
	else {
		it->cursor->prev = it->lastAccessed->prev;
	}

    // Free the value of the node to be deleted using the IteratorGRep's
    // function pointer to free. Then, free the node itself.
	it->free(it->lastAccessed->value);
	free(it->lastAccessed);

	// set/delete CANNOT be called after this function.
	it->lastAccessed = NULL;

	return 1;
}

/* Replaces the last element returned by next or previous or findNext or findPrevious
with the specified element (*vp). (Precondition: A call to set must be IMMEDIATELY
preceded by a successful call to one of next or previous or findNext or findPrevious.) 
Returns 1 if successful, 0 otherwise (for example, invalid set call). */
int set(IteratorG it, void *vp)
{
	assert(it != NULL);
	
	// If set was NOT called directly after next, findNext
	// previous or findPrevious, set cannot be called.
	if (it->lastAccessed == NULL) return 0;

    // Free the value of the node to be deleted using the IteratorGRep's
    // function pointer to free. Then, set the value of the newly-created
    // node using the IteratorGRep's function pointer to new.
	it->free(it->lastAccessed->value);
	it->lastAccessed->value = it->new(vp);

	// set/delete CANNOT be called after this function.
	it->lastAccessed = NULL;

	return 1;
}

/* Returns pointer to the next value in it that matches the value pointed to by vp
and advances the cursor position past the value returned. The method returns NULL
if there is no such next value and the cursor is not moved from the current position. */
void *findNext(IteratorG it, void *vp)
{
	assert(it != NULL);
	
	// Create a pointer to the node to the right of the cursor.
    Node *list = it->cursor->next;
    // Iterate forwards through the list...
    while (list != NULL) {
        // Use the IteratorGRep's function pointer to cmp to compare the given value to
        // the currently-searched node's value. If they are the same...
        if (it->cmp(list->value, vp) == 0) {
            // Move the cursor to the found node's right.  Then, set the 'last accessed'
            // value to the found node.
            // set/delete CAN be called after this function.
            it->cursor->prev = list;
            it->cursor->next = list->next;
			it->lastAccessed = list;
            return list->value;
        }
        list = list->next;
    }
    
    // set/delete CANNOT be called after a failed call to this function.
    it->lastAccessed = NULL;
    return NULL;
}

/* Returns pointer to the previous value in it that matches the value pointed to by vp
and moves the cursor position backwards before the value returned. The method returns NULL
if there is no such previous value and the cursor is not moved from the current position. */
void *findPrevious(IteratorG it, void *vp)
{
	assert(it != NULL);
	
	// Create a pointer to the node to the left of the cursor.
    Node *list = it->cursor->prev;
    // Iterate backwards through the list...
    while (list != NULL) {
        // Use the IteratorGRep's function pointer to cmp to compare the given value to
        // the currently-searched node's value. If they are the same...
        if (it->cmp(list->value, vp) == 0) {
            // Move the cursor to the found node's left.  Then, set the 'last accessed'
            // value to the found node.
            // set/delete CAN be called after this function.
            it->cursor->prev = list;
            it->cursor->next = list->next;
			it->lastAccessed = list;
            return list->value;
        }
        list = list->prev;
    }
    
    // set/delete CANNOT be called after a failed call to this function.
    it->lastAccessed = NULL;
    return NULL;
}

/* Resets it to the start of the list. */
void reset(IteratorG it)
{
    assert(it != NULL);
    
	// set/delete CANNOT be called after this function.
	it->lastAccessed = NULL;

    // Move the cursor to the left of the first element in the list.
	it->cursor->prev = NULL;
	it->cursor->next = it->first;
}

/* Deletes all the nodes in it and frees associated memory. */
void freeIt(IteratorG it)
{
	assert(it != NULL);
	
	// Move the cursor to the right of the last element in the list.
	it->cursor->next = NULL;
	it->cursor->prev = it->last;

    // Iterate backwards through the list...
	while (it->cursor->prev != NULL) {
	    // Create a pointer to the node to the left of the cursor.
		Node *delNode = it->cursor->prev;
		// Move the cursor one element to the left and the list's last
		// element to the second-last element.
		it->last = it->cursor->prev->prev;
		it->cursor->prev = it->last;
		// Free the value of the node to be deleted using the IteratorGRep's
        // function pointer to free. Then, free the node itself.
		it->free(delNode->value);
		free(delNode);
	}

    // When all the nodes have been correctly freed, free the actual list (IteratorG).
	free(it);
}
