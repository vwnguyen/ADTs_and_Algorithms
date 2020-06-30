#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 5
#
#  make                     makes FindComponents
#  make clean               removes all binaries
#  make memcheck            runs FindComponents Client under valgrind
#------------------------------------------------------------------------------

CLIENT         = FindComponents
ADT1           = Graph
ADT2           = List
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

GraphClient : GraphClient.o Graph.o List.o
	$(LINK) GraphTest GraphTest.o Graph.o List.o

GraphClient.o : GraphClient.c Graph.h List.h
	$(COMPILE) GraphClient.c

GraphTest : GraphTest.o Graph.o List.o
	$(LINK) GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c Graph.h List.h
	$(COMPILE) GraphTest.c
	
submit : 
	submit cse101-pt.f19 pa5 FindComponents.c Graph.c Graph.h List.c List.h GraphTest.c README Makefile

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) GraphTest GraphClient *.o

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)
