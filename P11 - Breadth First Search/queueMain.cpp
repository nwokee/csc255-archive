#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "queue.h"

using namespace std;

int main() {
    int i;
    bool rc;
    int v;
    queue myQ(10);

    for (i = 0; i < 12; i++) {
	cout << "Enq of " << i << " got: " << (myQ.enq(i) ? "true" : "false") << endl;
    }

    cout << "Q size is " << myQ.count() << endl;
    myQ.printIt();

    for (i = 0; i < 5; i++) {
	rc = myQ.deq(v);
	cout << "Deq got " << (rc ? "true" : "false") << " and v = " << v << endl;
    }

    cout << "Enq of " << 24 << " got: " << (myQ.enq(24) ? "true" : "false") << endl;

    cout << "Q size is " << myQ.count() << endl;
    myQ.printIt();

    for (i = 0; i < 5; i++) {
	rc = myQ.deq(v);
	cout << "Deq got " << (rc ? "true" : "false") << " and v = " << v << endl;
    }

    cout << "Q size is " << myQ.count() << endl;
    myQ.printIt();

    for (i = 0; i < 2; i++) {
	rc = myQ.deq(v);
	cout << "Deq got " << (rc ? "true" : "false") << " and v = " << v << endl;
    }

    cout << "Q size is " << myQ.count() << endl;
    myQ.printIt();

}
