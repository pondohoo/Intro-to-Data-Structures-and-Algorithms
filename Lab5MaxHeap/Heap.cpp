#include "Heap.h"
#include<iostream>
using namespace std;

Heap::Heap()
{
    numItems = 0;
}
void Heap::enqueue(PrintJob* job)
{

    if(numItems < MAX_HEAP_SIZE){ // checks if numItems < MAX_HEAP_SIZE. if not, implies violation to max heap properties, thus prints error msg
        if (empty()){               // if array is empty, only need to enqueue job to array
            arr[numItems] = job;
            numItems++;
        }
        
        else{
            
            int curr = numItems;
            while (curr > 0 && arr[(curr - 1) / 2]->getPriority() < job->getPriority()){

                arr[curr] = arr[(curr - 1) / 2];
                curr = (curr - 1) / 2;

            }

            arr[curr] = job;
            numItems++;

        }

    }
    else{
        cout << "ERROR: max heap";
    }

}
void Heap::dequeue()
{
    //remove root by moving it to last rightmost child of last level
    if (numItems > 0)
    {
    arr[0] = arr[numItems - 1];
    --numItems;
    trickleDown(0);
    }

}
void Heap::trickleDown(int index)
{
    int greatest;
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    // check if there is a right child
    if (rightChild < numItems)
    {
    // check if left or right have the greatest priority
        if (arr[rightChild]->getPriority() > arr[leftChild]->getPriority())
        {
            greatest = rightChild;
        }
        else greatest = leftChild;
    // if either right or left child is greater than parent, greatest should become parent--maxheap property
        if (arr[greatest]->getPriority() > arr[index]->getPriority())
        {
            PrintJob* temp = arr[index];
            arr[index] = arr[greatest];
            arr[greatest] = temp;
        }
        index = greatest;
        trickleDown(greatest);
    }
}
PrintJob* Heap::highest()
{
    if (numItems > 0)
    {
        return arr[0]; // max heap ensures the highest priority is the root
    }
    return nullptr;
}
void Heap::print()
{
    //highest priority item is the root item (index 0)
    if (numItems > 0)
    {
        int i = 0;
        while (i < numItems)
         {
            cout << "Priority: " << arr[i]->getPriority() << ", Job Number: " << arr[i]->getJobNumber() << ", Number of Pages: " << arr[i]->getPages() << endl;
            i = i + 1;
         }
    }
}
bool Heap::empty()
{
    return numItems == 0;
}
