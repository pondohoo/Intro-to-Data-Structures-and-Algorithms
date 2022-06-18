#include "IntList.h"
#include <iostream>

using namespace std;

int main()
{
    IntList doublyList;

    cout << "Testing push_front" << endl;
    //first case
    doublyList.push_front(2);
    //second case
    doublyList.push_front(3);
    cout << "List should be 3, 2" << endl;
    cout << "List: " << doublyList;

    cout << endl << endl;

    cout << "Testing pop_front" << endl;
    doublyList.pop_front();
    cout << "List should be 2" << endl;
    cout << "List: " << doublyList;

    cout << endl;
    //pop_front can't delete dummy head and tail
    doublyList.pop_front();
    doublyList.pop_front();
    doublyList.pop_front();
    cout << "List must be empty" << endl;
    cout << "List: " << doublyList;

    cout << endl << endl;

    cout << "Testing push_back" << endl;
    //first case
    doublyList.push_back(10);
    //second case
    doublyList.push_back(11);

    cout << "List should be 10 11" << endl;
    cout << "List " << doublyList;
    //testing pop_back
    doublyList.pop_back();
    doublyList.pop_back();
    //pop_back can't delete dummy head and tail
    doublyList.pop_back();
    doublyList.pop_back();
    doublyList.pop_back();

    cout << endl << "List must be empty" << endl << "List: " << doublyList << endl;

    cout << endl;

    cout << "Testing printReverse" << endl;
    doublyList.push_front(5);
    doublyList.push_front(4);
    doublyList.push_front(3);
    doublyList.push_front(2);
    doublyList.push_front(1);

    cout << "List should be: 5 4 3 2 1" << endl;

    cout << "List: "; 
    doublyList.printReverse();

    cout << endl << endl;
    
    return 0;
}