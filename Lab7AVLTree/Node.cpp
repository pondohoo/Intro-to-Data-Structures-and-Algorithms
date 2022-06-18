#include "Node.h"
#include<iostream>
using namespace std;


// reused from program 2
Node::Node(string s)
{
    phrase = s;
    left = nullptr;
    right = nullptr;
}



string Node::getPhrase() const
{
    return phrase;
}

Node* Node::getLeft() const
{
    return left;
}

Node* Node::getRight() const
{
    return right;
}

bool Node::isLeaf() const
{
    if (this->getLeft() == nullptr && this->getRight() == nullptr)
    {
        return true;
    }
    return false;
}

void Node::setPhrase(string s)
{
    phrase = s;
}

void Node::setLeft(Node* newLeft)
{
    left = newLeft;
}

void Node::setRight(Node* newRight)
{
    right = newRight;
}

