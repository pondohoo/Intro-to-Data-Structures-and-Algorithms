#include "Node.h"
#include<iostream>
using namespace std;
Node::Node(string s)
{
    phrase = s;
    count = 0;
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

int Node::getCount() const
{
    return count;
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

void Node::setCount(int newCount)
{
    count = newCount;
}
