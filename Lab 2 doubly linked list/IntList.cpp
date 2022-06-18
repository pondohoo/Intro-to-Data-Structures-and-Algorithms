#include "IntList.h"

IntList::IntList()
{
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}
IntList::~IntList()
{
    while (!empty()) {
        pop_front();
    }
}
void IntList::push_front(int value)
{
    if (empty())
    {
        dummyHead->next = new IntNode(value);
        dummyHead->next->prev = dummyHead;


        dummyHead->next->next = dummyTail;
        dummyTail->prev = dummyHead->next;
    }
    else
    {
        IntNode* temp = dummyHead->next;

        dummyHead->next = new IntNode(value);
        dummyHead->next->prev = dummyHead;

        dummyHead->next->next = temp;
        dummyHead->next->next->prev = dummyHead->next;
    }
}
void IntList::pop_front()
{
    if (!(empty()))
    {
        IntNode* temp = dummyHead->next->next;
        delete dummyHead->next;
        dummyHead->next = temp;
        dummyHead->next->prev = dummyHead;
    }
}

 void IntList::push_back(int value)
 {

    if (empty()) {

        dummyHead->next = new IntNode(value);
        dummyHead->next->next = dummyTail;
        dummyHead->next->prev = dummyHead;
        dummyTail->prev = dummyHead->next;

    }
    else {

        IntNode* temp = dummyTail->prev;
        dummyTail->prev = new IntNode(value);
        dummyTail->prev->next = dummyTail;

        dummyTail->prev->prev = temp;
        dummyTail->prev->prev->next = dummyTail->prev;


    }


}
void IntList::pop_back()
{
    if (!(empty()))
    {
        IntNode* temp = dummyTail->prev->prev;
        delete dummyTail->prev;
        dummyTail->prev = temp;
        dummyTail->prev->next = dummyTail;
    }
}
bool IntList::empty() const
{
    if (dummyHead->next == dummyTail)
    {
        return true;
    }
    else return false;
}
ostream& operator<<(ostream& out, const IntList& rhs)
{

    IntNode* curr = rhs.dummyHead->next;

    while (curr != rhs.dummyTail) {

        out << curr->data;

        if (curr->next != rhs.dummyTail) {
            out << ' ';
        }

        curr = curr->next;
    }
    return out;

}
void IntList::printReverse() const
{
    if (!empty())
    {
    IntNode* curr = dummyTail->prev;
    while (curr->prev != dummyHead)
    {
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << curr->data;
    }
}