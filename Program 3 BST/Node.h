#ifndef __NODE_H__
#define __NODE_H__

#include<string>

using namespace std;

class Node
{
    // Each node in your tree should hold a string (note: a string can hold more than one word) 
    // and also contain an integer count.
private:
    int count;
    string phrase;
    Node* left;
    Node* right;
public:

    Node(string);
    //~Node();

    //accessor functions
    string getPhrase() const;
    Node* getLeft() const;
    Node* getRight() const;
    int getCount() const;
    bool isLeaf() const;
 

    //mutator functions

    void setPhrase(string);
    void setLeft(Node*);
    void setRight(Node*);
    void setCount(int);

};

#endif