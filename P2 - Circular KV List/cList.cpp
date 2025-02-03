#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "cList.h"

using namespace std;

 

int cKeyValueList::virtualToPhysical(int virtualIndex) const {
    // compare location to first index
    return (first + virtualIndex) % listCapacity;
}

 

int cKeyValueList::physicalToVirtual(int physicalIndex) const {
    // find the difference from the first index
    return (physicalIndex - first + listCapacity) % listCapacity;
}



cKeyValueList::cKeyValueList(int theCapacity) {
    // initialize variables and allocate memory for circular list
    listCapacity = theCapacity;
    listCount = 0;
    first = 0;
    last = 0;
    keyValues = new KEY_VALUE[listCapacity];
}

 

cKeyValueList::~cKeyValueList() {
    // free keyValues memory and delete the object
    if(keyValues) {
        delete [] keyValues;
        keyValues = NULL;
    }
}

 

bool cKeyValueList::insert(KEY_VALUE kv) {
    // check if list is full
    bool returnCode = listCount < listCapacity;

    if(returnCode) {
        // rotate starting point back one and insert new kv
        cListDec(first);
        keyValues[first] = kv;
        listCount++;

        //adjust last spot if list was empty
        if(listCount == 1) {
            last = first;
        }
    }

    return returnCode;
}

 

bool cKeyValueList::add(KEY_VALUE kv) {
    // check if list is full
    bool returnCode = listCount < listCapacity;

    if(returnCode) {
        //adjust last spot if list was not empty
        if(listCount) {
            cListInc(last);
        }

        //increment last entry and append new kv
        keyValues[last] = kv;
        listCount++;
    }
    
    return returnCode;
}

 

bool cKeyValueList::insertAt(int index, KEY_VALUE kv) {
    //check if list is full and if index is in bounds
    bool returnCode = (listCount < listCapacity);
    returnCode = returnCode && (index > -1) && (index <= listCount);

    if(returnCode) {
        // rotate all items ahead of (index) one spot
        for(int i = listCount; i > index; i--) {
            int newIndex = virtualToPhysical(i);
            int oldIndex = virtualToPhysical(i-1);
            keyValues[newIndex] = keyValues[oldIndex];
        }

        // insert new kv and update list size
        int insertIndex = virtualToPhysical(index);
        keyValues[insertIndex] = kv;
        cListInc(last);
        listCount++;

        // readjust list size if list was empty
        if(listCount == 1) {
            last = first;
        }
    }
    
    return returnCode;
}

 

bool cKeyValueList::deleteAt(int index, KEY_VALUE &kv) {
    //check if list is empty and if index is in bounds
    bool returnCode = (listCount > 0) && (index > -1) && (index < listCount);

    if(returnCode) {
        //store value to be removed
        int removeIndex = virtualToPhysical(index);
        kv = keyValues[removeIndex];

        //rotate every element before index back one and adjust list size
        for(int i = index; i < listCount; i++) {
            int newIndex = virtualToPhysical(i);
            int oldIndex = virtualToPhysical(i+1);
            keyValues[newIndex] = keyValues[oldIndex];
        }

        listCount--;

        if(listCount) {
            cListDec(last);
        }
    }
    
    return returnCode;
}

 

bool cKeyValueList::deleteFirst(KEY_VALUE &kv) {
    // check if list is empty
    bool returnCode = listCount;

    if (returnCode) {
        // store value to be removed
        kv = keyValues[first];

        // rotate start of the list and adjust listCount
        if(listCount > 1) {
            cListInc(first);
        }
        listCount--;
    }

    return returnCode;
}

 

bool cKeyValueList::deleteLast(KEY_VALUE &kv) {
    //check if list is empty
    bool returnCode = listCount > 0;

    if(returnCode) {
        //store value to be removed
        kv = keyValues[last];

        //adjust list size
        if(listCount > 1) {
            cListDec(last);
        }
        listCount--;
    }

    return returnCode;
}

 

void cKeyValueList::clear() {
    //set listCount to zero and reset first & last, emptying the list
    listCount = 0;
    first = 0;
    last = 0;
}

 

bool cKeyValueList::readAt(int index, KEY_VALUE &kv) const {
    //check if list is empty
    bool returnCode = listCount > 0;
    //check if provided index is valid
    returnCode = (index > -1) && (index < listCount);

    if(returnCode) {
        //convert index to physical and store the intended value
        index = virtualToPhysical(index);
        kv = keyValues[index];
    }

    return returnCode;
}

 

void cKeyValueList::printIt(int limit) const {
    // re adjust limit in case limit < 1 or limit > listCount
    if(limit > listCount || limit <= 0) {
        limit = listCount;
    }

    // print blanket statement
    cout << "Printing " << limit << " of " << listCount << " entries" << endl;

    // loop through list until limit and print each key
    for(int i = 0; i < limit; i++) {
        int actualIndex = virtualToPhysical(i);
        cout << "At index " << i << " there is (" << keyValues[actualIndex].key;
        cout << "," << keyValues[actualIndex].value << ")" << endl;
    }
}

 

void cKeyValueList::printItBackwards(int limit) const {
    // re adjust limit in case limit < 1 or limit > listCount
    if(limit > listCount || limit <= 0) {
        limit = listCount;
    }

    // print blanket statement
    cout << "Printing " << limit << " of " << listCount;
    cout << " entries backwards" << endl;

    // loop through list until limit and print each key
    for(int i = 1; i <= limit; i++) {
        int actualIndex = virtualToPhysical(listCount - i);
        cout << "At index " << listCount - i << " there is (";
        cout << keyValues[actualIndex].key << "," ;
        cout << keyValues[actualIndex].value << ")" << endl;
    }
}

 

int cKeyValueList::getIndex(int key) const {
    // initialize returnCode
    int returnCode = -1;

    // adjust the returnCode if value is found
    for(int i = 0; i < listCount; i++) {
        int actualIndex = virtualToPhysical(i);
        if(keyValues[actualIndex].key == key) {
            returnCode = i;
            break;
        }
    }

    return returnCode;
}

 

int cKeyValueList::getCapacity() const {
    return listCapacity;
}

 

int cKeyValueList::getCount() const {
    return listCount;
}