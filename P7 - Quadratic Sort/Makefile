CWFLAGS=-Wall -Wextra

all: quadSort

list.o:	list.cpp list.h
	g++ $(CWFLAGS) -O2 -c list.cpp
	
quadSortMain.o:	quadSortMain.cpp list.h 
	g++ $(CWFLAGS) -O2 -c quadSortMain.cpp
	
quadSort:	quadSortMain.o list.o
	g++ $(CWFLAGS) -O2 quadSortMain.o list.o -o quadSort

clean:
	rm -f *.o quadSort.exe quadSort