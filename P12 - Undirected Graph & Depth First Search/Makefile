CWFLAGS=-Wall -Wextra

all: cList.o queue.o graph

cList.o: cList.cpp cList.h
	g++ $(CWFLAGS) -O2 -c cList.cpp

queue.o: queue.cpp queue.h
	g++ $(CWFLAGS) -O2 -c queue.cpp

graph.o: graph.cpp graph.h
	g++ $(CWFLAGS) -O2 -c graph.cpp

graphMain.o: graphMain.cpp graph.h
	g++ $(CWFLAGS) -O2 -c graphMain.cpp

graph: graphMain.o graph.o
	g++ $(CWFLAGS) -O2 graphMain.o graph.o queue.o cList.o -o graph

clean:
	rm -f *.o graph.exe graph queue.o cList.o
