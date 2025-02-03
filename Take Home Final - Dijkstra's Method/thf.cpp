#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "thf.h"

using namespace std;



int graph::min(int x, int y) const {
    // returns the minimum value of x and y
    int returnCode = (x < y) ? x : y;
    return returnCode;
}



int graph::max(int x, int y) const {
    // returns the maximum value of x and y
    int returnCode = (x > y) ? x : y;
    return returnCode;
}



int graph::vidToLabel(int vid) const {
    // setup returnCode
    int returnCode = -1;

    // if vid is valid, get its label from vList
    if (vid >= 0 && vid < vCount) {
        returnCode = vertexList[vid].label;
    }
    return returnCode;
}



int graph::labelToVid(int label) const {
    // setup returnCode
    int returnCode = -1;

    // look through vList for a vid with the same label
    for (int i = 0; i < vCount; i++) {
        if (label == vertexList[i].label) {
            returnCode = i;
            break;
        }
    }
    return returnCode;
}



bool graph::isEdge(int uLabel, int vLabel) const {
    bool returnCode = false;
    //check if it is a valid node
    if (isV(uLabel) && isV(vLabel)){
        int uID = labelToVid(uLabel);
        int vID = labelToVid(vLabel);

        //check if there is an edge weight in adjacency matrix
        returnCode = (a[uID][vID] != 0);
    }

    return returnCode;
}



bool graph::isV(int label) const {
    // use labelToVid to see if label exists in the vList
    bool returnCode = (labelToVid(label) != -1) ? true : false;
    return returnCode;
}



void graph::printPath(int uVid, int vVid) const {
    if (uVid == vVid) {
        // we were able to make it back to the starter vertex, start the
        // printing process
        cout <<  vidToLabel(uVid) << " ";
    } else if (vertexList[vVid].predVID == vidNIL) {
        // we hit a dead end traversing backwards, meaning no path exists
        cout << "No path from " << vidToLabel(uVid);
        cout << " to " << vidToLabel(vVid) << " exists." <<endl;
    } else {
        // traverse back a vertex and see if the path ends there
        printPath(uVid, vertexList[vVid].predVID);
        cout <<  vidToLabel(vVid) << " ";
    }
}



void graph::bfs(int uVid) {
    // reset all the colors, distances, and predVIDs of every vertex
    for (int i = 0; i < vCount; i++) {
        vertexList[i].color = WHITE;
        vertexList[i].distance = INFINITE;
        vertexList[i].predVID = vidNIL;
    }

    // set the head leading node to the right color, dist, and predVID
    vertexList[uVid].color = WHITE;
    vertexList[uVid].distance = 0;
    vertexList[uVid].predVID = vidNIL;

    // make queue for BFS
    q->clear();
    q->enq(uVid);

    while (q->count() != 0) {
        int u;
        q->deq(u);

        for (int i = 0; i < vCount; i++) {
            // look for adjacent values to q and 
            // see if they've been discovered
            if (a[u][i] != 0 && vertexList[i].color == WHITE) {
                // set undiscovered adjacent vertices to discovered
                // and update their height and previous vertex
                vertexList[i].color = GRAY;
                vertexList[i].distance = vertexList[u].distance + 1;
                vertexList[i].predVID = u;
                
                // add found vertex to the queue to re-search
                // in the next round
                q->enq(i);
            }
        }

        // u has been fully used at this point, so we can move past it
        vertexList[u].color = BLACK;
    }

}



void graph::dfs(int uVid, int &timestamp) {
    // set starting time for the specific vertex
    timestamp++;
    vertexList[uVid].startTime = timestamp;
    vertexList[uVid].color = GRAY;

    // run dfs through all adjacent vertices
    for (int i = 0; i < vCount; i++) {
        // check if vertex is unvisited and an edge exists 
        // (nested if to fit the line character limit of 81)
        if (isEdge(vidToLabel(uVid), vidToLabel(i))) {
            if (vertexList[i].color == WHITE) {
                vertexList[i].predVID = uVid;
                dfs(i,timestamp);
            }
        }
    }

    // set finish time and end dfs for the vertex
    timestamp++;
    vertexList[uVid].finishTime = timestamp;
    vertexList[uVid].color = BLACK;
}



void graph::dfs(int vVid) {
    // reset all the vertices before starting dfs
    for (int i = 0; i < vCount; i++) {
        vertexList[i].color = WHITE;
        vertexList[i].predVID = vidNIL;
    }

    // start dfs timer and start dfs with the given vertex
    int time = 0;
    dfs(vVid,time);
}



bool graph::isCyclicDirected() {
    // use cycleFound as returnCode
    cycleFound = false;

    for (int i = 0; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            // check if edge exists but also if there
            // is a path back to the starting node
            if (isEdge(vidToLabel(i),vidToLabel(j)) && isPath(j,i)) {
                // path found, graph is cyclic, stop checking
                cycleFound = true;
                break;
            }
        }
        if (cycleFound) {
            // found a cycle, stop checking
            break;
        }
    }

    return cycleFound;
}



bool graph::isCyclicUndirected() {
    // use cycleFound as returnCode
    cycleFound = false;

    for (int i = 0; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            // check if edge between the two exists
            if (isEdge(vidToLabel(i),vidToLabel(j))) {
                // delete edge and check if there is 
                // still a path back to the starting vertex
                int w;
                deleteEdge(vidToLabel(i),vidToLabel(j), w);
                if (isPath(j,i)) {
                    // path found, graph is cyclic
                    cycleFound = true;
                }
                addEdge(vidToLabel(i),vidToLabel(j), w);
                if (cycleFound) {
                    // found a cycle, stop checking
                    break;
                }
            }
        }
        if (cycleFound) {
            // found a cycle, stop checking
            break;
        }
    }

    return cycleFound;
}



bool graph::isPath(int uVid, int vVid) {
    // do bfs with starting vertex and return true if ending vertex was reached
    bfs(uVid);
    return vertexList[vVid].predVID != vidNIL;
}



void graph::dijkstra(int s) {
    // reset the set and lambda arrays
    for (int i = 0; i < vCount; i++) {
        set[i] = Y;
        lambda[i] = INFINITE;
    }

    // set s lambda to start the search
    // it will get moved to set X in the first part of the loop
    lambda[s] = 0;

    // while theres a value in set y relax all the edges in set y
    int mindex;
    while (minLambdaY(mindex)) { // find the current smallest val in set Y
        // lock in the distance of mindex
        set[mindex] = X;

        // go through the adjacency matrix and
        // relax all edges adjacent to mindex
        for (int j = 0; j < vCount; j++) {
            if (a[mindex][j] && set[j]) {
                // edge exists and the vertex we are looking
                // at hasn't been optimized yet so we can
                // attempt a relax
                lambda[j] = min(lambda[j], lambda[mindex] + a[mindex][j]);
            }
        }
    }

}



bool graph::minLambdaY(int &minV) {
    bool rc = false;
    int smallestY = -1;

    for (int i = 0; i < vCount; i++) {
        if (set[i] == Y && smallestY < 0) {
            smallestY = i;
            rc = true;
        } else {
            if (set[i] == Y) {
                if (lambda[i] < lambda[smallestY]) {
                    smallestY = i;
                }
            }
        }
    }

    minV = smallestY;
    std::cout << smallestY << std::endl;
    return rc;
}



graph::graph(int vidCapacity, bool directed) {
    //initialize variables
    vertexList = new vertex[vidCapacity];
    this->vidCapacity = vidCapacity;
    this->directed = directed;
    vCount = 0;
    eCount = 0;
    set = new int[vidCapacity];
    lambda = new int[vidCapacity];
    q = new queue(vidCapacity);

    // create adjacency matrix by creating an NxN matrix
    // and giving a access to different segments
    int *b = new int[vidCapacity * vidCapacity];
    a = new int*[vidCapacity];
    for (int i = 0; i < vidCapacity; i++) {
        a[i] = b + (i * vidCapacity);
    }

}



graph::~graph() {
    // delete the adjacency matrix, starting with the nxn part and then a**
    if(a) {
        delete [] a[0];
        delete [] a;
        a = NULL;
    }

    // delete vertexList
    if(vertexList) {
        delete [] vertexList;
        vertexList = NULL;
    }

    // delete the queue
    if(q) {
        delete q;
        q = NULL;
    }
}



bool graph::createV(int label) {
    // Check if label is unused and there is space
    bool returnCode = !isV(label) && vCount < vidCapacity;
    
    if(returnCode) {
        // add label to the vertex list and increment vCount
        vertexList[vCount].label = label;
        vCount++;
    }
    
    return returnCode;
}



bool graph::addEdge(int uLabel, int vLabel, int weight) {
    // EITHER EVERYTHING HAPPENS OR NOTHING HAPPENS

    // check if edge is valid and does not already exist
    bool returnCode = (weight > 0) && (!isEdge(uLabel,vLabel));

    if (returnCode) {
        // check if vertices have room to be added
        int need = 0;
        if (isV(uLabel)) {
            need++;
        }
        if (isV(vLabel)) {
            need++;
        }

        if ((vCount + need) <= vidCapacity) {
            // if there is room, create the vertices that don't exist
            // and add weight to their corresponding spot on the adj matrix
            createV(uLabel);
            createV(vLabel);
            a[labelToVid(uLabel)][labelToVid(vLabel)] = weight;
            if (!directed) {
                // undirected graph, add mirror edge as well
                a[labelToVid(vLabel)][labelToVid(uLabel)] = weight;
            }
            eCount++;
            returnCode = true;
        }
    }

    return returnCode;
}



bool graph::deleteEdge(int uLabel, int vLabel, int &weight) {
    // set returnCode and weight to be returned
    bool returnCode = false;
    weight = -1;
    // Check if an edges exists between the two labels
    if (isEdge(uLabel,vLabel)) {

        // set the weight of the edge to 0 and decrement edge count
        int uID = labelToVid(uLabel);
        int vID = labelToVid(vLabel);
        weight = a[uID][vID]; // capture the old weight

        if (!directed) {
            // undirected graph, reset mirror edge as well
            a[vID][uID] = 0;
        }
        a[uID][vID] = 0; 
        eCount--;
        returnCode = true;   
    }

    return returnCode;
}



int graph::getEdgeWeight(int uLabel, int vLabel) {
    int returnCode = -1;
    // check if both labels exist and
    // get the weight from the adj matrix if they do
    if (isV(uLabel) && isV(vLabel)) {
        returnCode = a[labelToVid(uLabel)][labelToVid(vLabel)];
    }

    return returnCode;
}



void graph::clear() {
    // reset adjacency matrix
    for (int i = 0; i < vCount; i++) {
        for (int j = i; j < vCount; j++) {
            a[i][j] = 0;
        }
    }

    //reset vCount and eCount
    vCount = 0;
    eCount = 0;
}



int graph::inDegree(int label) const {
    int returnCode = -1;

    // check if label exists and if graph is directed
    if (directed && isV(label)) {
        int vid = labelToVid(label);
        returnCode = 0;

        // go through the label's column and 
        // increment every time we find an edge
        for (int i = 0; i < vCount; i++) {
            if (a[i][vid] != 0) {
                returnCode++;
            }
        }
    }

    return returnCode;
}



int graph::outDegree(int label) const {
    int returnCode = -1;

    // check if label exists and graph is directed
    if (directed && isV(label)) {
        int vid = labelToVid(label);
        returnCode = 0;

        // go through the label's row and 
        // increment every time we find an edge
        for (int i = 0; i < vCount; i++) {
            if (a[vid][i] != 0) {
                returnCode++;
            }
        }
    }

    return returnCode;
}



int graph::sizeV() const {
    return vidCapacity;
}



int graph::sizeUsedV() const {
    return vCount;
}



int graph::sizeE() const {
    return eCount;
}



void graph::printIt() const {
    int r, c;

    cout << "Graph info:\n";
    cout << "  Graph capacity = " << vidCapacity << endl;
    cout << "  vCount = " << vCount << endl;
    cout << "  eCount = " << eCount << endl;
    cout << "\nGraph contents:\n";
    for (r = 0; r < vCount; r++) {
	cout << "  Node(" << r << "," << vertexList[r].label << "):";
	for (c = 0; c < vCount; c++) {
	    cout << " " << setw(2) << a[r][c];
	}
	cout << endl;
    }

    cout << "Degree table (normal, in, out)\n";

    for (r = 0; r < vCount; r++) {
	cout << "  Node(" << r << "," << vertexList[r].label << "):";
	cout << "  " << setw(4) << degree(vertexList[r].label);
    cout << ", " << setw(2) << inDegree(vertexList[r].label);
    cout << ", " << setw(2) << outDegree(vertexList[r].label) << endl;
    }
}



void graph::printAllPaths() {
    for (int i = 0; i < vCount; i++) {
        // do bfs for every vertex
        bfs(i);
        for (int j = 0; j < vCount; j++) {
            // check if vertex contains a self loop
            if (i == j && vertexList[i].predVID == i) {
                // vertex points to itself, meaning its a self loop
                cout << vidToLabel(i) << " has a self loop" << endl;
            } else {
                // print label text for print path otherwise
                cout << "Path from " << vidToLabel(i);
                cout << " to " << vidToLabel(j) << endl;
                printPath(i,j);
                cout << endl;
            }
        }
    }
}



int graph::degree(int label) const {
    int returnCode = -1;

    // check if label exists and graph is undirected
    if (!directed && isV(label)) {
        int vid = labelToVid(label);
        returnCode = 0;

        // go through the label's row and 
        // increment every time we find an edge
        for (int i = 0; i < vCount; i++) {
            if (a[vid][i] != 0) {
                returnCode++;
            }
        }
    }

    return returnCode;
}



void graph::dfs() {
    // reset all the vertices before starting dfs
    for (int i = 0; i < vCount; i++) {
        vertexList[i].color = WHITE;
        vertexList[i].predVID = vidNIL;
    }

    // start dfs timer
    int time = 0;

    for (int i = 0; i < vCount; i++) {
        if (vertexList[i].color == WHITE) {
            // vertex unvisited, do dfs here
            dfs(i,time);
        }
    }


}



bool graph::isCyclic() {
    // call either the directed or undirected helper method
    return directed ? isCyclicDirected() : isCyclicUndirected();
}



void graph::dumpAllPairsShortestPath() {
    for (int sVid = 0; sVid < vCount; sVid++) {

	int sLabel = vidToLabel(sVid);

	cout << " For start as (" << sVid << "," << sLabel << "):" << endl;
	for (int dVid = 0; dVid < vCount; dVid++) {
	    int dLabel = vidToLabel(dVid);
	    int distance;

	    dijkstra(sLabel, dLabel, distance);
	    cout << "  The distance to (" << dVid << "," << dLabel << ") is "
		    << distance << endl;
	}
    }
}



bool graph::dijkstra(int sLabel, int dLabel, int &distance) {
    // set returnCode, checking if both labels exist
    bool returnCode = (labelToVid(sLabel) != -1) && (labelToVid(sLabel) != -1);

    // if returnCode is true, run dijkstra through sLabel
    // and set the distance it gives us, otherwise set distance to -1
    if (returnCode) {
        dijkstra(labelToVid(sLabel));
        distance = lambda[labelToVid(dLabel)];
    } else {
        distance = -1;
    }

    return returnCode;
}
