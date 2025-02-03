#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "thf.h"

using namespace std;


int
main() {
    int action, unode, vnode, weight;

    graph myD(40, true);
    graph myU(40, false);

    while (cin >> action >> unode >> vnode >> weight) {
	bool rc;

	if (vnode >= 0) {
	    // this is an edge record
	    if (action == 0) {
		rc = myU.addEdge(unode, vnode, weight);
		cout << "myU.addEdge(" << unode << "," << vnode << "," << weight << ") returned: " << (rc?"True":"False") << endl;
		rc = myD.addEdge(unode, vnode, weight);
		cout << "myD.addEdge(" << unode << "," << vnode << "," << weight << ") returned: " << (rc?"True":"False") << endl;
	    } else {
		rc = myU.deleteEdge(unode, vnode, weight);
		cout << "myD.deleteEdge(" << unode << "," << vnode << ") returned: " << (rc?"True":"False") << endl;
		rc = myD.deleteEdge(unode, vnode, weight);
		cout << "myD.deleteEdge(" << unode << "," << vnode << ") returned: " << (rc?"True":"False") << endl;
	    }
	} else {
	    // this is a node creation
	    if (action == 0) {
		rc = myU.createV(unode);
		//cout << "myU.createV(" << unode << ") returned: " << (rc?"True":"False") << endl;
		rc = myD.createV(unode);
		//cout << "myD.createV(" << unode << ") returned: " << (rc?"True":"False") << endl;
	    }
	}
    }
    cout << "************************ Printing myU\n";
    myU.printIt();
    myU.dumpAllPairsShortestPath();

    cout << endl << endl;

    cout << "************************ Printing myD\n";
    myD.printIt();
    myD.dumpAllPairsShortestPath();

    cout << endl << endl;
    cout << endl << endl;

    return 0;
}
