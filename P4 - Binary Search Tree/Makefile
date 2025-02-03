CWFLAGS=-Wall -Wextra

all: BST

BST.o:	BST.cpp BST.h
	g++ $(CWFLAGS) -O2 -c BST.cpp
	
BSTMain.o:	BSTMain.cpp BST.h 
	g++ $(CWFLAGS) -O2 -c BSTmain.cpp
	
BST:	BSTMain.o BST.o
	g++ $(CWFLAGS) -O2 BSTmain.o BST.o -o BST

clean:
	rm -f *.o BST.exe BST