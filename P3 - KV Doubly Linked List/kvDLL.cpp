#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "kvDLL.h"

using namespace std;


 
node::node(KEY_VALUE kv, node* next, node* prev) {
    // Initialize variables
    this->kv = kv;
    this->next = next;
    this->prev = prev;
}

 

int kvDoublyLinkedList::getIndex(int key, node* pn, int index) const {
    // initialize return code
    int returnCode = -1;

    // compare node to key if node exists
    if (pn) {
        if (pn->kv.key == key) {
            returnCode = index;
        } else {
            // recursive step if node exists, but the keys aren't equal
            returnCode = getIndex(key, pn->next, index + 1);
        }
    }

    return returnCode;
}

 

void kvDoublyLinkedList::printIt(node* pn, int index, int limit) const {
    // Only print out statement if the node exists and limit > 0
    // otherwise there is nothing to do
    if (pn && limit) {
        // print the current node
        cout << "At index " << index++ << " there is (" << pn->kv.key << ",";
        cout << pn->kv.value << ")" << endl;

        // adjust the limit bc we just printed a node
        // then call to print the next node using recursion
        limit--;
        printIt(pn->next, index, limit);
    }
}

 

void kvDoublyLinkedList::printItBackwards(node* pn, int index, int limit) const {
    // Only print out statement if the node exists and limit > 0
    // otherwise there is nothing to do
    if (pn && limit) {
        // print the current node
        cout << "At index " << index-- << " there is (" << pn->kv.key << ",";
        cout << pn->kv.value << ")" << endl;

        // adjust the limit bc we just printed a node
        // then call to print the previous node using recursion
        limit--;
        printItBackwards(pn->prev, index, limit);
    }
    
}

 

void kvDoublyLinkedList::clear(node *pn) {
    // if node exists, clear the next node and delete itself
    if (pn) {
        clear(pn->next);
        delete pn;
    }
}

 

kvDoublyLinkedList::kvDoublyLinkedList() {
    // initialize variables
    first = NULL;
    last = NULL;
    nCount = 0;
}

 

kvDoublyLinkedList::~kvDoublyLinkedList() {
    // because we dont pre allocate anything, use the clear method
    // to manually clear all the nodes
    clear();

}

 

bool kvDoublyLinkedList::insert(KEY_VALUE kv) {
    //create node
    first = new node(kv, first, NULL);

    // if list was empty, set last to first
    // otherwise just adjust what the next node points to
    if (nCount) {
        first->next->prev = first;
    } else {
        last = first;
    }

    //increase list size and return true
    nCount++;
    return true;
}

 

bool kvDoublyLinkedList::add(KEY_VALUE kv) {
    //create node
    last = new node(kv, NULL, last);

    // if list is empty, set first to last
    // otherwise just adjust what the previous node points to
    if (nCount) {
        last->prev->next = last;
    } else {
        first = last;
    }

    //increase list size and return true
    nCount++;
    return true;
}

 

bool kvDoublyLinkedList::insertAt(int index, KEY_VALUE kv) {
    //check if provided index is valid
    bool returnCode = (index > -1) && (index <= nCount);
    
    if (returnCode) {
        // if list is empty make a new node and set it to first and last
        // or if we're adding it to the end of the list, adjust last
        // otherwise find where to add the node
        if (!nCount) {
            first = new node(kv, NULL, NULL);
            last = first;
        } else if (index == nCount) {
            //append node to the end
            last = new node(kv, NULL, last);
            last->prev->next = last;
        } else {
            //loop through list until index and create new node
            node *temp = first;
            for (int i = index; i > 0; i--) {
                temp = temp->next;
            }
            node *toAdd = new node(kv,temp,temp->prev);

        
            //if we're not at the start of the list update the previous node
            if (temp->prev) {
                temp->prev->next = toAdd;
            } else {
                first = toAdd;
            }
            temp->prev = toAdd;
        }

        nCount++;
    }

    return returnCode;

}

 

bool kvDoublyLinkedList::deleteAt(int index, KEY_VALUE& kv) {
    // check if list is empty and if provided index is valid
    bool returnCode = (nCount > 0) && (index > -1) && (index < nCount);
    
    if(returnCode) {
        // get to the node we're deleting
        node *toDelete = first;
        int i = 0;
        while (i != index) {
            toDelete = toDelete->next;
            i++;
        }

        // if we're not deleting the first node update the prev node
        if (toDelete->prev) {
            // wasn't first node
            toDelete->prev->next = toDelete->next;
        } else {
            // was first node
            first = toDelete->next;
        }

        // if we're not deleting the last node update the next node
        if (toDelete->next) {
            // wasn't last node
            toDelete->next->prev = toDelete->prev;
        } else {
            // was last node
            last = toDelete->prev;
        }

        //store deleted value, delete node, and update nCount
        kv = toDelete->kv;
        delete toDelete;
        nCount--;


    }

    return returnCode;
}

 

bool kvDoublyLinkedList::deleteFirst(KEY_VALUE& kv) {
    // Check if the list is empty
    bool returnCode = nCount > 0;

    if (returnCode) {
        // store node to be deleted
        kv = first->kv;
        node *toDelete = first;

        // adjust first and if list had more that one element
        // set new first node, otherwise adjust last
        first = first->next;
        if (first) {
            first->prev = NULL;
        } else {
            last = NULL;
        }

        // delete the removed node and adjust nCount
        delete toDelete;
        nCount--;
    }

    return returnCode;
}

 

bool kvDoublyLinkedList::deleteLast(KEY_VALUE& kv) {
    // Check if the list is empty
    bool returnCode = nCount > 0;

    if (returnCode) {
        // store node to be deleted
        kv = last->kv;
        node *toDelete = last;

        // adjust last and if list had more that one element
        // set new last node, otherwise adjust first
        last = last->prev;
        if (last) {
            last->next = NULL;
        } else {
            first = NULL;
        }

        // delete the removed node and adjsut nCount
        delete toDelete;
        nCount--;
    }

    return returnCode;
}

 

void kvDoublyLinkedList::clear() {
    // start recursion with last node
    clear(first);

    //reset all variables
    first = NULL;
    last = NULL;
    nCount = 0;
}

 

bool kvDoublyLinkedList::readAt(int index, KEY_VALUE& kv) const {
    //check if provided index is valid
    bool returnCode = (index > -1) && (index < nCount);

    if (returnCode) {
        //loop through list until index and store the kv
        node *temp = first;
        for (int i = index; i > 0; i--) {
            temp = temp->next;
        }
        kv = temp->kv;
    }

    return returnCode;

}

 

int kvDoublyLinkedList::getIndex(int key) const {
    // Start the search from the first node with index 0
    return getIndex(key, first, 0);
}

 

void kvDoublyLinkedList::printIt(int limit) const {
    // re adjust limit in case limit < 1 or limit > nCount
    if (limit > nCount || limit <= 0) {
        limit = nCount;
    }

    // print blanket statement
    cout << "Printing " << limit << " of " << nCount;
    cout << " entries" << endl;

    // start printing recursion
    printIt(first, 0, limit);
}

 

void kvDoublyLinkedList::printItBackwards(int limit) const {
    // re adjust limit in case limit < 1 or limit > nCount
    if (limit > nCount || limit <= 0) {
        limit = nCount;
    }

    // print blanket statement
    cout << "Printing " << limit << " of " << nCount;
    cout << " entries backwards" << endl;

    // start printing recursion
    printItBackwards(last, nCount - 1, limit);
}

 

int kvDoublyLinkedList::getCount() const {
    return nCount;
}

 

int kvDoublyLinkedList::getCapacity() const {
    return -1;
}