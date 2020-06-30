//-----------------------------------------------------------------------------
// List.c
// Viet Nguyen
// ID: vwnguyen
// #: 1467315
// Assignment: pa5
//-----------------------------------------------------------------------------

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// structs --------------------------------------------------------------
// private NodeObj type

typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
// Node can now be used to reference a NodeObj
typedef NodeObj* Node;


// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	int length;
	Node cursor;
	int indexOfCursor;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void){ // Creates and returns a new empty List.
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->length = 0;
   L->indexOfCursor = -1;
   return(L);
}
void freeList(List* pL){ // Frees all heap memory associated with *pL, and sets
// *pL to NULL.
	clear(*pL);
	if( pL!=NULL && *pL!=NULL ){
		free(*pL);
		*pL = NULL;
	}

}
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ){
		free(*pN);
		*pN = NULL;
	}
}

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
int front(List L); // Returns front element of L. Pre: length()>0
int back(List L); // Returns back element of L. Pre: length()>0
int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
int equals(List A, List B); // Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.

// preconditions: none
// postconditions: returns current length of list
int length(List L){
	if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
    }
	return L->length;
}
// preconditions: none
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
	return L->indexOfCursor;
}

// Returns front element of L. Pre: length()>0
int front(List L){
	if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling front() on List of length <= 0\n");
		return -1;
	}else{
		return L->front->data;
	}
}

// Returns front element of L. Pre: length()>0
int back(List L){
	if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling back() on List of length <= 0\n");
		return -1;
	}else{
		return L->back->data;
	}
}
//Pre: length()>0, index()>=0
int get(List L){
	if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
    }
	if( length(L) <= 0 ){
		printf("List Error: calling get() on List of length <= 0\n");
		exit(1);
	}
	if( index(L) < 0 ){
		printf("List Error: calling get() on List with index < 0\n");
		exit(1);
	}

	return L->cursor->data;
	
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.

int equals(List A, List B){
	int i = 0;
	int lengthA = length(A);
	int lengthB = length(B);
	
	if ( lengthA == 0 && lengthB == 0 ) {
		return 1;
	}else if ( lengthA == lengthB ) {	
		Node Aref = newNode(A->front->data);
		Node Bref = newNode(B->front->data);
		Aref = A->front;
		Aref->next = A->front->next;
		Bref = B->front;
		Bref->next = B->front->next;
		
		for ( i = 0; i < lengthA ; i++ ){
			if ( Aref->data != Bref->data ){
				return 0; // returning false
			}
			Aref = Aref->next;
			Bref = Bref->next;
		}
		return 1;
	}else{
		return 0;
	}
}

// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void moveFront(List L); // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void prepend(List L, int data); // Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void append(List L, int data); // Insert new element into L. If L is non-empty,
// insertion takes place after back element.

void insertBefore(List L, int data); // Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data); // Insert new element before cursor.
// Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.


// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, int x){
	if( L==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(1);
	}
	if( index(L) < 0 ){
	  printf("List Error: calling set() on List with index < 0\n");
      exit(1);
	}
	L->cursor->data = x; 
}

// Pre: length()>0, index()>=0
// Insert new element into L.
// If L is non-empty, insertion takes place after back element.
void append(List L, int data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if( length(L) <= 0 ) { 
      L->front = L->back = N; 
   }else{ 
      L->back->next = N;
	  N->prev = L->back;
      L->back = N; 
   }
   L->length++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
   Node N = newNode(data);
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if( length(L) <= 0 ) { 
      L->front = L->back = N; 
   }else{
	  // if the index is defined on the list
	  if ( index(L) != -1 ) {
		  L->indexOfCursor++;
	  }
	  L->front->prev = N;
	  N->next = L->front;
	  L->front = N;
   }
   L->length++;
}

void moveFront(List L){ // If L is non-empty, sets cursor under the front element,
						// otherwise does nothing.
	if( L==NULL ){
      printf("List Error: calling moveFront) on NULL List reference\n");
      exit(1);
    }	
	
	if ( length(L) > 0 ) { 
		L->cursor = L->front;
		L->cursor->data = (L->front->data);
		L->indexOfCursor = 0;
	}
}

void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
						// otherwise does nothing.		
	if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
    }								
	if ( length(L) > 0 ) { 
		L->cursor = L->back;
		L->cursor->data = L->back->data;
		L->indexOfCursor = length(L) - 1;
	}
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; 
// if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
	if ( L->indexOfCursor != -1 && L->indexOfCursor != 0 ){ // if the cursor is defined and not at the front
		// move the cursor one step towards the front
		L->indexOfCursor = L->indexOfCursor - 1;
		L->cursor = L->cursor->prev;
	}else if ( L->indexOfCursor == 0 ){ // cursor is defined and at the front
		L->indexOfCursor = -1;
	}else if (L->indexOfCursor == -1){
		// do nothing
	}
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing

void moveNext(List L){
	
	if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
    }
	if ( L->indexOfCursor != -1 && L->indexOfCursor != length(L)-1 ){ // if the cursor is defined and not at the back
		// move the cursor one step towards the back
		L->indexOfCursor = L->indexOfCursor + 1;
		L->cursor = L->cursor->next;
	}else if ( L->indexOfCursor == length(L)-1 ){ // cursor is defined and at the back
		L->indexOfCursor = -1;
	}else if (L->indexOfCursor == -1){
		// do nothing
	}
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling insertBefore() on List of length <= 0\n");
		exit(1);
	}else if( index(L) < 0 ){
		printf("List Error: calling insertBefore() on List with index < 0\n");
		exit(1);
	}else{
		if( index(L) == 0 ){ // if the length is one, all you need to do is prepend it. 
			prepend(L,data);  
		}else{
			Node N = newNode(data); // create new node with data
			N->next = L->cursor;
			N->prev = L->cursor->prev;
			L->cursor->prev->next = N;
			L->cursor->prev = N;
			L->length++;
			L->indexOfCursor++;
		}
		
		
	}
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L,int data){
	if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling insertAfter() on List of length <= 0\n");
		exit(1);
	}else if( index(L) < 0 ){
		printf("List Error: calling insertAfter() on List with index < 0\n");
		exit(1);
	}else{
		if( length(L) == 1 || index(L) == length(L)-1 ){ // if you are inserting after the first or last element, 
														 // just append it.
			append(L,data);  
		}else{
			Node N = newNode(data); // appropriate switching logic
			N->next = L->cursor->next;
			L->cursor->next->prev = N;
			N->prev = L->cursor;
			L->cursor->next = N;
			L->length++;
		}
	}
	
}

// Pre: length()>0, index()>=0
void deleteFront(List L){ // Delete the front element. Pre: length()>0
	if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling deleteFront() on List of length <= 0\n");
		exit(1);
	} else {
		// if the index is already at the front
		if ( index(L) == 0 ){
			L->cursor = NULL;
			L->indexOfCursor = -1;
		}else if ( index(L) <= length(L)-1 ){
			L->indexOfCursor--;
		}
		Node N = newNode(L->front->data);
		//L->front; // reference node to the front
		L->front = L->front->next;
		freeNode(&N);
		L->length--;
	}	
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){ // Delete the back element. Pre: length()>0
	if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling deleteBack() on List of length <= 0\n");
		exit(1);
	} else if ( length(L) == 1 ) {
		clear(L);
	} else {		
		// at this point length is > 0 
		if ( index(L) == length(L)-1 ){
			L->cursor = NULL;
			L->indexOfCursor = -1;
		}
		
		Node N = L->back; // reference node to the back
		L->back = L->back->prev; // list's back is now the list's previous back
		L->back->next = NULL;
		freeNode(&N);
		L->length--;
	}
}
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
    }else if( length(L) <= 0 ){
		printf("List Error: calling delete() on List of length <= 0\n");
		exit(1);
	}else if ( index(L) == 0){ // front element
		deleteFront(L);
	}else if (index(L) == length(L)-1 ){ //back element
		deleteBack(L);
	}else{ // some inbetween element
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->length--;
	}
	L->cursor = NULL;
	L->indexOfCursor = -1;
}

void clear(List L){ // Resets L to its original empty state.
	if( L==NULL ){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
    }
	//int i = 0;
	moveFront(L);
	//printf("i: %d length: %d, index: %d\n",i,length(L),index(L));
	
	while ( length(L) > 0 ){
		delete(L);
		moveFront(L);
		//printf("i: %d length: %d, index: %d\n",i,length(L),index(L));
		//printList(stdout,L);
	}
	L->front = L->back = NULL;
	L->length = 0;
	L->indexOfCursor = -1;
}


// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.

void printList(FILE* out, List L){
	
	if ( L == NULL ){
		fprintf(stderr,"List Error: calling printList() on NULL Dictionary reference\n");
		exit(1);
	}
	
	if ( L->front != NULL ){
		Node N = newNode(L->front->data);
		N->next = L->front->next;
		while( N != NULL ){
			fprintf(out,"%d ",N->data);
			N = N->next;
		}
		//fprintf(out,"\n");
		
	}
}


// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
	
	if ( L == NULL ){
		fprintf(stderr,"List Error: calling copyList() on NULL Dictionary reference\n");
		exit(1);
	} else if ( length(L) == 0 ){
		List emptyList = newList();
		return emptyList;
	}
	
	List copiedList = newList();
	int i = 0;
	int lengthOfList = length(L);
	
	Node N = newNode(L->front->data);
	N = L->front;
	N->next = L->front->next;

	for ( i = 0; i < lengthOfList; i++){
		append(copiedList,N->data);
		N = N->next;
	}
	return copiedList;
}

