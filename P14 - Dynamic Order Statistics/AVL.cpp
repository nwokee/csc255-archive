#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "AVL.h"

using namespace std;


node::node(KEY_VALUE kv) {
    // Initialize variables
    this->kv = kv;
    this->h = 1;
    this->subTreeSize = 1;
    this->left = NULL;
    this->right = NULL;
}



int AVL::calcHeight(node *p) {
    int returnCode = 0;
    // if p exists, calculate height based on its children
    if (p) {
        returnCode = max(height(p->left), height(p->right)) + 1;
    }

    return returnCode;
}



int AVL::calcSubTreeSize(node *p) {
    int returnCode = 0;
    // if p exists, calculate subTreeSize based on its children
    if (p) {
        returnCode = getSubTreeSize(p->left) + getSubTreeSize(p->right) + 1;
    }

    return returnCode;
}



int AVL::height(node *p) const{
    int returnCode = 0;
    // if p exists, return its height
    if (p) {
        returnCode = p->h;
    }
    return returnCode;
}



int AVL::getSubTreeSize(node *p) const{
    int returnCode = 0;
    // if p exists, return its subTreeSize
    if (p) {
        returnCode = p->subTreeSize;
    }
    return returnCode;
}



KEY_VALUE AVL::findMin(node *ptr) {
    // find the far left node from the current subtree and return its kv
    while (ptr->left) {
        ptr = ptr->left;
    }
    return ptr->kv;
}



void AVL::rotateLeft(node * &p1) {
    // use temp to make the right child of p1 the new root node of the subtree
    node *temp = p1->right; 

    // make temp's old left child the new right child of p1
    p1->right = temp->left; 
    temp->left = p1; 

    // re-calculate heights, stSizes, and reassign the head node
    p1->h = calcHeight(p1);
    temp->h = calcHeight(temp);
    p1->subTreeSize = calcSubTreeSize(p1);
    temp->subTreeSize = calcSubTreeSize(temp);
    p1 = temp;
}



void AVL::rotateRight(node * &p1) {
    // use temp to make the left child of p1 the new root node of the subtree
    node *temp = p1->left; 

    // make temp's old right child the new left child of p1
    p1->left = temp->right; 
    temp->right = p1;

    // re-calculate heights, stSizes, and reassign the head node
    p1->h = calcHeight(p1);
    temp->h = calcHeight(temp);
    p1->subTreeSize = calcSubTreeSize(p1);
    temp->subTreeSize = calcSubTreeSize(temp);
    p1 = temp;
}



void AVL::bal(node *&p) {
    //only balance if p exists and doBal is true
    if (p) {
        if (doBal) {
            // calculate height difference and only rebalance if list isn't already
            int diff = height(p->left) - height(p->right);
            if (diff == 2) {
                // left heavy, check make LR cases LL then fix balance
                diff = height(p->left->left) - height(p->left->right);
                if (diff == -1) {
                    // LR heavy, rotate left first
                    rotateLeft(p->left);
                }
                // all cases are LL now, free to rotateRight
                rotateRight(p);
            } else if (diff == -2) {
                // right heavy, check make RL cases RR then fix balance
                diff = height(p->right->left) - height(p->right->right);
                if (diff == 1) {
                    // RL heavy, rotate right first
                    rotateRight(p->right);
                }
                // all cases are RR now, free to rotateLeft
                rotateLeft(p);
            }
        }
        // re-calculate height and stSize
        p->h = calcHeight(p);
        p->subTreeSize = calcSubTreeSize(p);
    }
    
}



bool AVL::insert(KEY_VALUE kv, node *&ptr) {
    // setup returnCode and check if node exists
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

    // rebalance tree
    bal(ptr);
    return returnCode;
}



bool AVL::remove(int key, node *&ptr) {
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
            // we're at the right node
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
    // rebalance tree
    bal(ptr);
    return returnCode;
}



bool AVL::getValue(int key, int &value, node *ptr) const {
    // setup returnCode and check if node exists
    bool returnCode = (ptr);

    if (returnCode) {
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



int AVL::getKeyAtRank(node *ptr, int rank) const{
    //initialize returnCode (guaranteed to get changed)
    int returnCode;
    // get size of the left subtree and 
    // compare it to the rank we are looking for
    int stSize = getSubTreeSize(ptr->left) + 1;

    if(rank == stSize) {
        // the node we are at is the rank we want, return the key here
        returnCode = ptr->kv.key;

    } else if (rank < stSize) {
        // rank we are looking for is in the left tree
        // recurse down through it and look again
        returnCode = getKeyAtRank(ptr->left, rank);

    } else {
        // rank we are looking for is in the right tree
        // recurse down through it and look again
        // modifying rank in terms of the right subtree
        returnCode = getKeyAtRank(ptr->right, rank - stSize);
    }

    return returnCode;

}



void AVL::printIt(node *ptr, int &index) const{
    // print node's left side, then the current node, then its right side
    // ONLY IF THE NODE EXISTS
    if (ptr) {
        printIt(ptr->left, index);
        cout << "At " << index << " the value is " << "(" << ptr->kv.key;
        cout << "," << ptr->kv.value << "): height = " << ptr->h << endl;
        index++;
        printIt(ptr->right, index);
    }
}



void AVL::clear(node *ptr) {
    // if node exists, clear its children and delete itself
    if (ptr) {
        clear(ptr->left);
        clear(ptr->right);
        delete ptr;
    }
}



AVL::AVL(bool doBal) {
    // initialize variables
    this->doBal = doBal;
    root = NULL;
    nCount = 0;

}



AVL::~AVL() {
    // because we dont pre allocate anything, we can use the clear method
    // to manually clear all the nodes
    clear();

}



bool AVL::insert(KEY_VALUE kv) {
    // start the insertion recursion
    return insert(kv, root);
}



bool AVL::remove(int key) {
    // start remove recursion with root
    return remove(key, root);

}


void AVL::clear() {
    // start clear recursion with root
    clear(root);

    // reset both variables
    root = NULL;
    nCount = 0;
}



bool AVL::getValue(int key, int &value) const {
    // start looking for value using recursion
    return getValue(key, value, root);
}



void AVL::printIt() const {
    // initialize index and start printing recursion
    int index = 0;
    printIt(root, index);
}



int AVL::count() const {
    return nCount;
}



int max(int a, int b) {
    return (a > b) ? a : b;
}




int AVL::getKeyAtRank(int rank, int &key) const{
    // use key as returnCode to check if given rank is in bounds and
    // use helper getKeyAtRank to recurse through the tree
    // storing the final value in key, as well as returning it
    // all of this can be done in 2 lines
    key = (rank > 0 && rank <= nCount) ? getKeyAtRank(root, rank) : 0;
     
    return key;
}
