#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "PQ.h"

using namespace std;

//******************************************************************************

void part1(PQ &myPQ) {
    bool rc;
    KEY_VALUE kv;

    //srand(time(NULL));
    srand(0);

    for (kv.value = 0; kv.value < 100; kv.value++) {
	kv.key = rand() % 1000;
	myPQ.enq(kv);
    }

    cout << "Tree count is " << myPQ.count() << endl;
    cout << "Tree contents are: \n";

    myPQ.printIt();


    for (int i = 0; i < 10; i++) {
	rc = myPQ.deq(kv);
	cout << i << ": deq got " << "(" << kv.key << "," << kv.value;
	cout  << ") and " << (rc ? "TRUE" : "FALSE") << endl;
    }

    myPQ.clear();
    cout << "Tree count is now " << myPQ.count() << endl;
}

//******************************************************************************

void part2(PQ &myPQ) {
    KEY_VALUE kv;

    //srand(time(NULL));
    srand(0);

    for (kv.value = 0; kv.value < 10; kv.value++) {
	kv.key = rand() % 1000;
	myPQ.enq(kv);
    }

    cout << "Tree count is " << myPQ.count() << endl;
    cout << "Tree contents are: \n";

    myPQ.printIt();


    for (int i = 0; myPQ.deq(kv); i++) {
	cout << i << ": deq got " << "(" << kv.key << "," << kv.value << ")"
	    << endl;
    }

    myPQ.clear();
}

//******************************************************************************

int main() {
    PQ myPQ(200);

    part1(myPQ);
    part2(myPQ);
    cout << "all done \n";
}
