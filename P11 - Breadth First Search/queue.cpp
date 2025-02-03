#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "queue.h"

using namespace std;



queue::queue(int n) {
    // setup new KV queue using cList 
    theList = new cKeyValueList(n);
}



queue::~queue() {
    // call the cList deconstructor and delete the object
    if(theList) {
        delete [] theList;
        theList = NULL;
    }
}



bool queue::enq(int v) {
    //create new kv with k of v and value of 0
    KEY_VALUE kv;
    kv.key = v;

    // use cList add to the end of the cList
    // and storing the result in returnCode
    bool returnCode = theList->add(kv);

    return returnCode;
}



bool queue::deq(int &v) {
    // create kv we're going to use to dequeue, as well as presetting their key
    KEY_VALUE kv;
    kv.key = -1;


    // use cList's deleteFirst to remove the first value
    // and store the result in returnCode
    bool returnCode = theList->deleteFirst(kv);
    
    // store the value of the kv in v
    v = kv.key;

    return returnCode;


}



void queue::clear() {
    // clear the cList we're using with its own clear
    theList->clear();
}



int queue::count() const {
    // get the count of the cList we're using
    return theList->getCount();
}



void queue::printIt() const {
    // use cList's printIt to print out the queue
    theList->printIt(0);
}