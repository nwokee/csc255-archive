#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "list.h"

using namespace std;

//******************************************************************************

int main() {
    int key;
    int count;
    bool rc;

    list myL;
    list *myLa = new list(22);
    list *myLb = new list(10000);

    myL.printIt(-1);
    cout << "The size of the first list is " << myL.getCount() << endl << endl;

    for (key = 0; key < 10; key++) {
	cout << "insert of " << key << " got ";
	cout << (myLa->insert(key) ? "true" : "false") << endl;

	cout << "add of " << key << " got ";
	cout << (myLa->add(key) ? "true" : "false") << endl;
    }

    cout << endl;

    cout << "we have this number of entries " << myLa->getCount() << endl;
    myLa->printIt(-1);
    cout << endl;
    myLa->printItBackwards(-1);
    
    cout << endl;

    cout << "insertAt(5, 100) got ";
    cout << (myLa->insertAt(5, 100) ? "true" : "false") << "\n\n";

    cout << "insertAt(15, 111) got ";
    cout << (myLa->insertAt(15, 111) ? "true" : "false") << "\n\n";

    cout << "insertAt(25, 222) got ";
    cout << (myLa->insertAt(25, 222) ? "true" : "false") << "\n\n";

    cout << "insert(333) got ";
    cout << (myLa->insert(333) ? "true" : "false") << "\n\n";

    cout << "add(444) got ";
    cout << (myLa->insert(444) ? "true" : "false") << "\n\n";

    cout << "getIndex(7) returned " << myLa->getIndex(7) << "\n\n";
    cout << "getIndex(50) returned " << myLa->getIndex(50) << "\n\n";

    key = 123;
    rc = myLa->readAt(4, key);
    cout << "readAt(4, key) got ";
    cout << (rc ? "true" : "false") << " and " << key << "\n\n";

    key = 456;
    rc = myLa->readAt(-10, key);
    cout << "readAt(-10, key) got ";
    cout << (rc ? "true" : "false") << " and " << key << "\n\n";

    key = -777;
    rc = myLa->deleteAt(3, key);
    cout << "deleteAt(3, key) got ";
    cout << (rc ? "true" : "false") << " and " << key << "\n\n";

    key = -888;
    rc = myLa->deleteAt(33, key);
    cout << "deleteAt(33, key) got ";
    cout << (rc ? "true" : "false") << " and " << key << "\n\n";

    myLa->printIt(-1);

    cout << endl;

    key = -555;

    rc = myLa->deleteFirst(key);
    cout << "deleteFirst(key) got ";
    cout << (rc ? "true" : "false") << " and " << key << endl << endl;

    key = -666;

    rc = myLa->deleteLast(key);
    cout << "deleteLast(key) got ";
    cout << (rc ? "true" : "false") << " and " << key << endl << endl;

    myLa->printIt(10);
    cout << endl;
    myLa->printItBackwards(10);

    count = myLa->getCount();

    for (int i = 0; i <= count; i++) {
	key = -i;
	if (i % 2) {
	    rc = myLa->deleteAt(0, key);
	    cout << "deleteAt(0, key) got ";
	} else {
	    rc = myLa->deleteFirst(key);
	    cout << "deleteFirst(key) got ";
	}
	cout << (rc ? "true" : "false") << " and " << key << endl;
    }

    myLa->printIt(10);
    cout << endl;
    myLa->printItBackwards(10);

    //************************** starting with BLIST now

    cout << endl << "Working on the B list now." << endl << endl;

    myLb->insertAt(0,100);

    key = -888;
    rc = myLb->deleteAt(0, key);
    cout << "deleteAt(0, key) got ";
    cout << (rc ? "true" : "false") << " and " << key << endl;

    myLb->printIt(10);
    cout << endl;
    myLb->printItBackwards(10);

    for (int key = 0; key < 40; key++) {
	myLb->insertAt(0, key);
    }

    myLb->printIt(10);
    cout << endl;
    myLb->printItBackwards(10);

    count = myLb->getCount();

    for (int i = 0; i < count; i++) {
	myLb->readAt(i, key);
	if (key != (count - i - 1)) {
	    cout << "readAt wrong answer with i = " << i << " key = "
		    << key << endl;
	    myLb->printIt(5);
	    myLb->printItBackwards(5);
	    break;
	}
    }

    for (int i = 0; i < count; i++) {
	myLb->deleteAt(0, key);
	if (key != (count - i - 1)) {
	    cout << "deleteAt wrong answer with i = " << i << " key = "
		    << key << endl;
	    myLb->printIt(5);
	    myLb->printItBackwards(5);
	    break;
	}
    }

    myLb->clear();


    for (key = 0; key < 1000; key++) {
	myLb->insertAt(key, key + 5000);
    }

    cout << endl;

    myLb->printIt(5);
    cout << endl;
    myLb->printItBackwards(5);

    return 0;
}
