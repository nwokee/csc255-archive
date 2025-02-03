CWFLAGS=-Wall -Wextra

all: cList cListTime

cList.o:	cList.cpp cList.h
	g++ $(CWFLAGS) -O2 -c cList.cpp

cListMainTime.o:	cListMainTime.cpp cList.h
	g++ $(CWFLAGS) -O2 -c cListMainTime.cpp
	
cListMain.o:	cListMain.cpp cList.h
	g++ $(CWFLAGS) -O2 -c cListMain.cpp
	
cList:	cListMain.o cList.o
	g++ $(CWFLAGS) -O2 cListMain.o cList.o -o cList

cListTime:	cListMainTime.o cList.o
	g++ $(CWFLAGS) -O2 cListMainTime.o cList.o -o cListTime

clean:
	rm -f *.o cList.exe cListTime.exe cList cListTime
