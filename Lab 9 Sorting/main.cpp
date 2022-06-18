#include<cmath>
#include<iostream>
#include <cstdlib>
using namespace std;

const int NUMBERS_SIZE = 50000;

//given functions that generate three similar arrays of random integers
int genRandInt(int low, int high)
{
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[])
{
    for (int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}
//end of given functions


int Quicksort_partition(int numbers[], int i, int k, bool midpointPivot)
{
    //i is start index, k is end index
    //finding midpoint case
    int pivot = 0;
    if (midpointPivot)
    {
        int midpointIndex = i + (k - i) / 2;
        pivot = numbers[midpointIndex];
    }
    else
    {
        // median of 3 case
        int start = i;
        int end = k;
        int mid = start + (end - start) / 2;
        if ((start > end && start < mid) || (start < end && start > mid))
        {
            pivot = start;
        }
        if ((mid > start && mid < end) || (mid < start && mid > end))
        {
            pivot = mid;
        }
        else pivot = end;
    }

    bool done = false;
    while (!done)
    {

        //traversing array from the front, finding an element > pivot
        while (numbers[i] < pivot)
        {
            ++i;
        }
        //traversing array from the back, finding an element < pivot
        while (numbers[k] > pivot)
        {
            --k;
        }
        if (i >= k)
        {
            done = true;
        }
        else
        {
            int temp = numbers[i];
            numbers[i] = numbers[k];
            numbers[k] = temp;

            --k;
            ++i;
        }

    }
    //return last element in lower partition
    return k;
}

//this function sorts the given array in the range from i to k using quicksort method. 
//In this function, pivot is the midpoint element (numbers[(i+k)/2]). 
//(implementation of this function is given in section 21.5)
void Quicksort_midpoint(int numbers[], int i, int k)
{
    //i is start index, k is end index

    //recursion: base case (0 elements or 1 element)
    if (i >= k)
    {
        return;
    }
    int lowPartitionTopIndex = Quicksort_partition(numbers, i, k, true);

    // sorting lower partition
    Quicksort_midpoint(numbers, i, lowPartitionTopIndex);

    // sorting upper partition
    Quicksort_midpoint(numbers, lowPartitionTopIndex + 1, k);


}


//this function utilizes different pivot selection technique in quicksort algorithm. 
//The pivot is the median of the following three values: leftmost (numbers[i]),
// midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). 
//You should modify the partition function given in section 21.5 to select the pivot 
//using median-of-three technique.
void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    if (i >= k)
    {
        return;
    }
    int lowPartitionTopIndex = Quicksort_partition(numbers, i, k, false);

    // sorting lower partition
    Quicksort_medianOfThree(numbers, i, lowPartitionTopIndex);

    // sorting upper partition
    Quicksort_medianOfThree(numbers, lowPartitionTopIndex + 1, k);
}

//this function sorts the given array using InsertionSort method. 
//(implementation of this method is provided in section 21.3).
void InsertionSort(int numbers[], int numbersSize)
{
    for (int i = 1; i < numbersSize; i++)
    {
        int j = i;
        while (j > 0 && numbers[j - 1] > numbers[j])
        {
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            j = j - 1;
        }
    }



}



//clock per milliseconds
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

int main()
{
    srand(time(0));
    int arr[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr, arr2, arr3);

    cout << "Measuring the running time of Quicksort Midpoint on an array of 50,000 random integers" << endl;
    // measuring the time
    clock_t Start = clock();
    //call sort function here
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time elapsed: " << elapsedTime << " milliseconds." << endl;
    cout << "Quicksort Midpoint on sorted array of 50,000 random integers" << endl;
    Start = clock();
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    End = clock();
    cout << "Time elapsed: " << elapsedTime << " milliseconds." << endl;



    cout << endl;



    cout << "Measuring the running time of Quicksort Median of Three on an array of 50,000 random integers" << endl;
    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
    cout << "Time elapsed: " << elapsedTime << " milliseconds." << endl;
    cout << "Quicksort Median of Three on sorted array of 50,000 random integers" << endl;
    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
    cout << "Time elapsed: " << elapsedTime << " milliseconds." << endl;



    cout << endl;



    cout << "Measuring the running time of Insertion Sort on an array of 50,000 random integers" << endl;
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    cout << "Time elapsed: " << elapsedTime << " milliseconds." << endl;
    cout << "Insertion Sort on sorted array of 50,000 random integers" << endl;
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    cout << "Time elapsed: " << elapsedTime << " milliseconds." << endl;










    return 0;
}