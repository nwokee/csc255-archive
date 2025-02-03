#ifndef __BST_H
#define __BST_H


typedef struct key_value {
    int key;
    int value;
} KEY_VALUE;

class node {
    private:
    KEY_VALUE kv; // Stores the key-value pair
    int h; // for future use
    node *left, *right; // Pointer to the left and right children
    
    public:
    node(KEY_VALUE kv); // Constructor
    
    // Declares AVL as a friend class
    friend class BST; 
};

class BST {
    private:
    int nCount;
    node *root;
    KEY_VALUE findMin(node *ptr); // returns the minimum key in the subtree

    // Recursion helpers
    bool insert(KEY_VALUE kv, node *&ptr);
    bool remove(int key, node *&ptr);
    bool getValue(int key, int &value, node *ptr) const;
    void printIt(node *ptr) const;
    void clear(node *ptr);


    public:
    BST(); // Constructor to create the Binary Search Tree Object
    ~BST(); // Destructor that deletes all nodes and destroys the tree

    // inserts kv into tree, returning true if successful
    // or false if the key is already in the tree
    bool insert(KEY_VALUE kv);  

    // removes node with corresponding key, returning true is successful
    // or false if the key does not exist in the tree
    bool remove(int key);

    //empties the binary search tree using recursion
    void clear();

    // stores value of the key if it is in the tree, returning true if
    // the key is in the key and false otherwise
    bool getValue(int key, int &value) const;

    //prints the BST key value pairs in ascending order (by keys)
    void printIt() const; 

    //returns the number of nodes in the tree
    int count() const;
};

#endif