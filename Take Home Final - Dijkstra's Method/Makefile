CWFLAGS=-Wall -Wextra

all: cList.o queue.o thf

cList.o: cList.cpp cList.h
	g++ $(CWFLAGS) -O2 -c cList.cpp

queue.o: queue.cpp queue.h
	g++ $(CWFLAGS) -O2 -c queue.cpp

thf.o: thf.cpp thf.h
	g++ $(CWFLAGS) -O2 -c thf.cpp

thfMain.o: thfMain.cpp thf.h
	g++ $(CWFLAGS) -O2 -c thfMain.cpp

thf: thfMain.o thf.o
	g++ $(CWFLAGS) -O2 thfMain.o thf.o cList.o queue.o -o thf

clean:
	rm -f *.o thf.exe thf queue.o cList.o
