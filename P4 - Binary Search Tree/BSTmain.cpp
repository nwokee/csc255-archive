#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

//******************************************************************************

void doWork(BST &myTree) {
    KEY_VALUE kv;
    int deleteCount;

    cout << "Do Work - START ********************\n";

    while (cin >> kv.key && cin >> kv.value) {
	if (!myTree.insert(kv)) {
	    cout << "Key not inserted:  " << kv.key << endl;
	}
    }
    
    cout << "Tree count is " << myTree.count() << endl;
    cout << "Tree contents are: \n";
    myTree.printIt();

    deleteCount = 0;
    for (int key = 25; key >=0; key--) {
	if (myTree.remove(key)) {
	    deleteCount++;
	}
    }


    cout << "\nDelete Count is " << deleteCount << endl;
    cout << "Tree count is " << myTree.count() << endl;
    cout << "Tree contents are: \n";
    myTree.printIt();

    cout << endl;

    for (int key = 0; key < 100; key += 2) {
	int value;
	if (myTree.getValue(key, value)) {
	    cout << "getValue reports this is in the list: (";
	    cout << key << "," << value << ")" << endl;
	}
    }


    myTree.clear();

    cout << "\nThe cleared tree status:  count = " << myTree.count() <<endl;
    cout << "The cleared tree contents follow:\n";
    myTree.printIt();

    cout << "Do Work - END   ********************\n";
}

//******************************************************************************

int main() {
    BST theTree;

    doWork(theTree);

    return 0;
}
