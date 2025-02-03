CWFLAGS=-Wall -Wextra

all: list listTime

list.o:	list.cpp list.h
	g++ $(CWFLAGS) -O2 -c list.cpp

listMainTime.o:	listMainTime.cpp list.h
	g++ $(CWFLAGS) -O2 -c listMainTime.cpp
	
listMain.o:	listMain.cpp list.h
	g++ $(CWFLAGS) -O2 -c listMain.cpp
	
list:	listMain.o list.o
	g++ $(CWFLAGS) -O2 listMain.o list.o -o list

listTime:	listMainTime.o list.o
	g++ $(CWFLAGS) -O2 listMainTime.o list.o -o listTime

clean:
	rm -f *.o list.exe listTime.exe list listTime
