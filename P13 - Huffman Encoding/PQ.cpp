#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "PQ.h"

using namespace std;


keyValue::keyValue(int key, char value, keyValue *left, keyValue *right) {
	// initialize variables
	this->key = key;
	this->value = value;
	this->left = left;
	this->right = right;
}



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

    if (ind < qCount) {
	cout << "Level[" << (int)log2(ind + 1) << "]-> ";
	for (i = ind; i < (ind+count); i++) {
	    if (i == qCount) {
		break;
	    } else {
		cout << "(" << keys[i]->key << "," << keys[i]->value << ") ";
	    }
	}
	cout << endl;
	ind = left(ind);
	printIt(ind, 2*count);
    }
}



void PQ::swap(keyValue *&x, keyValue *&y) {
	keyValue *temp = x;
	x = y;
	y = temp;
}



void PQ::bubbleUp(int index) {
	// start if index is greater than 0
	if (index > 0) {
		// if the key at the index is less than its parent
		// swap and recurse upwards
		if (keys[index]->key < keys[parent(index)]->key) {
			swap(keys[index], keys[parent(index)]);
			bubbleUp(parent(index));
		}
	}
	
}



void PQ::heapify(int i) {
	// start if index is in bounds
	if (i < qCount) {
		// find the smallest value between the given index and its children
		// only if they exist
		int minIDX = i;
		if ((left(i) < qCount) && (keys[left(i)]->key < keys[minIDX]->key)) {
			minIDX = left(i);
		}
		if ((right(i) < qCount) && (keys[right(i)]->key < keys[minIDX]->key)) {
			minIDX = right(i);
		}

		// if minIDX got changed
		// swap the index with the child and recurse down
		if (minIDX != i) {
			swap(keys[minIDX], keys[i]);
			heapify(minIDX);
		}
	}
	
}



PQ::PQ(int n) {
	// initialize variables and allocate memory for queue
	qCount = 0;
	pqSize = n;
	keys = new keyValue*[n];
}



PQ::~PQ() {
	// free keys memory and delete the object
    if(keys) {
        delete [] keys;
        keys = NULL;
    }
}



bool PQ::enq(keyValue *kv) {
	// if queue isn't full, add new kv and bubble it up
	bool returnCode = (qCount < pqSize); 
	if (returnCode) {
		keyValue *x = new keyValue(kv->key, kv->value, kv->left, kv->right);
		keys[qCount] = x;
		bubbleUp(qCount);
		qCount++;
	}
	return returnCode;
}



bool PQ::deq(keyValue *&kv) {

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
