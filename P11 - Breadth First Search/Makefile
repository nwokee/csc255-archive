CWFLAGS=-Wall -Wextra

all: cList.o queue graph

cList.o: cList.cpp cList.h
	g++ $(CWFLAGS) -O2 -c cList.cpp

graph.o: graph.cpp graph.h
	g++ $(CWFLAGS) -O2 -c graph.cpp

graphBFSmain.o: graphBFSmain.cpp graph.h
	g++ $(CWFLAGS) -O2 -c graphBFSmain.cpp

graph: graphBFSmain.o graph.o
	g++ $(CWFLAGS) -O2 graphBFSmain.o graph.o queue.o cList.o -o graph

queue.o: queue.cpp queue.h
	g++ $(CWFLAGS) -O2 -c queue.cpp

queueMain.o: queueMain.cpp queue.h
	g++ $(CWFLAGS) -O2 -c queueMain.cpp

queue: queueMain.o queue.o
	g++ $(CWFLAGS) -O2 queueMain.o queue.o cList.o -o queue 

clean:
	rm -f *.o graph.exe queue.exe graph queue cList.o
