#ifndef __LIST_H
#define __LIST_H

class list  {
    private:
    int* keys;
    int listCapacity, listCount;
    
    // tracks the size of the heap that is superimposed over the list
    int heapSize;

    void buildHeap(); // converts list to a maxHeap
    void heapify(int index); // performs the heap heapify operation
    void swap(int &x, int &y); // swaps two keys with each other

    // returns the index of the left child of the given index
    int left(int index) const;

    // returns the index of the right child of the given index
    int right(int index) const;

    public:
    // allocates memory for a list with a maximum size of (capacity)
    list(int capacity = 100); 

    // resets memory allocation of the list and deletes the object 
    ~list(); 

    bool insert(int key); // inserts new key at the start of the list
    bool add(int key); // appends new key to the end of the list
    bool insertAt(int index, int key); // inserts new key at specified index
    bool deleteAt(int index, int &key); // deletes key at specified index
    bool deleteFirst(int &key); // deletes the first key of the list
    bool deleteLast(int &key); // deletes the last key of the list
    void clear(); // empties the list
    
    // returns the key at the specified index
    bool readAt(int index, int &key) const; 

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

    // implements bubble sort (time complexity of O(n^2))
    void bubbleSort();

    // implements selection sort (time complexity of O(n^2))
    void selectionSort();

    // implements insertion sort (time complexity of O(n^2))
    void insertionSort();

    // implements heap sort (time complexity of O(nlogn))
    void heapSort();

    // checks if the list is sorted in ascending order, printing
    // the first instance of the list not being sorted
    bool isSorted();
};

#endif