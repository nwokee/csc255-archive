#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "list.h"

using namespace std;

 

list::list(int capacity) {
    // initialize variables
    listCapacity = capacity;
    listCount = 0;
    keys = new int[capacity];
}


 

list::~list() {
    // delete the keys object
    if (keys) {
        delete [] keys;
        keys = NULL;
    }
}

 

bool list::insert(int key) {
    // check if list is full
    bool returnCode = listCount < listCapacity;

    if (returnCode) {
        // shift all items in list down one spot
        for (int i = listCount; i > 0; i--) {
            keys[i] = keys[i-1];
        }

        // insert key at the start of list and increase list size
        keys[0] = key;
        listCount++;
    }

    return returnCode;
}

 

bool list::add(int key) {
    // check if list is full
    bool returnCode = listCount < listCapacity;

    if (returnCode) {
        // append key to the end of the list and increase list size
        keys[listCount] = key;
        listCount++;
    }

    return returnCode;
}

 

bool list::insertAt(int index, int key) {
    // check if list is full and if index is in bounds
    bool returnCode = (listCount < listCapacity);
    returnCode = returnCode && (index > -1) && (index <= listCount);

    if (returnCode) {
        // shift all items ahead of index down one spot
        for (int i = listCount; i > index; i--) {
            keys[i] = keys[i-1];
        }

        // insert key at the index and increase list size
        keys[index] = key;
        listCount++;
    }

    return returnCode;
}

 

bool list::deleteAt(int index, int &key) {
    // check if list is empty and if index is in bounds
    bool returnCode = (listCount > 0) && (index > -1) && (index < listCount);

    if (returnCode) {
        // store value to be removed
        key = keys[index];

        // shift every element before index up one and adjust list size
        for (int i = index + 1; i < listCount; i++) {
            keys[i-1] = keys[i];
        }

        listCount--;
    }

    return returnCode;
}

 

bool list::deleteFirst(int &key) {
    // check if list is empty
    bool returnCode = listCount > 0;

    if (returnCode) {
        // store value to be removed
        key = keys[0];

        // shift every element up one and adjust list size
        for (int i = 1; i < listCount; i++) {
            keys[i-1] = keys[i];
        }

        listCount--;
    }

    return returnCode;
}

 

bool list::deleteLast(int &key) {
    // check if list is empty
    bool returnCode = listCount > 0;

    if (returnCode) {
        // store value to be removed
        key = keys[listCount - 1];

        // adjust list size
        listCount--;
    }

    return returnCode;
}

 

void list::clear() {
    // set listCount to zero, emptying the list
    listCount = 0;
}

 

bool list::readAt(int index, int &key) const {
    // check if list is empty and index is valid
    bool returnCode = (listCount > 0) && (index > -1) && (index < listCount);

    if (returnCode) {
        // store the intended value
        key = keys[index];
    }

    return returnCode;
}

 

void list::printIt(int limit) const {
    // re adjust limit in case limit < 1 or limit > listCount
    if (limit > listCount || limit < 1) {
        limit = listCount;
    }

    // print blanket statement
    cout << "Printing " << limit << " of " << listCount << " entries" << endl;

    // loop through list until limit and print each key
    for (int i = 0; i < limit; i++) {
        cout << "At index " << i << " there is key " << keys[i] << endl;
    }
}

 

void list::printItBackwards(int limit) const {
    // re adjust limit in case limit < 1 or limit > listCount
    if (limit > listCount || limit < 1) {
        limit = listCount;
    }

    // print blanket statement
    cout << "Printing " << limit << " of ";
    cout << listCount << " entries backwards" << endl;

    // loop through list until limit and print each key
    for (int i = 1; i <= limit; i++) {
        cout << "At index " << listCount - i << " there is key ";
        cout << keys[listCount - i] << endl;
    }

}

 

int list::getIndex(int key) const {
    // initialize returnCode
    int returnCode = -1;

    // adjust the returnCode if value is found
    for (int i = 0; i < listCount; i++) {
        if (keys[i] == key) {
            returnCode = i;
            break;
        }
    }

    return returnCode;
}

 

int list::getCapacity() const {
    return listCapacity;
}

 

int list::getCount() const {
    return listCount;
}

 

void list::bubbleSort() {
    // go through list, swapping items one by one 
    // until the list is fully sorted
    for (int i = listCount - 1; i > 0; i --) {
        for (int j = 0; j < i; j ++) {
            if (keys[j] > keys[j + 1]) {
                // keys are out of order, swap them
                int temp = keys[j];
                keys[j] = keys[j+1];
                keys[j+1] = temp;
            }
        }
    }
}

 

void list::selectionSort() {
    for (int i = 0; i < listCount - 1; i++) {
        // look for the index of the smallest key in the list
        int minIndex = i;
        for (int j = i; j < listCount; j++) {
            if (keys[j] < keys[minIndex]) {
                minIndex = j;
            }
        }
        // swap the smallest key at the current date line
        int temp = keys[i];
        keys[i] = keys[minIndex];
        keys[minIndex] = temp;
    }
}

 

void list::insertionSort() {
    for (int i = 1; i < listCount; i++) {
        // store key to be inserted and 
        // find where exactly it should be placed
        int save = keys[i];
        int j = i;
        for (j = i; j > 0; j--) {
            if (keys[j - 1] > save) {
                // key to be inserted is smaller, shift and keep moving
                keys[j] = keys[j-1];
            } else {
                // key needs to be inserted here, exit the loop
                break;
            }
        }
        // store saved key where it belongs
        keys[j] = save;
    }
}

 

bool list::isSorted() {
    bool returnCode = true;
    // loop through list to see if it is sorted
    // print out where it fails (if it does)
    for (int i = 0; i < listCount - 1; i++) {
        if (keys[i] > keys[i + 1]) {
            cout << "Failed at index " << i << endl;
            returnCode = false;
            break;
        }
    }

    return returnCode;
}