CWFLAGS=-Wall -Wextra

all: MSQS

list.o:	list.cpp list.h
	g++ $(CWFLAGS) -O2 -c list.cpp
	
MSQSmain.o:	MSQSmain.cpp list.h 
	g++ $(CWFLAGS) -O2 -c MSQSmain.cpp
	
MSQS:	MSQSmain.o list.o
	g++ $(CWFLAGS) -O2 MSQSmain.o list.o -o MSQS

clean:
	rm -f *.o MSQS.exe MSQS