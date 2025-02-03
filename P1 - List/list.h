#ifndef __LIST_H
#define __LIST_H

class list  {
    private:
    int* keys;
    int listCapacity, listCount;

    public:
    list(int capacity = 100);  // allocates memory for a list with a maximum size od (capacity)
    ~list(); // resets memory allocation of the list and deletes the object

    bool insert(int key); // inserts new key at the start of the list
    bool add(int key); // appends new key to the end of the list
    bool insertAt(int index, int key); // inserts new key at specified index
    bool deleteAt(int index, int &key); // deletes key at specified index
    bool deleteFirst(int &key); // deletes the first key of the list
    bool deleteLast(int &key); // deletes the last key of the list
    void clear(); // empties the list
    
    bool readAt(int index, int &key) const; // returns the key at the specified index
    void printIt(int limit) const; // prints out (limit) amount of items from the list
    void printItBackwards(int limit) const; // prints out (limit) amount of items from the list backwards
    int getIndex(int key) const; // returns the index of the first appearance of (key)
    int getCapacity() const; // returns the max capacity of the list
    int getCount() const; // returns the current list size
};

#endif