#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "graph.h"

using namespace std;


main(int argc, char *argv[]) {
    int action, unode, vnode, weight;
    bool rc;
    int tf;

    if ((argc < 2) || (sscanf(argv[1], "%d", &tf) != 1) || ((tf != 0) && (tf != 1))) {
	cerr << "Run " << argv[0] << " with a parameter of 0 for false, 1 for true.\n";
	exit(1);
    }

    graph myGraph(40, (bool)tf);

    while (cin >> action >> unode >> vnode >> weight) {
	rc = false;
	if (vnode >= 0) {
	    // this is an edge record
	    if (action == 0) {
		rc = myGraph.addEdge(unode, vnode, weight);
		cout << "addEdge(" << unode << "," << vnode << "," << weight << ") returned: " << (rc?"True":"False") << endl;
	    } else {
		rc = myGraph.deleteEdge(unode, vnode, weight);
		cout << "deleteEdge(" << unode << "," << vnode << ") returned: " << (rc?"True":"False");
		cout << " with edge weight of " << weight << endl;
	    }
	} else {
	    // this is a node creation
	    if (action == 0) {
		rc = myGraph.createV(unode);
		cout << "createV(" << unode << ") returned: " << (rc?"True":"False") << endl;
	    }
	}
    }

    myGraph.printIt();
    myGraph.printAllPaths();

    cout << "*** start of isCyclic output\n";
    cout << "    The graph is " << (myGraph.isCyclic()?"cyclic":"acyclic") << endl;
    cout << "*** end of isCyclic output\n";
}
