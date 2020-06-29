
/* hasPath.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"



/* 
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/

int *visited;

static int hasPathCheck(Graph g, Vertex src, Vertex dest)
{
    if (adjacent(g, src, dest)) return 1;
    Vertex i;
    for (i = 0; i < g->nV; i++) {
        if (!adjacent(g, src, i)) continue;
        if (visited[i]) continue;
        visited[i] = 1;
        if (hasPathCheck(g, i, dest)) return 1;
    }
    return 0;
}

int hasPath(Graph g, Vertex src, Vertex dest)
{
    visited = calloc(g->nV, sizeof(int));
    int result = hasPathCheck(g, src, dest);
    free(visited);
	return result;
}


