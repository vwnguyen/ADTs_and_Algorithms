//-----------------------------------------------------------------------------
// Graph.c
// Viet Nguyen
// ID: vwnguyen
// #: 1467315
// Assignment: pa4
// Description: Main file that takes in two input files 
// in format specified in PDF, then outputs the distance
// between those using BFS search algorithm
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
    FILE* in;
    FILE* out;
	
	// standard argument checks
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

    // determining the order of the graph

	char str[MAX_LEN];
	int n = 0;
	
	if( fgets (str, MAX_LEN, in)!=NULL ) {
      /* writing content to stdout */
	  sscanf( str, "%d", &n);
	  //puts(str);
    }
	Graph G = newGraph(n);
	List L = newList();

	// keep reading until the end of the file
	int vertexU, vertexV;
	while( fgets(str, MAX_LEN, in) != NULL)  {
		sscanf( str, "%d %d", &vertexU, &vertexV);
		if ( vertexU == 0 && vertexV == 0){
			break;
		}else{
			addEdge(G,vertexU,vertexV);
		}
    }
	// complete part 1
	printGraph(out,G);
	fprintf(out,"\n");
	// complete part 2
	while( fgets(str, MAX_LEN, in) != NULL)  {
		sscanf( str, "%d %d", &vertexU, &vertexV);
		if ( vertexU == 0 && vertexV == 0){
			break;
		}
		BFS(G,vertexU);
		getPath(L,G,vertexV);
		moveFront(L);
		// if the front is NIL
		if ( get(L) == NIL ) {
			fprintf(out,"The distance from %d to %d is infinity\n",vertexU,vertexV);
			fprintf(out,"No %d-%d path exists\n",vertexU,vertexV);
		}else{
			fprintf(out,"The distance from %d to %d is %d\n",vertexU,vertexV,getDist(G,vertexV));
			fprintf(out,"A shortest %d-%d path is: ",vertexU,vertexV);
			printList(out,L);
			fprintf(out,"\n");
		}
		fprintf(out,"\n");
		clear(L);
	}
	
	//printGraph(stdout,G);
    
	freeList(&L);
	freeGraph(&G);
    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}