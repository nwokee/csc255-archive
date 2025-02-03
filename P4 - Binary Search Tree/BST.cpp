#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

 

node::node(KEY_VALUE kv) {
    // Initialize variables
    this->kv = kv;
    this->left = NULL;
    this->right = NULL;
}

 

KEY_VALUE BST::findMin(node *ptr) {
    // find the far left node from the current subtree and return its kv
    while (ptr->left) {
        ptr = ptr->left;
    }
    return ptr->kv;
}

 

bool BST::insert(KEY_VALUE kv, node *&ptr) {
    //setup returnCode and check if node exists
    bool returnCode = false;

    if (ptr) {
        // node exists, check if we need to go further or if key is a dupe
        if (kv.key < ptr->kv.key) {
            // have to go down the left side
            returnCode = insert(kv, ptr->left);
        } else if (kv.key > ptr->kv.key) {
            // have to go down the right side
            returnCode = insert(kv, ptr->right);
        }
    } else {
        // node doesn't exist, we can add a new node where we are
        ptr = new node(kv);
        returnCode = true;
        nCount++;
    }

    return returnCode;
}

 

bool BST::remove(int key, node *&ptr) {
    // setup returnCode and see if list exists
    bool returnCode = (ptr);

    if (returnCode) {
        // look for the node we are removing
        if (key < ptr->kv.key) {
            // remove from left subtree
            returnCode = remove(key, ptr->left); 
        } else if (key > ptr->kv.key) {
            // remove from right subtree
            returnCode = remove(key, ptr->right); 
        } else {
            //we're at the right node
            if (ptr->right) {
                // right tree exists, find smallest value on the right tree and
                // use it to replace the current node, then delete the dupe
                ptr->kv = findMin(ptr->right);
                remove(ptr->kv.key, ptr->right);
            } else {
                // right tree doesn't exist, shift left subtree up
                node *temp = ptr;
                ptr = ptr->left;
                delete temp;
                temp = NULL;
                nCount--;
            }
            returnCode = true;
        }

    }
    return returnCode;
}

 

bool BST::getValue(int key, int &value, node *ptr) const {
    //setup returnCode and check if node exists
    bool returnCode = false;

    if (ptr) {
        // check if current key we're at is the one we're looking for
        // otherwise go down either the left or right depending on
        // whether the key is greater than or less than the current one
        if(ptr->kv.key == key) {
            value = ptr->kv.value;
            returnCode = true;
        } else if (ptr->kv.key > key) {
            returnCode = getValue(key, value, ptr->left);
        } else {
            returnCode = getValue(key, value, ptr->right);
        }
    }



    return returnCode;
}

 

void BST::printIt(node *ptr) const{
    // print node's left side, then the current node, then its right side
    // ONLY IF THE NODE EXISTS
    if (ptr) {
        printIt(ptr->left);
        cout << "(" << ptr->kv.key << "," << ptr->kv.value << ")" << endl;
        printIt(ptr->right);
    }
}

 

void BST::clear(node *ptr) {
    // if node exists, clear its children and delete itself
    if (ptr) {
        clear(ptr->left);
        clear(ptr->right);
        delete ptr;
    }
}

 

BST::BST() {
    // initialize variables
    root = NULL;
    nCount = 0;

}

 

BST::~BST() {
    // because we dont pre allocate anything, we can use the clear method
    // to manually clear all the nodes
    clear();

}

 

bool BST::insert(KEY_VALUE kv) {
    // start the insertion recursion
    return insert(kv, root);
}

 

bool BST::remove(int key) {
    // start remove recursion with root
    return remove(key, root);

}

 

void BST::clear() {
    // start clear recursion with root
    clear(root);

    //reset both variables
    root = NULL;
    nCount = 0;
}

 

bool BST::getValue(int key, int &value) const {
    // start looking for value using recursion
    return getValue(key, value, root);
}

 

void BST::printIt() const {
    // start printing recursion
    printIt(root);
}

 

int BST::count() const {
    return nCount;
}
