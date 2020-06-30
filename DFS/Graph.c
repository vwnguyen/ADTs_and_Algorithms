//-----------------------------------------------------------------------------
// Graph.c
// Viet Nguyen
// ID: vwnguyen
// #: 1467315
// Assignment: pa5
// Description: Source file for Graph ADT implementation added on from pa4
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define INF -1
#define UNDEF -1
#define NIL 0
#define WHITE 1 // UNDISCOVERED
#define GRAY 2  // DISCOVERED BUT UNFINISHED
#define BLACK 3 // FINISHED
#define TRUE 1
#define FALSE 0

/*** Constructors-Destructors ***/

// data type to store vertex information
typedef struct vertex_info_obj {
    List adjacencyList;   // List of vertex adjacencies
    int color;  	
    int distance;   
	int parent;  
	int discoverTime;
	int finishTime;
}vertex_info_obj;

// graph objects
// order: number of vertices in the graph
// size: number of edges in the grpah
// source: the most recently used vertex by BFS
// 		   use source for determining if BFS was 
//		   ran or not
// graph info obj: object to store graph information

typedef struct GraphObj{
    int order;      // number of vertices
    int size;       // number of edges
    int source;     // vertex most recently used by BFS
    vertex_info_obj vertex[]; // array of vertex info objects
} GraphObj;

// we can now use Graph as a reference to a GraphObj*
typedef GraphObj* Graph;

// newGraph:
// Function newGraph() returns a Graph pointing to a
// newly created GraphObj representing a graph having
// n vertices and no edges. 
Graph newGraph(int n){
	// n + 1 because we will simplify our representation for
	// n + 2 results in no memory leaks... ask TA about this
    Graph G = malloc(sizeof(G) + (n+2) * sizeof(vertex_info_obj));
    
    for(int i=0; i<=n; i++){
        G->vertex[i].adjacencyList = newList();
        G->vertex[i].color = NIL;
        G->vertex[i].parent = NIL;
        G->vertex[i].distance = INF;
		
		G->vertex[i].discoverTime = UNDEF;
		G->vertex[i].finishTime = UNDEF;
    }
	
	G->order = n;
    G->size = 0;
    G->source = NIL;
    return G;
}
//  Function freeGraph() frees all dynamic memory associated 
//  with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        makeNull(*pG);
        for(int i=0; i<=(*pG)->order; i++){
            freeList(&((*pG)->vertex[i].adjacencyList));
        }
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

// returns the order of a graph
int getOrder(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling getOrder() on a NULL Graph reference\n");
      exit(1);
    }	
    return G->order;
}

// returns the size of a graph
int getSize(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling getSize() on a NULL Graph reference\n");
      exit(1);
    }	
    return G->size;
}

/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getDiscover() on a NULL Graph reference\n");
      exit(1);
    }	
	if(1 <= u && u <= getOrder(G)){
        return G->vertex[u].discoverTime;
    }else{
		printf("Graph Error: calling getDiscover() on u out of range\n");
		exit(1);
	}
}
/* Pre: 1<=u<=n=getOrder(G) */ 
int getFinish(Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getFinish() on a NULL Graph reference\n");
      exit(1);
    }
	if(1 <= u && u <= getOrder(G)){
        return G->vertex[u].finishTime;
    }else{
		printf("Graph Error: calling getFinish() on u out of range\n");
		exit(1);
	}
}

// return the source of a graph
// returns the source vertex most recently used in                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
// function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling getSource() on a NULL Graph reference\n");
      exit(1);
    }	

	return G->source;
}

// Precondition: 1 <= u <= getOrder(G)
// returns the parent of vertex[u] in Graph G
int getParent(Graph G, int u){
	
	if( G==NULL ){
      printf("Graph Error: calling getParent() on a NULL Graph reference\n");
      exit(1);
    }	
	
    if(1 <= u && u <= getOrder(G)){
        return G->vertex[u].parent;
    }else{
		printf("Graph Error: calling getParent() on u out of range\n");
		exit(1);
	}
}

// Precondition: 1 <= u <= getOrder(G)
// Function getDist() returns the
// distance from the most recent BFS source to vertex u, 
// or INF if BFS() has not yet been called. 
int getDist(Graph G, int u){
	
	if( G==NULL ){
      printf("Graph Error: calling getDist() on a NULL Graph reference\n");
      exit(1);
    }
	// case that BFS was not called yet 
	if ( G->source == NIL ){
		return INF;
	}
	
    if(1 <= u && u <= getOrder(G)){
		return G->vertex[u].distance;
    }else{
		printf("Graph Error: calling getDist() on u out of range\n");
		exit(1);
	}
}

// getPath()
// Precondition: 1 <= u <= getOrder(G)
// Precondition: getSource(G)!=NIL, so BFS() must be called before getPath()
// Function getPath() appends to the List L the vertices of a 

// shortest path in G from source to u, or appends to L the
// value NIL if no such path exists. getPath() has the 
// be called before getPath(). 

// a recursive function that has to bottom out once the top 
// parent node is found.
// once parent node is found. append to list, and begin 
// recursive trace

void getPath(List L, Graph G, int u){
	
	if( G==NULL ){
      printf("Graph Error: calling getPath() on a NULL Graph reference\n");
      exit(1);
    }	
	if( L==NULL ){
      printf("Graph Error: calling getPath() on a NULL List reference\n");
      exit(1);
    }	
	if(getSource(G) == NIL){
		printf("Graph Error: calling getPath() without running BFS first\n");
		exit(1);
	}
	if(1 <= u && u <= getOrder(G)){
		// if BFS has been run on this graph, then 
		// the source would not be NIL
		if(G->source == u){
			// if getPath finds the source
			append(L, u);
		}else if(G->vertex[u].parent == NIL){
			// if no path exists
			append(L,NIL);
		}else{
			// if a parent does exist, i.e. a path does exist
			getPath(L, G, G->vertex[u].parent);
			append(L, u);
		}
		
	}else{
		printf("Graph Error: calling getPath() on u out of range\n");
		exit(1);
	}
}

/*** Manipulation procedures ***/

// Precondition: 1 <= u <= getOrder(G)
// Function makeNull() deletes all edges of G, restoring
// it to its original (no edge) state

void makeNull(Graph G){
    
	if( G!=NULL ){
      //printf("Graph Error: calling getPath() on a NULL Graph reference\n");
		for(int i=0; i<=getOrder(G); i++){
			clear(G->vertex[i].adjacencyList);
		}
	}
	// reset the fields
    G->size = 0;
	G->order = 0;
	G->source = NIL;
}

// Precondition: 1 <= u <= getOrder(G) &&  1 <= v <= getOrder(G)
// Function addArc() adds a directed edge to Graph G

void addArc(Graph G, int u, int v){
	
	int NEW_EDGE = TRUE;
	if( G==NULL ){
      printf("Graph Error: calling addArc() on a NULL Graph reference\n");
      exit(1);
    }	
	// check the precondition
    if((1<=u && u<=G->order) && (1<=v && v<=G->order)){    
        // in the event that u has at least 1 other edge
        if(length(G->vertex[u].adjacencyList) > 0){
            moveFront(G->vertex[u].adjacencyList);
            while(index(G->vertex[u].adjacencyList) != UNDEF){
                // if the edge already exists, break 
                if(get(G->vertex[u].adjacencyList) == v){
                    NEW_EDGE = FALSE;
                    break;
                }
                if(v < get(G->vertex[u].adjacencyList)){
                    insertBefore(G->vertex[u].adjacencyList, v);
                    break;
                }
                moveNext(G->vertex[u].adjacencyList);
                // in the event that the edge needs to be inserted at the end of the list
                if(index(G->vertex[u].adjacencyList) == UNDEF){
                    append(G->vertex[u].adjacencyList, v);
                }
            }
        }else{
            // in the event that u has no edges
            prepend(G->vertex[u].adjacencyList, v);
        }
        if(NEW_EDGE==TRUE){
			G->size++;
		}
    }else{
		printf("Graph Error: calling addArc() using either v or u out of range\n");
		exit(1);
	}
}

// addEdge() inserts a new edge
// joining u to v, i.e. u is added to the adjacencyListacency List of v,
// and v to the adjacencyListacency List of u. Your program is
// required to maintain these lists in sorted order by increasing labels. 

void addEdge(Graph G, int u, int v){
	
	if( G==NULL ){
      printf("Graph Error: calling addEdge() on a NULL Graph reference\n");
      exit(1);
    }	
	if((1<=u && u<=G->order) && (1<=v && v<=G->order)){    
		addArc(G,u,v);
		// account for, if this is a valid edge, we dont 
		// want to increase the size 2x for each addition.
		G->size--;
		addArc(G,v,u);
	}
}

// inspired from the BFS code from the Graph Algorithms Handout 

void BFS(Graph G, int s){
    G->source = s;
    List Q = newList();
    int x = 0;
	int y = 0;
    // initialize all vertices to NIL
    for(x=1; x<=getOrder(G); x++){
        G->vertex[x].color = WHITE;
        G->vertex[x].distance = INF;
        G->vertex[x].parent = NIL;
    }
	// correct the source vertex
    G->vertex[s].color = GRAY;
    G->vertex[s].distance = 0;
    G->vertex[s].parent = NIL;
    
    // initialize queue
    append(Q, s);
    
    while(length(Q) != 0){
        x = front(Q);
        deleteFront(Q);
        for(moveFront(G->vertex[x].adjacencyList); index(G->vertex[x].adjacencyList)!=UNDEF; moveNext(G->vertex[x].adjacencyList)){
            y = get(G->vertex[x].adjacencyList);
			if(G->vertex[y].color == WHITE){
				G->vertex[y].color = GRAY;
				G->vertex[y].distance = G->vertex[x].distance + 1;
				G->vertex[y].parent = x;
				append(Q, y);
			}
        }
        G->vertex[x].color = BLACK;
    }
	// remember to free after usage
    freeList(&Q);
}

// recursive function used by DFS

void Visit(Graph G, List S, int u, int* time){
	int y;
    G->vertex[u].color = GRAY;
	*time = (*time) + 1;
    G->vertex[u].discoverTime =  *time;
	//printf("beginning of Visit() on %d, time: %d\n",u,*time);
    if ( length(G->vertex[u].adjacencyList) != 0 ){
		moveFront(G->vertex[u].adjacencyList);
		while( index(G->vertex[u].adjacencyList) != UNDEF ){
			
			y = get(G->vertex[u].adjacencyList);

			if(G->vertex[y].color == WHITE){
				G->vertex[y].parent = u;
				Visit(G, S, y, time);
			}
			
			moveNext(G->vertex[u].adjacencyList);
		}   
	}		
    
    G->vertex[u].color = BLACK;
	*time = (*time) + 1;
    G->vertex[u].finishTime = *time;
	//printf("end of Visit() on %d, time: %d\n",u,*time);
    prepend(S, u);
}

/* Pre: length(S)==getOrder(G) */
// inspired by the DFS algorithm  on the Graph Handouts 
void DFS(Graph G, List S){
	int time = 0;
    for(int i=1; i<=G->order; i++){
        G->vertex[i].color = WHITE;
        G->vertex[i].parent = NIL;
    }
	//List inputStack = copyList(S);

	
	
    if(length(S) == getOrder(G)){
		List inputStack = copyList(S);
		//printf("S: ");
		//printList(stdout,S);
		//printf("\n");
		//printf("C: ");
		//printList(stdout,inputStack);
		//printf("\n");
		clear(S);
		moveFront(inputStack);
        while( index(inputStack) != UNDEF ){
            if(G->vertex[get(inputStack)].color == WHITE){
				Visit(G, S, get(inputStack),&time);
			}
			moveNext(inputStack);
        }
		freeList(&inputStack);
        
    }else{ // run in increasing order
		printf("Graph Error: calling DFS() with length(S) != getOrder(G)\n");
		exit(1);
	}
	// freeList(&inputStack);
}


/*** Other operations ***/
Graph transpose(Graph G){
	
	if( G==NULL ){
      printf("Graph Error: calling transpose() on a NULL Graph reference\n");
      exit(1);
    }	
	
	Graph tG = newGraph(G->order); // create graph with same order
	tG->size = G->size;
	for(int i=1; i<=G->order; i++){
        if(length(G->vertex[i].adjacencyList) != 0){
			moveFront(G->vertex[i].adjacencyList);
            while(index(G->vertex[i].adjacencyList) != UNDEF){
				// add arc to tG at u, v
                addArc(tG, get(G->vertex[i].adjacencyList), i);
				moveNext(G->vertex[i].adjacencyList);
            }
        }
    }
    return tG;
}


Graph copyGraph(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling copyGraph() on a NULL Graph reference\n");
      exit(1);
    }	
	
	Graph nG = newGraph(G->order); // create graph with same order
	nG->size = G->size;
	// go through each of the vertex lists, append as needed
	for(int i=1; i<=getOrder(G); i++){
		// if the vertex list is not empty we need to populate it 
		if ( length(G->vertex[i].adjacencyList) != 0 ){
			moveFront(G->vertex[i].adjacencyList);
			while(index(G->vertex[i].adjacencyList) != UNDEF){
				append(nG->vertex[i].adjacencyList,get(G->vertex[i].adjacencyList));
				moveNext(G->vertex[i].adjacencyList);
			}
		}
	}
	return nG;
}


void printGraph(FILE* out, Graph G){
    int i;
    for(i=1; i<=getOrder(G); i++){
        fprintf(out,"%i: ", i);
        printList(out, G->vertex[i].adjacencyList);
        fprintf(out, "\n");
    }
}
