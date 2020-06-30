//-----------------------------------------------------------------------------
// Graph.c
// Viet Nguyen
// ID: vwnguyen
// #: 1467315
// Assignment: pa4
// Description: Test file for Graph ADT implementation
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define ASTERISKS "******************************\n"
#define TEST_SIZE 6
#define SOURCE_TEST 3
int main(void){

	printf("Graph Tests\n");
	
    Graph G = newGraph(TEST_SIZE);
	List L = newList();
	List S = newList();
	for (int i = 1; i <= TEST_SIZE; i++){
		append(S,i);
	}
	printf("List S: ");
	printList(stdout,S);
	printf("\n");
	
	printf(ASTERISKS);
	printf("ADDING EDGES NORMALLY\n");
	printf(ASTERISKS);
	
	// adding edges normally 
	addEdge(G, 1, 2); // creates (1,4)
    addEdge(G, 1, 3); // creates (1,2)
    addEdge(G, 2, 4); // creates (1,5)
	addEdge(G, 2, 5); // creates (2,3)
    addEdge(G, 2, 6); // creates (2,4)

	addEdge(G, 5, 6); // creates (3,8)
	addEdge(G, 2, 5); // creates (2,5)
	addEdge(G, 3, 4); // creates (2,5)
	addEdge(G, 4, 5); // creates (2,5)
	// add arc normally 
	//addArc(G, 2, 6); // creates (1,4)
	//addArc(G, 6, 2); // creates (1,4)
	//addArc(G, 3, 7); // creates (1,4)
	//addArc(G, 1, 4); // creates (1,4)

	
	// should only be 8 vertices
	printf("Graph G: \n");
    printGraph(stdout, G);
	printf("G Order: %i\n", getOrder(G));
    printf("G Size: %i\n", getSize(G));
	printf(ASTERISKS);
	printf("ADDING EDGES OUT OF RANGE\n");
	printf(ASTERISKS);
	// adding edges out of range test
    //addEdge(G, 1, 16);
    //addEdge(G, 1, 17);
    //addEdge(G, 1, 18);
	//printf("Graph G: \n");
    //printGraph(stdout, G);
	//printf("G Order = %i\n", getOrder(G));
    //printf("G Size = %i\n", getSize(G));
	// attempting to add redundant edges
	printf(ASTERISKS);
	printf("ADDING REDUNDANT EDGES\n");
	printf(ASTERISKS);
	addEdge(G, 5, 6); // creates (3,8)
	addEdge(G, 2, 5); // creates (2,5)
	addEdge(G, 3, 4); // creates (2,5)
	addEdge(G, 4, 5); // creates (2,5)
	printf("Graph G: \n");
    printGraph(stdout, G);
	printf("G Order = %i\n", getOrder(G));
    printf("G Size = %i\n", getSize(G));
	printf(ASTERISKS);
	printf("COPY GRAPH TESTS\n");
	printf(ASTERISKS);
	Graph copyTest = copyGraph(G);
	printf("Graph copyTest: \n");
    printGraph(stdout, copyTest);
	printf(ASTERISKS);
	printf("TRANSPOSE GRAPH TESTS\n");
	printf(ASTERISKS);
	Graph transposeTest = transpose(G);
	printGraph(stdout, transposeTest);
	printf(ASTERISKS);
	
	
	
	
	printf(ASTERISKS);
	printf("BFS TEST\n");
	printf(ASTERISKS);
	
	// we must run BFS at least once before getPath
    BFS(G,SOURCE_TEST);
    printf("using source: %d\n", getSource(G));
    printf("Parent of 1: %d\n", getParent(G, 1));
	printf("Parent of 2: %d\n", getParent(G, 2));
	printf("Parent of 3: %d\n", getParent(G, 3));
    printf("Dist between %d and 2 is: %i\n", SOURCE_TEST, getDist(G, 2));
	printf("Dist between %d and 3 is: %i\n", SOURCE_TEST, getDist(G, 3));
	printf("Dist between %d and 4 is: %i\n", SOURCE_TEST, getDist(G, 4));
    getPath(L, G, 1);
    printf("PATH from source to 1: ");
    printList(stdout, L);
    printf("\n");
	clear(L);
	getPath(L, G, 5);
    printf("PATH from source to 5: ");
    printList(stdout, L);
    printf("\n");
	clear(L);
	getPath(L, G, 2);
    printf("PATH from source to 2: ");
    printList(stdout, L);
    printf("\n");
    printf(ASTERISKS);
	printf("DFS TEST\n");
	printf(ASTERISKS);
	printf("Input List S: ");
	printList(stdout,S);
	printf("\n");
	DFS(G,S);
	printf("Output List S: ");
	printList(stdout,S);
	printf("\n");
	
	
	printf(ASTERISKS);
	printf("MAKENULL TESTS\n");
	printf(ASTERISKS);
	makeNull(G);
    printf("Null graph:\n");
    printGraph(stdout, G);
	
	
	
	
    freeList(&L);
    freeGraph(&G);
	
    return EXIT_SUCCESS;
}