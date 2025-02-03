#ifndef __GRAPH_H
#define __GRAPH_H

#include "queue.h"

enum color { WHITE, GRAY, BLACK };

class vertex {
    public:
    int label; // what is the world's name for this vertex
    int color; // for BFS
    int distance; // for BFS and DFS
    int predVID;
    int startTime; // for DFS
    int finishTime; // for DFS
};

class graph {
    private:
    int **a; // the array for the graph (size of vidCapacity)
    vertex *vertexList; // an array of vertex type (size of vidCapacity)
    bool directed; // stores whether the graph is directed; defaults to true.
    bool cycleFound; // stores whether a cycle has been found in the graph
    int vidCapacity; // memorializes the dimensions of the graph matrix
    int vCount; // tracks the number of nodes in the graph 
    int eCount; // tracks the number of edges in the graph
    const int INFINITE = 1000000;
    const int vidNIL = -1;
    
    queue *q;
    
    int min(int x, int y) const; // returns the minimum of x and y
    int max(int x, int y) const; // returns the maximum of x and y

    // Returns the label associated with vertex vid
    // or -1 if the vid is not in range
    int vidToLabel(int vid) const; 

    // returns the vid for the given label
    // otherwise -1 if the label is not in the vertexList
    int labelToVid(int label) const; 

    // returns true if the edge exists.
    bool isEdge(int uLabel, int vLabel) const; 

    // returns true if there is a vid associated with the given label
    bool isV(int label) const;

    // recursive causes the path from uVid to vVid to be printed.
    void printPath(int uVid, int vVid) const;

    // performs the BFS algorithm as described in class and in the CLRS text
    // using the vertex attributes that were defined in the prior assignment
    void bfs(int uVid); 

    // does the private part of Depth First Search
    void dfs(int uVid, int &timestamp); 
    
    // does a dfs, but only starting at v
    void dfs(int vVid);

    // determines whether a directed graph is cyclic
    bool isCyclicDirected();

    // determines whether an undirected graph is cyclic
    bool isCyclicUndirected();

    // determins if a path exists from uVid to vVid
    bool isPath(int uVid, int vVid);

    public:
    graph(int vidCapacity, bool directed = true); // sets up the empty graph

    ~graph(); // deletes the array “a”

    // creates the node labeled by the parameter
    // returns true if label not already used and there is a 
    // label table entry left to be allocated to the label
    // returns false otherwise
    bool createV(int label); 
    
    // creates the edge with the given weight. Weight must be > 0
    bool addEdge(int uLabel, int vLabel, int weight); 

    // deletes the edge, if the edge had been set and decrements eCount 
    // returns true if it deletes it
    // returns false if the edge was already deleted
    // returns false if the labels didn’t match existing nodes
    bool deleteEdge(int uLabel, int vLabel, int &weight); 

    // returns the weight of an edge
    int getEdgeWeight(int uLabel, int vLabel);

    // causes the graph to be reset to its vertices and edges
    void clear(); 

    // return inD of the node; -1 if the node does not exist
    int inDegree(int label) const; 
    
    // return outD of the node; -1 if the node does not exist
    int outDegree(int label) const; 

    // returns the largest size the graph could be, vidCapacity.
    int sizeV() const; 

    // returns the number of nodes actually used, vCount
    int sizeUsedV() const; 

    // returns the number of edges in the graph, eCount
    int sizeE() const; 

    // prints the graph; see sample output for proper format
    void printIt() const; 

    // for every vertex, it prints whether a path exists to each vertex.
    void printAllPaths(); 

    // return the degree of a vertex in an undirected graph
    // returns -1 if graph is directed or vertex doesn't exist
    int degree(int label) const; 

    void dfs(); // traverses the graph using Depth First Searching

    bool isCyclic(); // returns whether graph is Cyclic or not

};

#endif