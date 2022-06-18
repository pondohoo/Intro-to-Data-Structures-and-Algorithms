#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include "Entry.h"
using namespace std;
#include <iostream>
#include <vector>


class HashTable
{
private:
    //each entry in the hash table has TWO parts (dictionary)
    //one is what you have and you use to reach the entry (key)
    //the other you don't have and you want to get from the entry (value)

    //both are going to be arrays with pair elements
    pair<string, int>* encoder;
    pair<int, string>* decoder;
    unsigned int size;
public:
    HashTable(unsigned int);
    pair<string, int>* encode(const vector<Entry*>&);
    pair<int, string>* decode(const vector<Entry*>&);
    unsigned int getSize();

};
#endif