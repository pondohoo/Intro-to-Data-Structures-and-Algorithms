#ifndef __COMPRESSION_H__
#define __COMPRESSION_H__

#include<fstream>
#include<vector>

#include "HashTable.h"
#include "Entry.h"
#include "PriorityList.h"

class Compression
{
private:
    PriorityList frequencyHeap;
    vector<Entry*> accessibleList;
    string filename;
    vector<string> everySingleWordLol;
    vector<int> code;
public:
    Compression(string);

    //passing through the data first time, collecting token-frequency list (max heap)
    void CreateSortedList();

    //empties frequencyHeap into accessibleList vector
    //also assigns codes to each item starting from 1 going to size
    void MakeAccessible();
    void HashItUp();
    void UnhashItUp();
   
};
#endif