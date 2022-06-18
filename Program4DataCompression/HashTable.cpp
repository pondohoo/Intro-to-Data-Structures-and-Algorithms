#include "HashTable.h"

HashTable::HashTable(unsigned int s)
{
    size = s;
    encoder = new pair<string, int>[size];
    decoder = new pair<int, string>[size];
}
pair<string, int>* HashTable::encode(const vector<Entry*>& list)
{
    // in Compression.h I have a vector of Entry objects sorted by their frequency (member variable)

    // right now I'm thinking maybe to pass that in here (as a parameter) and push those entries
    // onto the encoder array here and decoder array on decode()

    pair<string, int> temp;

    for (unsigned int i = 0; i < list.size(); ++i)
    {

        temp = make_pair(list.at(i)->getToken(), list.at(i)->getCode());

        encoder[i] = temp;

    }

    return encoder;
}
pair<int, string>* HashTable::decode(const vector<Entry*>& list)
{
    
    pair<int, string> temp;

    for (unsigned int i = 0; i < list.size(); ++i)
    {

        temp = make_pair(list.at(i)->getCode(), list.at(i)->getToken());

        decoder[i] = temp;

    }

    return decoder;
}

unsigned int HashTable::getSize()
{
    return size;
}
//int HashTable::createEncodeHash(const string& s)
//{
//    // since hashing string, I'm using multiplicative hashing
//
//    //Daniel J. Bernstein initial value
//    unsigned int hash = 5381;
//    int multiplier = 33;
//    for (unsigned int i = 0; i < s.size(); ++i)
//    {
//        hash = (hash * multiplier) + s.at(i);
//    }
//
//    hash = hash % size;
//    return hash;
//}
//int HashTable::createDecodeHash(int)
//{
//
//}