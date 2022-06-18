#include "PriorityList.h"
#include<iostream>
using namespace std;

PriorityList::PriorityList()
{
    size = 0;
}
int PriorityList::getSize()
{
    return size;
}
void PriorityList::enqueue(string wordEntry)
{

    if (size < MAX_HEAP_SIZE) { // checks if size < MAX_HEAP_SIZE. if not, implies violation to max heap properties, thus prints error msg
        if (empty()) {               // if array is empty, only need to enqueue entry to array
            Entry* add = new Entry(wordEntry);
            arr[size] = add;
            size++;
        }

        else {
            for (int i = 0; i < size; ++i)
            {
                // going through the array and checking if entry already exists
                if (arr[i]->getToken() == wordEntry)
                {
                    // if entry already exists, increment frequency and fix violations
                    arr[i]->addFrequency();
                    percolateUp(i);
                    return;
                }
            }

            // case that entry was not found in list
            Entry* add = new Entry(wordEntry);
            arr[size] = add;
            percolateUp(size);
            size += 1;
        }

    }
    else {
        cout << "ERROR: max heap";
    }

}
void PriorityList::dequeue()
{
    //remove root by moving it to last rightmost child of last level
    if (size == 1)
    {
        arr[0] = nullptr;
        size = 0;
    }
    if (size > 1)
    {
        arr[0] = arr[size - 1];
        arr[size - 1] = nullptr;
        --size;
        trickleDown(0);
    }

}
void PriorityList::percolateUp(int index)
{
    int parent = (index - 1) / 2;
    if (index > 0 && arr[index]->getFrequency() > arr[parent]->getFrequency())
    {
        Entry* temp = arr[index];
        arr[index] = arr[parent];
        arr[parent] = temp;
        percolateUp(parent);
    }
}
void PriorityList::trickleDown(int index)
{
    int greatest;
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    // check if there is a right child
    if (rightChild < size)
    {
        // check if left or right have the greatest priority
        if (arr[rightChild]->getFrequency() > arr[leftChild]->getFrequency())
        {
            greatest = rightChild;
        }
        else greatest = leftChild;
        // if either right or left child is greater than parent, greatest should become parent--maxheap property
        if (arr[greatest]->getFrequency() > arr[index]->getFrequency())
        {
            Entry* temp = arr[index];
            arr[index] = arr[greatest];
            arr[greatest] = temp;
        }
        index = greatest;
        trickleDown(greatest);
    }
}
Entry* PriorityList::highest()
{
    if (size > 0)
    {
        return arr[0]; // max heap ensures the highest priority is the root
    }
    return nullptr;
}
bool PriorityList::empty()
{
    return size == 0;
}



//for tests
void PriorityList::testing()
{
    enqueue("hi");
    enqueue("bye");
    enqueue("hi");
    enqueue("555");
    enqueue("a");
    enqueue("a");
    enqueue("a");
    enqueue("b");
    enqueue("b");
    enqueue("555");
    enqueue("55");
    for (int i = 0; i < 10; ++i)
    {
        char curr = 'a';
        for (int j = 0; j < i; ++j)
        {
            ++curr;
            string hi = "";
            hi = curr;
            enqueue(hi);
        }
    }
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i]->getToken() << " " << arr[i]->getFrequency() << endl;
    }
}