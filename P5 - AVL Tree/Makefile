CWFLAGS=-Wall -Wextra

all: AVL

AVL.o:	AVL.cpp AVL.h
	g++ $(CWFLAGS) -O2 -c AVL.cpp
	
AVLMain.o:	AVLMain.cpp AVL.h 
	g++ $(CWFLAGS) -O2 -c AVLmain.cpp
	
AVL:	AVLMain.o AVL.o
	g++ $(CWFLAGS) -O2 AVLmain.o AVL.o -o AVL

clean:
	rm -f *.o AVL.exe AVL