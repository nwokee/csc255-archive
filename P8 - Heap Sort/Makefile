CWFLAGS=-Wall -Wextra

all: heapSort

list.o:	list.cpp list.h
	g++ $(CWFLAGS) -O2 -c list.cpp
	
heapSortMain.o:	heapSortMain.cpp list.h 
	g++ $(CWFLAGS) -O2 -c heapSortMain.cpp
	
heapSort:	heapSortMain.o list.o
	g++ $(CWFLAGS) -O2 heapSortMain.o list.o -o heapSort

clean:
	rm -f *.o heapSort.exe heapSort