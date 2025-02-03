CWFLAGS=-Wall -Wextra

all: PQ

PQ.o:	PQ.cpp PQ.h
	g++ $(CWFLAGS) -O2 -c PQ.cpp
	
PQMain.o:	PQMain.cpp PQ.h 
	g++ $(CWFLAGS) -O2 -c PQmain.cpp
	
PQ:	PQMain.o PQ.o
	g++ $(CWFLAGS) -O2 PQmain.o PQ.o -o PQ

clean:
	rm -f *.o PQ.exe PQ