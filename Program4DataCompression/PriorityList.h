#ifndef __PRIORITYLIST_H__
#define __PRIORITYLIST_H__

#include "Entry.h"

const int MAX_HEAP_SIZE = 999;
class PriorityList
{
private:
    Entry* arr[999];
    int size;
public:
    /*Initializes an empty heap.*/
    PriorityList();

    //returns size
    int getSize();

    /*Inserts a Entry to the heap without
    violating max-heap properties.*/
    void enqueue(string);

    /*Removes the node with highest priority from the heap.*/
    void dequeue();

    /*Returns the node with highest priority.*/
    Entry* highest();
    void testing();
private:

    // called by dequeue, fixes max heap violations
    void trickleDown(int);
    // called by enqueue, fixes max heap violations
    void percolateUp(int);
    bool empty();


};

#endif