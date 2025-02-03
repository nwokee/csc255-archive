#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "huffman.h"

using namespace std;


void huffman::clear(keyValue *p) {
    // if keyValue exists, clear its children and delete itself
    if (p) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}



void huffman::getEncodings(keyValue *p, encoding code, encoding *rv) const {
    if (p) {
        if (!p->left) {
            // no left child means no right child, means its a leaf
            // assign its spot with the right encoding

            // we get a warning when just using char, so this guarantees
            // an int
            int c = p->value;
            rv[c] = code;
        } else {
            // we're at a parent, adjust code and continue with its children
            code.pat <<= 1;
            code.patCount++;
            getEncodings(p->left, code, rv);
            code.pat++;
            getEncodings(p->right, code, rv);
        }
    }
}



void huffman::printPattern(char val, int freq, encoding code) const {
    cout << val << "(" << (100.0*(float)freq/(float)fileSize) << "%) ";
    for (int i = 0; i < code.patCount; i++) {
    cout << (int)(((code.pat >> (code.patCount - 1 - i)) & 1));
    }
    cout << endl;
}



void huffman::printIt(keyValue *p, encoding code) const {
    // dump out the pattern of the left, then itself, then the right node
    // ONLY IF THE NODE EXISTS
    if (p) {
        // check if node is a leaf, and print its pattern if it is
        if (!p->left) {
            // no left child means no right child, means its a leaf
            // so we can print its pattern
            
            // we get a warning when just using char, so this guarantees an int
            int valInd = p->value;
            // print the pattern of the node
            printPattern(p->value, freqs[valInd], code);
        } else {
            // add one bit and level to the pattern and patternCount
            code.pat <<= 1;
            code.patCount++;
            printIt(p->left, code);


            // switch code for the other side
            code.pat++;
            printIt(p->right, code);
        }
    }
}



void huffman::dumpTree(keyValue *p, encoding code) const {
    // dump out the pattern of the left, then itself, then the right node
    // ONLY IF THE NODE EXISTS
    if (p) {
        // make a copy of the code to add onto for the children
        encoding temp = code;

        // add one bit to the pattern and patternCount
        temp.pat <<= 1;
        temp.patCount++;
        dumpTree(p->left, temp);

        // we get a warning when just using char, so this guarantees an int
        int valInd = p->value;
        // print the pattern of the node
        printPattern(p->value, freqs[valInd], code);

        // switch code for the other side
        temp.pat++;
        dumpTree(p->right, temp);
    }
}



huffman::huffman() {
    // initialize all variables
    pq = new PQ(FCOUNT);
    freqs = new int[FCOUNT];
    fileSize = 0;
    root = NULL;
}



huffman::~huffman() {
    // clear the tree
    clear(root);

    // delete pq and freqs array
    if (pq) {
        delete pq;
    }

    if(freqs) {
        delete [] freqs;
        freqs = NULL;
    }
    
}



bool huffman::importFile(std::string fname) {
    // read in file name and setup returnCode
    ifstream infile(fname, ios::in);
    bool returnCode = !(!infile);
    
    if (returnCode) {
        char c;
        // read every character in the file
        while (infile.get(c)) {
            if (c < FCOUNT) {
                // we get a warning when just using char, so this guarantees
                // an int
                int i = c;
                freqs[i]++;
                fileSize++;
            }
        }
    }

    return returnCode;
}



void huffman::buildTree() {
    // go through every index in freqs
    // enqueuing it into the pq if it was found
    for (int i = 0; i < FCOUNT; i++) {
        if(freqs[i]) {
            // frequency of value is at least 1, enqueue it
            keyValue *kv = new keyValue(freqs[i], i);
            pq->enq(kv);
        }
    }

    // dequeue two smallest values, make a parent node for them
    // and enqueue the parent until 
    // there is only one value left in the queue
    while (pq->count() > 1) {
        // make left and right children
        keyValue *left = NULL;
        keyValue *right = NULL;

        // get the two smallest values in PQ
        pq->deq(left);
        pq->deq(right);

        // create and enqueue parent kv
        keyValue *parent = new keyValue(left->key + right->key,
                                        '@', left, right);

        pq->enq(parent);
    }

    // set final kv as root of the tree
    pq->deq(root);
}



void huffman::clear() {
    // traverse the tree, deleting all the nodes
    // and clear the counts and empty the pq
    
    clear(root);
    fileSize = 0;
    root = NULL;

    for (int i = 0; i < FCOUNT; i++) {
	freqs[i] = 0;
    }

    pq->clear();
}



encoding *huffman::getEncodings() const {
    encoding *rv = new encoding[FCOUNT];

    encoding code;
    code.pat = 0;
    code.patCount = 0;

    getEncodings(root, code, rv);

    return rv;
}



int huffman::getOutFileSizeBits() const {
    int rc = 0;

    encoding *encodings = getEncodings();


    for (int i = 0; i < FCOUNT; i ++) {
	rc += encodings[i].patCount * freqs[i];
    }

    delete [] encodings;

    return rc;
}



int huffman::getInFileSizeBytes() const {
    return fileSize;
}



void huffman::printIt() const {
    encoding code;
    code.pat = 0;
    code.patCount = 0;
    printIt(root, code);
}



void huffman::dumpTree() const {
    encoding code;
    code.pat = 0;
    code.patCount = 0;
    dumpTree(root, code);
}