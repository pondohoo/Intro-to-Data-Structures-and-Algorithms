#include "WordLadder.h"
#include<fstream>
#include<iostream>
#include <string>
#include <cstring>

using namespace std;

WordLadder::WordLadder(const string& dictFileName)
{
    //open an input stream to draw words from
    ifstream inFS;
    inFS.open(dictFileName);
    if (!inFS.is_open())
    {
        cout << "Error opening file";
        return;
    }
    // continues until input stream does not detect any words left in the file
    string word;
    while (!getline(inFS, word).fail())
    {

        // program only works with 5 letter words
        if (word.size() != 5)
        {
            cout << "Error: Word length must be 5";
            inFS.close();
            return;
        }
        dict.push_back(word);
    }
    inFS.close();
}

void WordLadder::outputLadder(const string& start, const string& end, const string& outputFile)
{

    // open an output stream to push words to
    ofstream oFS;
    oFS.open(outputFile);
    if (!oFS.is_open())
    {
        cout << "Error opening file";
        return;
    }


    //searching if start and end are in dict or not

    //traversing through stl list
    bool foundStart = false;
    bool foundEnd = false;
    list<string>::iterator i;
    for (list<string>::iterator i = dict.begin(); i != dict.end(); i++) //traverses entire list of dictionary words
    {
        if ((*i) == start)
        {
            foundStart = true;
        }
        if ((*i) == end)
        {
            foundEnd = true;
        }
    }
    if (!(foundStart && foundEnd))  //if either start and end are not found, prints error msg
    {
        cout << "Error finding start and end words" << endl;
        return;
    }

    if (start == end) {             //if start is the same word as end. then only print the word to the output file. word ladder is finished
        oFS << start << " ";
        oFS.close();
        return;
    }


    //finding word ladder (breadth first search)

    // if start != end,


    stack<string> wordStack;    
    stack<string> newStack;     
    wordStack.push(start);      //creates stack containing first word in ladder caled wordStack
    queue< stack<string> > stackQueue;    //create queue called stackQueue
    stackQueue.push(wordStack);     // enqueue this Stack on to a Queue of Stacks. At this point, stackQueue only holds one stack containing only the start word.
    const int wordSize = 5;
    char* topWord;
    string temp;
    char* dictWord;
    int countDiff = 0;
    stack<string> outStack;
    list<string>::iterator current;

    // while this Queue of Stacks is not empty
    // get the word on top of the front Stack of this Queue for each word in the dictionary
    while (!stackQueue.empty()) //while queue is not empty,
    {
 
        topWord = &stackQueue.front().top()[0];                 // topWord = top word in front stack of queue

        for (list<string>::iterator i = dict.begin(); i != dict.end(); i++) //traverses through dictionary to find all words that are one letter off the previous word in the stack
        {
            
            countDiff = 0;          //counts how many differences there are between topWord and the dictionary word
            temp = *i;              //temp = deferenced word that i is pointing tp
            dictWord = &temp[0];    // dictionary word i is pointing to

            for (int i = 0; i < wordSize; ++i) //compare topWord to dictWord and count letter differences
            {
                if (topWord[i] != dictWord[i])
                {
                    countDiff++;
                }
            }
            
            if (countDiff == 1)     // if the word is off by just one letter from the top word
                                    // create a new Stack that is a copy of the front Stack and push on this off-by-one word found
            {
                newStack = stackQueue.front(); //assigns copy of front stack to wordStack
                newStack.push(dictWord);       //pushes the dict word onto the newStack stack
                if (dictWord == end)        // if this off-by-one word is the end word of the ladder, this new Stack contains the entire word ladder.
                {
                    while (!newStack.empty()) {         //because stacks are first in last out, create newStack to reverse the stack and print ladder from start word to end word
                        outStack.push(newStack.top());  //pushes top of newStack into outStack, and popping each time to update newStack.top()
                        newStack.pop();
                    }
                    while (!outStack.empty())
                    {
                        oFS << outStack.top() << " ";      //outputs full stack into output file (oFS)
                        outStack.pop();
                    }
                    oFS.close();    //closes file, returns function. word ladder is complete.
                    return;

                }
                else                       // otherwise, enqueue this new Stack and remove this word from the dictionary
                {
                    stackQueue.push(newStack);
                    current = i--;
                    dict.erase(current);
                }
            }

        }

        stackQueue.pop();   //pop queue if front of queue is NOT the completed word ladder
                            //repeats while loop until either the word ladder is found, or all stacks have been popped from queue, in which case word ladder does not exist

    }


    if (stackQueue.empty()) {       //if in the case word ladder is not found, prints "No Word Ladder Found" to the output file.
        oFS << "No Word Ladder Found." << endl;
    }

 


}