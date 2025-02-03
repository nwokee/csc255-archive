#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "graph.h"

using namespace std;


int main() {
    int action, uLabel, vLabel, weight;
    bool rc;

    graph myGraph(40, true);

    while (cin >> action >> uLabel >> vLabel >> weight) {
	if (vLabel >= 0) {
	    // this is an edge record
	    if (action == 0) {
		rc = myGraph.addEdge(uLabel, vLabel, weight);
		cout << "addEdge(" << uLabel << "," << vLabel << "," << weight << ") returned: " << (rc?"True":"False") << endl;
	    } else {
		rc = myGraph.deleteEdge(uLabel, vLabel);
		cout << "deleteEdge(" << uLabel << "," << vLabel << ") returned: " << (rc?"True":"False") << endl;
	    }
	    cout << "The weight of (" << uLabel << ", " << vLabel << ") is " << myGraph.getEdgeWeight(uLabel, vLabel) << endl;
	} else {
	    // this is a node creation
	    if (action == 0) {
		rc = myGraph.createV(uLabel);
		cout << "createV(" << uLabel << ") returned: " << (rc?"True":"False") << endl;
	    }
	}
    }
    uLabel = 15;
    vLabel = 100;
    cout << "The weight of (" << uLabel << ", " << vLabel << ") is " << myGraph.getEdgeWeight(uLabel, vLabel) << endl;
    myGraph.printIt();
    myGraph.printAllPaths();
}
