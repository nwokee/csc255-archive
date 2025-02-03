#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "graph.h"

using namespace std;


int main() {
    int action, unode, vnode, weight;
    bool rc;

    graph myGraph(40, true);

    while (cin >> action >> unode >> vnode >> weight) {
	if (vnode >= 0) {
	    // this is an edge record
	    if (action == 0) {
		rc = myGraph.addEdge(unode, vnode, weight);
		cout << "addEdge(" << unode << "," << vnode << "," << weight << ") returned: " << (rc?"True":"False") << endl;
	    } else {
		rc = myGraph.deleteEdge(unode, vnode);
		cout << "deleteEdge(" << unode << "," << vnode << ") returned: " << (rc?"True":"False") << endl;
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
}
