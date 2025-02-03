CWFLAGS=-Wall -Wextra

all: graph

graph.o:	graph.cpp graph.h
	g++ $(CWFLAGS) -O2 -c graph.cpp
	
graphMain.o:	graphMain.cpp graph.h 
	g++ $(CWFLAGS) -O2 -c graphMain.cpp
	
graph:	graphMain.o graph.o
	g++ $(CWFLAGS) -O2 graphMain.o graph.o -o graph

clean:
	rm -f *.o graph.exe graph