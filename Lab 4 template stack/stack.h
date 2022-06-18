#include<stdexcept>

using namespace std;

const int MAX_SIZE = 20;
template<typename T>
class stack
{
    private:
        T *data;
        int size;
    public:
        stack() // initiates an empty stack
        {
            size = 0;
            data = new T[MAX_SIZE];
        }
        void push(T val) // inserts either an integer or a string into the stack
        {
            if (size < MAX_SIZE)
            {
                data[size] = val;
                ++size;
            }
            else
            {
                throw overflow_error("Called push on full stack.");
            }
        }
        void pop()// removes last element from the data
        {
            if(empty()){
                throw out_of_range("Called pop on empty stack.");
            }
            else{
               size--;
            }
        }
        void pop_two() // removes the last two elements from the data
        {
            if(empty()){
                throw out_of_range("Called pop_two on empty stack.");
            }
            else if(size == 1){
                throw out_of_range("Called pop_two on a stack of size 1.");
            }
            else{
                size--;
                size--;
            }
        }
        T top() // returns the top element of the stack (the last pushed element)
        {
            if (!empty())
            {
                T returnThis = data[size-1];
                return returnThis;
            }
            else 
            {
                throw underflow_error("Called top on empty stack.");
            }
        }

        bool empty() {return size == 0;} // returns true if the stack is empty 
        
};