#ifndef QUEUE_H
#define QUEUE_H

#include "cList.h"

class queue {
private:
    cKeyValueList *theList;

public:
    queue(int n = 100); // the constructor
    ~queue(); // the destructor; deletes the list structure

    bool enq(int v); // enqueues the value v into the queue
    bool deq(int &v); // dequeues the oldest value, returns that value in v
    void clear(); // removes all items in the queue
    int count() const; // returns the number of items in the queue
    void printIt() const; // prints the contents of the queue
};

#endif