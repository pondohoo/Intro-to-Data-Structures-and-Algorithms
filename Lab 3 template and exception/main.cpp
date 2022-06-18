#include<vector>
#include<iostream>
#include<stdexcept>
using namespace std;
template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index);
template<typename T>
void selection_sort(vector<T>& vals);
vector<char> createVector();
char getElement(const vector<char>& vals, unsigned index);
template<typename T>
T getElement(vector<T> vals, int index);


int main()
{
    cout << "Testing selection sort..." << endl << endl;
    vector<int> sortThis;

    cout << "Empty vector" << endl;
    selection_sort(sortThis);
    cout << "Success" << endl;

    cout << endl;
    
    cout << "1 element" << endl;
    sortThis.push_back(100);
    selection_sort(sortThis);
    cout << "Expected 100" << endl;
    cout << "Got: " << sortThis.at(0) << endl;

    cout << endl;

    cout << "Many elements" << endl;
    sortThis.push_back(15);
    sortThis.push_back(100000);
    sortThis.push_back(-1);
    sortThis.push_back(2399);
    cout << "Before: ";
    for (unsigned int i = 0; i < sortThis.size(); ++i)
    {
        cout << sortThis.at(i) << " ";
    }
    cout << endl;
    selection_sort(sortThis);
    cout << "After: ";
    for (unsigned int i = 0; i < sortThis.size(); ++i)
    {
        cout << sortThis.at(i) << " ";
    }
    cout << endl << endl << endl;

    cout << "Testing double vector sorting..." << endl;
    vector<double> doubleSort;
    doubleSort.push_back(15.8959);
    doubleSort.push_back(10.9639);
    doubleSort.push_back(0.303196);
    doubleSort.push_back(-6.2785);
    doubleSort.push_back(-6.30376);
    doubleSort.push_back(-7.96164);
    doubleSort.push_back(-19.7683);
    doubleSort.push_back(14.6592);
    doubleSort.push_back(2.59696);
    doubleSort.push_back(10.8194);
    doubleSort.push_back(-5.39004);
    doubleSort.push_back(3.19263);
    doubleSort.push_back(-6.79472);
    cout << "Expected: -19.7683 -7.96164 -6.79472 -6.30376 -6.2785 -5.39004 0.303196 2.59696 3.19263 10.8194 10.9639 14.6592 15.8959" << endl;
    cout << "Got: ";
    selection_sort(doubleSort);
    for (unsigned int i = 0; i < doubleSort.size(); ++i)
    {
        cout << doubleSort.at(i) << " ";
    }
    cout << endl << endl;






    // given code by zybooks:
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while (--numOfRuns >= 0) {
       try{

        cout << "Enter a number: " << endl;
        cin >> index;
        curChar = getElement(vals, index);
        cout << "Element located at " << index << ": is " << curChar << endl;
      
       }
       catch(const logic_error &excpt){
           cout << excpt.what() << endl;
       }
    }
    return 0;

}


template<typename T>
void selection_sort(vector<T>& vals)
{
    unsigned int i = 0;
    //iterate through the entire vector swapping two elements if there is an element
    // smaller than the current element
    while (i < vals.size())
    {
        int minIndex = min_index(vals, i);
        if (vals.at(i) > vals.at(minIndex))
        {
            T temp = vals.at(i);
            vals.at(i) = vals.at(minIndex);
            vals.at(minIndex) = temp;
        }
        ++i;
    }
}

template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index)
{
    unsigned i = index;
    unsigned min = index;
    // iterate from the given index to the end of the vector
    // find the index of the smallest element and return it
    while (i < vals.size())
    {
        if (vals.at(i) < vals.at(min))
        {
            min = i;
        }
        ++i;
    }
    return min;
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for (int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
T getElement(vector<T> vals, int index) {
    int vectorSize = vals.size();
    if(index < 0 || index >= vectorSize){

        throw logic_error("out of range exception occured");

    }

    for (int i = 0; i < vectorSize; ++i) {
        if (i == index) {
            return vals.at(i);
        }
    }
    return -1;
}
