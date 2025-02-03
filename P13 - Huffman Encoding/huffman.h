#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include "PQ.h"

class encoding {
    public:
    int patCount; // length of a bit encoding
    unsigned int pat;   // bit encoding
};


class huffman {
    private:
    static const int FCOUNT = 128;
    PQ *pq;
    int *freqs; // array of frequencies for characters
    int fileSize; // count of total characters in the text
    keyValue *root; // root of the Huffman tree

    // the private, recursive version of clear
    void clear(keyValue *p); 

    // Fills the entries of the rv array that gets passed in
    void getEncodings(keyValue *p, encoding code, encoding *rv) const;

    // prints the value and frequency of a given node
    // as well as the binary encoding for the node
    void printPattern(char val, int freq, encoding code) const; 

    // Huffman in order tree traversal that
    // prints every leaf of the tree
    void printIt(keyValue *p, encoding code) const; 

    // Huffman in order tree traversal that
    // prints every NODE of the tree (including the @'s)
    void dumpTree(keyValue *p, encoding code) const;

    public:
    // the constructor; it will cause, among other things
    // the PQ to be created with FCOUNT capacity.
    huffman();

    // the destructor; lots of details to be managed
    // but it can manage all that in three lines.
    ~huffman();

    // this reads the input file, character by character
    // For each character it keeps count in freqs[]
    // also keeps track of the input file’s size.
    bool importFile(std::string fname);

    // This is used after the input file has been read in and processed. 
    // For each non-zero entry in freqs[]
    // create a keyValue for that character and enter it into the PQ.
    void buildTree();

    // clears the Huffman tree
    void clear();

    // returns an array of every characters code for the text that is read in
    encoding *getEncodings() const;

    int getOutFileSizeBits() const;
    int getInFileSizeBytes() const;

    // prints every leaf in the tree
    void printIt() const;

    // prints every node in the tree
    void dumpTree() const;
};

#endif