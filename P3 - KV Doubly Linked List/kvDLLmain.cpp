#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "kvDLL.h"

using namespace std;

//******************************************************************************

int myRand() {
    int v;
    while ((v = rand()) < 100);
    return (v % 1000);
}

//******************************************************************************

int main() {
    KEY_VALUE kv;
    int count;
    bool rc;

    kvDoublyLinkedList myL;
    kvDoublyLinkedList *myLa = new kvDoublyLinkedList();
    kvDoublyLinkedList *myLb = new kvDoublyLinkedList();

    srand(1);

    myL.printIt(-1);
    cout << "The size of the first list is " << myL.getCount() << endl << endl;

    for (kv.key = 0; kv.key < 10; kv.key++) {
	kv.value = myRand();
	cout << "insert of (" << kv.key << "," << kv.value << ") got ";
	cout << (myLa->insert(kv) ? "true" : "false") << endl;

	kv.value = -kv.value + 1;
	cout << "add of (" << kv.key << "," << kv.value << ") got ";
	cout << (myLa->add(kv) ? "true" : "false") << endl;
    }

    cout << endl;

    cout << "we have this number of entries " << myLa->getCount() << endl;
    myLa->printIt(-1);
    cout << endl;
    myLa->printItBackwards(-1);
    
    cout << endl;

    kv.key = 100;
    kv.value = myRand();
    cout << "insertAt(5, (" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insertAt(5, kv) ? "true" : "false") << "\n\n";

    kv.key = 111;
    kv.value = myRand();
    cout << "insertAt(15, (" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insertAt(15, kv) ? "true" : "false") << "\n\n";

    kv.key = 222;
    kv.value = myRand();
    cout << "insertAt(25, (" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insertAt(25, kv) ? "true" : "false") << "\n\n";

    kv.key = 333;
    kv.value = myRand();
    cout << "insert((" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->insert(kv) ? "true" : "false") << "\n\n";

    kv.key = 444;
    kv.value = myRand();
    cout << "add((" << kv.key << "," << kv.value <<") got ";
    cout << (myLa->add(kv) ? "true" : "false") << "\n\n";

    cout << "getIndex(7) returned " << myLa->getIndex(7) << "\n\n";
    cout << "getIndex(50) returned " << myLa->getIndex(50) << "\n\n";

    cout << "The list has this many entries " << myLa->getCount() << endl;
    cout << "The list has this capacity " << myLa->getCapacity() << endl << endl;

    kv.key = 123;
    kv.value = 123;
    rc = myLa->readAt(4, kv);
    cout << "readAt(4, key) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key << ","
	    << kv.value << "\n\n";

    kv.key = 456;
    kv.value = 456;
    rc = myLa->readAt(-10, kv);
    cout << "readAt(-10, key) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key << ","
	    << kv.value << "\n\n";

    kv.key = -777;
    kv.value = -777;
    rc = myLa->deleteAt(3, kv);
    cout << "deleteAt(3, kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    kv.key = -888;
    kv.value = -888;
    rc = myLa->deleteAt(33, kv);
    cout << "deleteAt(33, kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    myLa->printIt(-1);

    cout << endl;

    kv.key = -555;
    kv.value = -555;

    rc = myLa->deleteFirst(kv);
    cout << "deleteFirst(kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    kv.key = -666;
    kv.value = -666;

    rc = myLa->deleteLast(kv);
    cout << "deleteLast(kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";

    myLa->printIt(10);
    cout << endl;
    myLa->printItBackwards(10);

    count = myLa->getCount();

    for (int i = 0; i <= count; i++) {
        kv.key = -666;
        kv.value = -666;

        if (i % 2) {
            rc = myLa->deleteAt(0, kv);
            cout << "deleteAt(0, kv) got ";
        } else {
            rc = myLa->deleteFirst(kv);
            cout << "deleteFIrst(kv) got ";
        }
        cout << (rc ? "true" : "false") << " and (" << kv.key;
        cout << "," << kv.value << ")\n\n";
    }

    myLa->printIt(10);
    cout << endl;
    myLa->printItBackwards(10);


    //************************** WORKING WITH BLIST NOW
    
    cout << endl << "Working on the B list now." << endl << endl;
    kv.key = 100;
    kv.value = 1100;
    myLb->insertAt(0, kv);

    kv.key = -888;
    kv.value = -888;
    rc = myLb->deleteAt(0, kv);
    cout << "deleteAt(0, kv) got ";
    cout << (rc ? "true" : "false") << " and (" << kv.key;
    cout << "," << kv.value << ")\n\n";


    myLb->printIt(10);
    cout << endl;
    myLb->printItBackwards(10);

    for (kv.key = 0; kv.key < 40; kv.key++) {
	kv.value = kv.key + 1000;
	myLb->insertAt(0, kv);
    }

    myLb->printIt(10);
    cout << endl;
    myLb->printItBackwards(10);

    count = myLb->getCount();

    for (int i = 0; i < count; i++) {
	myLb->readAt(i, kv);
	if (kv.key != (count - i - 1)) {
	    cout << "readAt wrong answer with i = " << i << " kv.key = "
		    << kv.key << endl;
	    myLb->printIt(5);
	    myLb->printItBackwards(5);
	    break;
	}
    }

    for (int i = 0; i < count; i++) {
	myLb->deleteAt(0, kv);
	if (kv.key != (count - i - 1)) {
	    cout << "deleteAt wrong answer with i = " << i << " kv.key = "
		    << kv.key << endl;
	    myLb->printIt(5);
	    myLb->printItBackwards(5);
	    break;
	}
    }

    myLb->clear();


    for (kv.key = 0; kv.key < 1000; kv.key++) {
	kv.value = kv.key + 5000;
	myLb->insertAt(kv.key, kv);
    }

    cout << endl;

    myLb->printIt(5);
    cout << endl;
    myLb->printItBackwards(5);
    return 0;
}
