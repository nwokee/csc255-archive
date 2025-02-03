#ifndef __CLIST_H
#define __CLIST_H

#define cListInc(x) (x = (x + 1) % listCapacity)
#define cListDec(x) (x = (x + listCapacity - 1) % listCapacity)

typedef struct key_value {

int key;

int value;

} KEY_VALUE;


class cKeyValueList  {
    private:
    KEY_VALUE* keyValues;
    int listCapacity, listCount, first, last;

    // converts the index of the circular list 
    // to the physical index in the array
    int virtualToPhysical(int virtualIndex) const;

    // converts the index of the actual array 
    // to the index in the circular list
    int physicalToVirtual(int physicalIndex) const; 

    public:
    // allocates memory for a list with a maximum size of (theCapacity)
    cKeyValueList(int theCapacity = 100);

    // resets memory allocation of the list and deletes the object
    ~cKeyValueList(); 

    // inserts new kv at the start of the list
    bool insert(KEY_VALUE kv); 

    // appends new kv to the end of the list
    bool add(KEY_VALUE kv); 

    // inserts new kv at specified index
    bool insertAt(int index, KEY_VALUE kv); 

    // deletes kv at specified index
    bool deleteAt(int index, KEY_VALUE &kv); 

    // deletes the first kv of the list
    bool deleteFirst(KEY_VALUE &kv);

    // deletes the last kv of the list 
    bool deleteLast(KEY_VALUE &kv); 
    
    // empties the list
    void clear();

    // returns the key at the specified index
    bool readAt(int index, KEY_VALUE &kv) const;

    // prints out (limit) amount of items from the list 
    void printIt(int limit) const; 

    // prints out (limit) amount of items from the list backwards
    void printItBackwards(int limit) const; 

    // returns the index of the first appearance of (key)
    int getIndex(int key) const; 

    // returns the max capacity of the list
    int getCapacity() const; 

    // returns the current list size
    int getCount() const; 

};


#endif