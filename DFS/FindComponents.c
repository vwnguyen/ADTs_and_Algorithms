//-----------------------------------------------------------------------------
// FindComponents.c
// Viet Nguyen
// Description: Main file that utilizes Graph.h to find the strongly connected 
// components of a graph given an input file in a specific format
//-----------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
    FILE* in;
    FILE* out;

    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r");
    if(in == NULL){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if(out == NULL){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    
	char str[MAX_LEN];
	int n = 0;
	int i;
	if( fgets (str, MAX_LEN, in)!=NULL ) {
      /* writing content to stdout */
	  sscanf( str, "%d", &n);
	  //puts(str);
    }
	Graph G = newGraph(n);
	// keep reading until the end of the file
	int vertexU, vertexV;
	while( fgets(str, MAX_LEN, in) != NULL)  {
		sscanf( str, "%d %d", &vertexU, &vertexV);
		if ( vertexU == 0 && vertexV == 0){
			break;
		}else{
			addArc(G,vertexU,vertexV);
		}
    }
	
	fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
	fprintf(out,"\n");
	// create S to store decreasing finish times
	List S = newList();
	for ( int i = 1 ; i<=getOrder(G); i++ ){
		append(S,i);
	}
	
    DFS(G, S);
	
	moveFront(S);
	//deleteBack(S);
	
	for ( i = 1; i <= length(S); i++ ){

		moveNext(S);
	}  

	Graph T = transpose(G);
    DFS(T, S);
	for ( i = 1; i <= length(S); i++ ){
		moveNext(S);
	}

	moveFront(S);
	
	int nillCounter = 0;
	
	for ( i = 1; i <= length(S); i++ ){
		if ( getParent(T,get(S)) == NIL ){
			nillCounter++;
		}
		moveNext(S);
	} 
 
	fprintf(out,"G contains %d strongly connected components:\n",nillCounter);

	// S holds the second ordered List of vertices
	// parentList holds parents of S
	
	int count = 0;
	int component = 1;
	int initFlag = 0;
	moveBack(S);
	while ( component <= nillCounter ){
		
		fprintf(out,"Component %d: ",component);
		// get the parent of back of list S.
		while ( getParent(T,get(S)) != NIL ) {
			count++;
			movePrev(S);
		}
		printf("after while, count: %d\n",count);
		for ( i = 0; i<=count; i++ ){
			fprintf(out,"%d ",get(S));
			moveNext(S);
		}
		
		if (initFlag == 1){
			movePrev(S);
		}
		if ( index(S) == -1 ){
			moveBack(S);
			initFlag = 1;
		}
		
		
		for ( i = 0; i<=count; i++ ){
			movePrev(S);
		}
		fprintf(out,"\n");
		
		
		
		count = 0;
		component++;
	}


    // free items used
    freeGraph(&G);
	freeList(&S);

    return EXIT_SUCCESS;
}
