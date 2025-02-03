#ifndef __AVL_H
#define __AVL_H


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
    friend class AVL; 
};

class AVL {
    private:
    int nCount;
    node *root;
    bool doBal; // performs bal() if true, otherwise just resets the height

    KEY_VALUE findMin(node *ptr); // returns the minimum key in the subtree
    int calcHeight(node *p); // calculates p's height based on its children
    int height(node *p) const; // returns the height of p if it exists
    void rotateLeft(node * &p1); // balances a right heavy node
    void rotateRight(node * &p1); // balances a left heavy node 
    void bal(node *&p); // balances p if doBal has been set and p exists

    // Recursion helpers
    bool insert(KEY_VALUE kv, node *&ptr);
    bool remove(int key, node *&ptr);
    bool getValue(int key, int &value, node *ptr) const;
    void printIt(node *ptr, int &index) const;
    void clear(node *ptr);


    public:
    AVL(bool doBal); // Constructor to create the AVL Tree Object
    ~AVL(); // Destructor that deletes all nodes and destroys the tree

    // inserts kv into tree, returning true if successful
    // or false if the key is already in the tree
    bool insert(KEY_VALUE kv);  

    // removes node with corresponding key, returning true is successful
    // or false if the key does not exist in the tree
    bool remove(int key);

    // empties the  tree using recursion
    void clear();

    // stores value of the key if it is in the tree, returning true if
    // the key is in the key and false otherwise
    bool getValue(int key, int &value) const;

    // prints the AVL key value pairs in ascending order (by keys)
    void printIt() const; 

    // returns the number of nodes in the tree
    int count() const;
};

#endif