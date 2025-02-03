#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "AVL.h"

using namespace std;

//******************************************************************************

int main() {

    AVL myTree(true);

    int key, value;
    KEY_VALUE kv;

    while (cin >> kv.key && cin >> kv.value) {
	if (!myTree.insert(kv)) {
	    cout << "Key not inserted:  " << kv.key << endl;
	}
    }
    
    cout << "Tree count is " << myTree.count() << endl;
    cout << "Tree contents are: \n";
    myTree.printIt();

    for (int i = -2; i < myTree.count() + 3;  i++) {
	if (myTree.getKeyAtRank(i, key)) {
	    cout << "The key at rank " << i << " is " << key << endl;
	    if (myTree.getValue(key, value)) {
		cout << "  And the value is " << value << endl;
	    } else {
		cout << "Failed to get value at key " << key << endl;
	    }
	} else {
	    cout << "There is no key at rank " << i << endl;
	}
    }


    return 0;
}
