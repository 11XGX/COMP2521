// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "DLList.h"

#define NO_MOVE 0
#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE 3
#define MOVE 4
#define clear() printf("\033[H\033[J")

void printState(DLList);
void printOperation(int, int);
void printExpectedOutput(int);
void move(DLList, int);

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);
	assert(validDLList(myList));
	printState(myList);

	// Multiple nodes (curr == first) - insert before
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_BEFORE, NO_MOVE);
	DLListBefore(myList, "I think");
	assert(validDLList(myList));
	printExpectedOutput(1);
	printState(myList);

	// Move 4
	move(myList, 4);

	// Multiple nodes (curr == middle) - insert before
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_BEFORE, NO_MOVE);
	DLListBefore(myList, "cat and");
	assert(validDLList(myList));
	printExpectedOutput(2);
	printState(myList);
	
	// Move 6
	move(myList, 6);
	
	// Multiple nodes (curr == last) - insert before
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_BEFORE, NO_MOVE);
	DLListBefore(myList, "fluffy");
	assert(validDLList(myList));
	printExpectedOutput(3);
	printState(myList);
	
	// Move 1
	move(myList, 1);
	
	// Multiple nodes (curr == last) - delete node
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(DELETE, NO_MOVE);
	DLListDelete(myList);
	assert(validDLList(myList));
	printExpectedOutput(4);
	printState(myList);
	
	// Move -6
	move(myList, -6);
	
	// Multiple nodes (curr == middle) - delete node
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(DELETE, NO_MOVE);
	DLListDelete(myList);
	assert(validDLList(myList));
	printExpectedOutput(5);
	printState(myList);
	
	// Move -4
	move(myList, -4);
	
	// Multiple nodes (curr == first) - delete node
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(DELETE, NO_MOVE);
	DLListDelete(myList);
	assert(validDLList(myList));
	printExpectedOutput(6);
	printState(myList);
	
	// Multiple nodes (curr == first) - insert after
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_AFTER, NO_MOVE);
	DLListAfter(myList, "really");
	assert(validDLList(myList));
	printExpectedOutput(7);
	printState(myList);
	
	// Move 2
	move(myList, 2);
	
	// Multiple nodes (curr == middle) - insert after
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_AFTER, NO_MOVE);
	DLListAfter(myList, "cat and");
	assert(validDLList(myList));
	printExpectedOutput(8);
	printState(myList);
	
	// Move 6
	move(myList, 6);
	
	// Multiple nodes (curr == last) - insert after
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_AFTER, NO_MOVE);
	DLListAfter(myList, "dog");
	assert(validDLList(myList));
	printExpectedOutput(9);
	printState(myList);
	
	// Repeatedly delete the list until empty
	int counter = 0;
	while (counter < 12) {
		sleep(5);
		printf("\n\n\n\n\n");
		printOperation(DELETE, NO_MOVE);
		DLListDelete(myList);
		assert(validDLList(myList));
		printExpectedOutput(10 + counter);
		if (counter != 11) printState(myList);
		else printf("============== PRINTED STATE =============\n\n========== END OF PRINTED STATE ==========\n");
		counter++;
	}
	
	// Empty list - insert before
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_BEFORE, NO_MOVE);
	DLListBefore(myList, "the");
	assert(validDLList(myList));
	printExpectedOutput(20);
	printState(myList);
	
	// Delete node
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(DELETE, NO_MOVE);
	DLListDelete(myList);
	printExpectedOutput(21);
	printf("============== PRINTED STATE =============\n\n========== END OF PRINTED STATE ==========\n");
	
	// Empty list - insert after
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(INSERT_AFTER, NO_MOVE);
	DLListAfter(myList, "the");
	assert(validDLList(myList));
	printExpectedOutput(20);
	printState(myList);
	
	// Delete node
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(DELETE, NO_MOVE);
	DLListDelete(myList);
	printExpectedOutput(21);
	printf("============== PRINTED STATE =============\n\n========== END OF PRINTED STATE ==========\n");
	
	// Delete node
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(DELETE, NO_MOVE);
	DLListDelete(myList);
	printExpectedOutput(22);
	printf("============== PRINTED STATE =============\n\n========== END OF PRINTED STATE ==========\n");

	return 0;
}

void printState(DLList myList) {
	printf("============== PRINTED LIST ==============\n");
	putDLList(stdout, myList);
	printf("========== END OF PRINTED LIST ===========\n");
	printf("============== PRINTED STATE =============\n");
	printf("L->curr = %s\n", DLListCurrent(myList));
	printf("nitems = %d\n", DLListLength(myList));
	printf("========== END OF PRINTED STATE ==========\n");
}

void printOperation(int i, int move) {
	printf("Operation Performed: ");
	switch (i) {
		case 1:
			printf("Insert Before...\n");
			break;
		case 2:
			printf("Insert After...\n");
			break;
		case 3:
			printf("Delete Node...\n");
			break;
		case 4:
			printf("Moved curr %d times in List...\n", move);
			break;
	}
}

void printExpectedOutput(int i) {
	printf("============ EXPECTED OUTPUT =============\n");
	switch (i) {
		case 1:
			printf("I think\nthe\nquick\nbrown\nfox\njumped\nover\nthe\nlazy\ndog\n");
			break;
		case 2:
			printf("I think\nthe\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\ndog\n");
			break;
		case 3:
			printf("I think\nthe\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\nfluffy\ndog\n");
			break;
		case 4:
			printf("I think\nthe\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\nfluffy\n");
			break;
		case 5:
			printf("I think\nthe\nquick\nbrown\nfox\njumped\nover\nthe\nlazy\nfluffy\n");
			break;
		case 6:
			printf("the\nquick\nbrown\nfox\njumped\nover\nthe\nlazy\nfluffy\n");
			break;
		case 7:
			printf("the\nreally\nquick\nbrown\nfox\njumped\nover\nthe\nlazy\nfluffy\n");
			break;
		case 8:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\nfluffy\n");
			break;
		case 9:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\nfluffy\ndog\n");
			break;
		case 10:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\nfluffy\n");
			break;
		case 11:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\nlazy\n");
			break;
		case 12:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\nover\nthe\n");
			break;
		case 13:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\nover\n");
			break;
		case 14:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\njumped\n");
			break;
		case 15:
			printf("the\nreally\nquick\nbrown\ncat and\nfox\n");
			break;
		case 16:
			printf("the\nreally\nquick\nbrown\ncat and\n");
			break;
		case 17:
			printf("the\nreally\nquick\nbrown\n");
			break;
		case 18:
			printf("the\nreally\nquick\n");
			break;
		case 19:
			printf("the\nreally\n");
			break;
		case 20:
			printf("the\n");
			break;
		case 21:
			printf("\n");
			break;
	}
	printf("========= END OF EXPECTED OUTPUT =========\n");
}

void move(DLList myList, int i) {
	sleep(5);
	printf("\n\n\n\n\n");
	printOperation(MOVE, i);
	DLListMove(myList, i);
	assert(validDLList(myList));
}
