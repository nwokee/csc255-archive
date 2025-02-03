#ifndef __PQ_H
#define __PQ_H

typedef struct key_value {
    int key;
    int value;
} KEY_VALUE;

class PQ {
    private:
    KEY_VALUE* keys;
    int qCount, pqSize;

    // returns the parent’s index for the given index; returns 0 if index is 0
    int parent(int index) const; 

    // returns the index of the left child of the given index
    int left(int index) const; 

    // returns the index of the right child of the given index
    int right(int index) const; 

    void printIt(int ind, int count) const; // prints the tree, level by level
    void swap(KEY_VALUE *x, KEY_VALUE *y); // swaps two KVs with each other
    void bubbleUp(int index); // performs the heap bubble-up operation
    void heapify(int i); // performs the heap heapify operation

    public:
    PQ(int n = 100); // constructor
    ~PQ(); // destructor

    // adds new kv to the priority queue if it was not already full
    bool enq(KEY_VALUE kv); 

    // removes highest priority kv from queue if it wasn't already empty
    bool deq(KEY_VALUE &kv);

    void printIt() const; // prints the keys in breadth first order
    void clear(); // removes all the keys from the PQ, making it empty
    int count() const; // returns the number of keys in the PQ
};

#endif