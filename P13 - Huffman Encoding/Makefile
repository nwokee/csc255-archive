CWFLAGS=-Wall -Wextra

all: PQ.o huffman

PQ.o: PQ.cpp PQ.h
	g++ $(CWFLAGS) -O2 -c PQ.cpp

huffman.o: Huffman.cpp huffman.h
	g++ $(CWFLAGS) -O2 -c Huffman.cpp

huffmanMain.o: huffmanMain.cpp huffman.h
	g++ $(CWFLAGS) -O2 -c huffmanMain.cpp

huffman: huffmanMain.o huffman.o
	g++ $(CWFLAGS) -O2 huffmanMain.o huffman.o PQ.o -o huffman

clean:
	rm -f *.o huffman.exe huffman PQ.o
