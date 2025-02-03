#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "AVL.h"

using namespace std;
int const NCOUNT = 1000000;
long const TenThousand = 10000;
long const OneMillion = 1000000;
long const OneBillion = OneMillion * 1000L;

//******************************************************************************

int myRand() {
    int v;
    while ((v = rand()) < 100);
    return (v % 1000);
}

//******************************************************************************

double getElapsedTime(timespec start, timespec end) {
    // returns number of ms
    unsigned long long diff;
    diff = OneBillion * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    return(((double) diff)/1000000.0);
}

//***********************************************************************

void doWork1(AVL &tree) {
    int key, value;
    KEY_VALUE kv;
    int removeCount;

    cout << "Do Work #1 - START ********************\n";

    while (cin >> kv.key && cin >> kv.value) {
	if (!tree.insert(kv)) {
	    cout << "Key not inserted:  " << kv.key << endl;
	}
    }
    
    cout << "Tree count is " << tree.count() << endl;
    cout << "Tree contents are: \n";
    tree.printIt();

    removeCount = 0;
    for (key = 25; key >=0; key--) {
	if (tree.remove(key)) {
	    removeCount++;
	}
    }


    cout << "\nRemove Count is " << removeCount << endl;
    cout << "Tree count is " << tree.count() << endl;
    cout << "Tree contents are: \n";
    tree.printIt();

    cout << endl;

    for (key = 0; key < 100; key += 2) {
	value = -8888;
	if (tree.getValue(key, value)) {
	    cout << "getValue for key " << key;
	    cout << " reports this value is in the tree: " << value << endl;
	}
    }


    tree.clear();

    cout << "\nThe cleared tree status:  count = " << tree.count() <<endl;
    cout << "The cleared tree contents follow:\n";
    tree.printIt();

    cout << "Do Work #1 - END   ********************\n";
}

//***********************************************************************

void doWork2(AVL &tree) {
    int i, j;
    int key, value;
    KEY_VALUE kv;

    struct timespec tStart, tStop;


    cout << "Do Work #2 - START   ********************\n";
    for (j = 0; j < 2; j++) {
	//
	// TIMING INSERTION
	//
	clock_gettime(CLOCK_MONOTONIC, &tStart);

	if (j == 0) {
	    // First time, do random values
	    //srand(time(NULL));
	    srand(1); // seed so we get the same random numbers for each iteration of j
	    for (i = 0; i < NCOUNT; i++) {
		kv.key = rand() % OneMillion;
		tree.insert(kv);
	    }
	} else {
	    // Second time, do ascending values
	    for (kv.key = 0; kv.key < TenThousand; kv.key++) {
		tree.insert(kv);
	    }
	}

	clock_gettime(CLOCK_MONOTONIC, &tStop);

	cout << "Tree(" << j << ") took " << getElapsedTime(tStart,tStop) << " ms to insert.\n";
	
	//
	// TIMING isIn
	//
	clock_gettime(CLOCK_MONOTONIC, &tStart);
	//srand(time(NULL));
	srand(1); // seed so we get the same random numbers for each iteration of j

	for (i = 0; i < NCOUNT; i++) {
	    key = rand() % OneMillion;
	    tree.getValue(key, value);
	}

	clock_gettime(CLOCK_MONOTONIC, &tStop);

	cout << "Tree(" << j << ") took " << getElapsedTime(tStart,tStop) << " ms to do isIn().\n";

	tree.clear();
    }

    cout << "Do Work #2 - END   ********************\n";
}

//***********************************************************************

//***********************************************************************

int main(int argc, char *argv[]) {
    bool doBal;
    bool go = true;

    if (argc == 2) {
	if (*argv[1] == '0') {
	    doBal = false;
	} else if (*argv[1] == '1') {
	    doBal = true;
	} else {
	    go = false;
	}
	if (go) {
	    AVL myTree(doBal);
	    doWork1(myTree);
	    myTree.clear();
	    doWork2(myTree);
	}
    } else {
	cerr << "Usage: " << argv[0] << " 0 or 1 for doBal" << endl;
    }

    return 0;
}
