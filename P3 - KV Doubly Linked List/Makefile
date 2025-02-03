CWFLAGS=-Wall -Wextra

all: kvDLL

kvDLL.o:	kvDLL.cpp kvDLL.h
	g++ $(CWFLAGS) -O2 -c kvDLL.cpp
	
kvDLLMain.o:	kvDLLMain.cpp kvDLL.h
	g++ $(CWFLAGS) -O2 -c kvDLLmain.cpp
	
kvDLL:	kvDLLMain.o kvDLL.o
	g++ $(CWFLAGS) -O2 kvDLLmain.o kvDLL.o -o kvDLL

clean:
	rm -f *.o kvDLL.exe kvDLL