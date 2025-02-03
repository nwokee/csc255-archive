#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "huffman.h"

using namespace std;

//******************************************************************************

int main(int argc, char *argv[]) {
    int bitCount;
    int byteCount;

    if (argc == 2) {
	huffman *myHuff = new huffman();

	string s(argv[1]);
	myHuff->importFile(s);
	myHuff->buildTree();

	//cerr << "The dump is:" << endl;
	//myHuff->dumpTree();

	myHuff->printIt();

	bitCount = myHuff->getOutFileSizeBits();
	byteCount = bitCount/8;
	if (bitCount % 8) {
	    byteCount++;
	}

	cout << "The encoded file would have ";
	cout << bitCount;
	cout << " bits which would be ";
	cout << byteCount;
	cout << " bytes; giving a ratio of ";
	cout << (float)byteCount/(float)(myHuff->getInFileSizeBytes()) * 100.0;
	cout << "%" << endl;
    } else {
	cerr << "Usage: " << argv[0] << " filename" << endl;
    }
}

//******************************************************************************
