CWFLAGS=-Wall -Wextra

all: AVL

AVL.o:	AVL.cpp AVL.h
	g++ $(CWFLAGS) -O2 -c AVL.cpp
	
OSmain.o:	OSmain.cpp AVL.h 
	g++ $(CWFLAGS) -O2 -c OSmain.cpp
	
AVL:	OSmain.o AVL.o
	g++ $(CWFLAGS) -O2 OSmain.o AVL.o -o AVL

clean:
	rm -f *.o AVL.exe AVL