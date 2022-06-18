#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	size = s;
    hashTable = new list<WordEntry>[size];
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    // since hashing string, I'm using multiplicative hashing

    //Daniel J. Bernstein initial value
    unsigned int hash = 5381;
    int multiplier = 33;
    for (unsigned int i = 0; i < s.size(); ++i)
    {
        hash = (hash * multiplier) + s.at(i);
    }

    hash = hash % size;
    return hash;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {

    //checking if word exists in hash table or not
    int possibleIndex = computeHash(s);
    bool found = false;
	if (hashTable[possibleIndex].size() > 0)
    {
        // list at index is not empty, so check if word is found in list
        for (list<WordEntry>::iterator i = hashTable[possibleIndex].begin(); i != hashTable[possibleIndex].end(); i++)
        {
            if (i->getWord() == s)
            {
                // word is in the hash table
                i->addNewAppearance(score);
                found = true;
            }
        }
    }
    if (!found)
    {
        //if word is not found yet, add it to the possibleIndex list at the end
        hashTable[possibleIndex].push_back(WordEntry(s, score));
    }

}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    // repurposed code from put()

    // find word in hash table
    int possibleIndex = computeHash(s);
    bool found = false;
    double averageToReturn = 0.0;
	if (hashTable[possibleIndex].size() > 0)
    {
        // list at index is not empty, so check if word is found in list
        for (list<WordEntry>::iterator i = hashTable[possibleIndex].begin(); i != hashTable[possibleIndex].end(); i++)
        {
            if (i->getWord() == s)
            {
                averageToReturn = i->getAverage();
                found = true;
            }
        }
    }
    if (!found)
    {
        // if not in hash table, return 2.0 as the average
        averageToReturn = 2.0;
    }
    return averageToReturn;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    // repurposed code from put()

    int possibleIndex = computeHash(s);
	if (hashTable[possibleIndex].size() > 0)
    {
        // list at index is not empty, so check if word is found in list
        for (list<WordEntry>::iterator i = hashTable[possibleIndex].begin(); i != hashTable[possibleIndex].end(); i++)
        {
            if (i->getWord() == s)
            {
                return true;
            }
        }
    }
    return false;
}

