#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "PQ.h"

using namespace std;

 

int PQ::parent(int index) const {
	// subtract 1 divide by 2 to get parent
	return (index - 1) / 2;
}

 

int PQ::left(int index) const {
	// multiply by 2 add 1 to get left child
	return (index * 2) + 1;
}

 

int PQ::right(int index) const {
	// multiply by 2 add 2 to get right child
	return (index * 2) + 2;
}

 

void PQ::printIt(int ind, int count) const {
    int i;

	// check if we're past qCount
    if (ind < qCount) {
		// print the level we're in
		cout << "Level[" << (int)log2(ind + 1) << "]-> ";
		for (i = ind; i < (ind+count); i++) {
			// if we're still in bounds print the next key 
			if (i == qCount) {
				break;
			} else {
				cout << "(" << keys[i].key << "," << keys[i].value << ") ";
			}
		}
		cout << endl;
		// move down to the next level and recursively print it
		ind = left(ind);
		printIt(ind, 2*count);
    }
}

 

void PQ::swap(KEY_VALUE *x, KEY_VALUE *y) {
	KEY_VALUE temp;
	temp.key = x->key;
	temp.value = x->value;

	x->key = y->key;
	x->value = y->value;

	y->key = temp.key;
	y->value = temp.value;
}

 

void PQ::bubbleUp(int index) {
	// start if index is greater than 0
	if (index > 0) {
		// if the key at the index is greater than its parent
		// swap and recurse upwards
		if (keys[index].key > keys[parent(index)].key) {
			swap(&keys[index], &keys[parent(index)]);
			bubbleUp(parent(index));
		}
	}
	
}

 

void PQ::heapify(int i) {
	// start if index is in bounds
	if (i < qCount) {
		// find the greatest value between the given index and its children
		// only if they exist
		int maxIDX = i;
		if ((left(i) < qCount) && (keys[left(i)].key > keys[maxIDX].key)) {
			maxIDX = left(i);
		}
		if ((right(i) < qCount) && (keys[right(i)].key > keys[maxIDX].key)) {
			maxIDX = right(i);
		}

		// if maxIDX got changed
		// swap the index with the child and recurse down
		if (maxIDX != i) {
			swap(&keys[maxIDX], &keys[i]);
			heapify(maxIDX);
		}
	}
	
}

 

PQ::PQ(int n) {
	// initialize variables and allocate memory for queue
	qCount = 0;
	pqSize = n;
	keys = new KEY_VALUE[n]; 
}

 

PQ::~PQ() {
	// free keys memory and delete the object
    if(keys) {
        delete [] keys;
        keys = NULL;
    }
}

 

bool PQ::enq(KEY_VALUE kv) {
	// if queue isn't full, add new kv and bubble it up
	bool returnCode = (qCount < pqSize); 
	if (returnCode) {
		keys[qCount] = kv;
		bubbleUp(qCount);
		qCount++;
	}
	return returnCode;
}

 

bool PQ::deq(KEY_VALUE &kv) {
	// check if list is empty
	bool returnCode = (qCount > 0); 
	if (returnCode) {
		// store highest priority key value into kv
		kv = keys[0];
		
		// put last kv at the beginning, heapify it down and lower qCount
		keys[0] = keys[qCount - 1];
		heapify(0);
		qCount--;
	}

	return returnCode;
}

 

void PQ::printIt() const {
    printIt(0, 1);
}

 

void PQ::clear() {
	// reset all variables
	qCount = 0;
}

 

int PQ::count() const {
	return qCount;
}