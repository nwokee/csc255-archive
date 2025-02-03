#include <cstdio>
#include <iostream>
#include <cstdlib>

#ifndef KVDLL_H
#define KVDLL_H

typedef struct key_value {
    int key;
    int value;
} KEY_VALUE;

class node {
    private:
    KEY_VALUE kv; // Stores the key-value pair
    node *next, *prev; // Pointer to the next and prev node in the list
    
    public:
    node(KEY_VALUE kv, node* next = NULL, node* prev = NULL); // Constructor
    
    // Declares kvDoublyLinkedList as a friend class
    friend class kvDoublyLinkedList; 
};

class kvDoublyLinkedList {
    private:
    node *first, *last; // Pointers to the first and last nodes of the list
    int nCount; // Stores the number of entries in the list

    // Recursion helpers
    int getIndex(int key, node* pn, int index) const;
    void printIt(node* pn, int index, int limit) const;
    void printItBackwards(node* pn, int index, int limit) const;
    void clear(node* pn);

    public:   
    kvDoublyLinkedList(); // Constructor to initialize the list
    ~kvDoublyLinkedList(); // Destructor to clean up the list

    // Inserts a new element at the beginning of the list
    bool insert(KEY_VALUE kv);

    // Adds a new element at the end of the list
    bool add(KEY_VALUE kv);

    // Inserts a new element at a specific index
    bool insertAt(int index, KEY_VALUE kv); 

    // Deletes an element at a specific index
    bool deleteAt(int index, KEY_VALUE& kv); 

    // Deletes the first element of the list
    bool deleteFirst(KEY_VALUE& kv); 

    // Deletes the last element of the list
    bool deleteLast(KEY_VALUE& kv); 

    void clear(); // Clears the list

    // Reads the element at a specific index
    bool readAt(int index, KEY_VALUE& kv) const; 

    // Gets the index of a key in the list
    int getIndex(int key) const; 
    
    // Prints up to a specified limit of elements in the list
    void printIt(int limit) const;

    // Prints up to a specified limit of elements in the list in reverse order
    void printItBackwards(int limit) const;
    
    // Returns the number of elements in the list
    int getCount() const;
    
    // Returns the capacity of the list (always -1 as per requirements)
    int getCapacity() const;
};

#endif