#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"
#include "Queue.h"


/* 
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/

int shortestPath(Graph g, Vertex src, Vertex dest)
{
    visited = calloc(g->nV, sizeof(int));
    int result = hasPathCheck(g, src, dest);
    free(visited);
	return result;
}


