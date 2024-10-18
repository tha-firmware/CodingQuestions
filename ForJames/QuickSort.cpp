#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>


// Programming Test:
// You will implement the Quicksort algorithm and write a test to verify
// correctness.

// Select an arbitrary "pivot" value from the array.
// Move all values less than the pivot to before it.
// Move all values greater than or equal to the pivot to after it.
// The pivot must be located between the two partitions.
// Return the array index of the pivot.
size_t Partition(int* Data, size_t Length)
{
    std::vector<int> SmallerList;
    std::vector<int> BiggerList;

    size_t pivot = 0;
    int pivotVal = Data[pivot];
    
    for (int i = 1; i < Length; i++) {
        if (pivotVal > Data[i]) {
            SmallerList.push_back(Data[i]);
        } else {
            BiggerList.push_back(Data[i]);
        }
    }

    std::memcpy(Data, SmallerList.data(), SmallerList.size()*sizeof(int));
    Data[SmallerList.size()] = pivotVal;
    std::memcpy(&Data[SmallerList.size()+1], BiggerList.data(), BiggerList.size()*sizeof(int));

    return (size_t)SmallerList.size();
}



// Recursive sorting operation.
// Partition the array and recursively sort the upper and lower halves.
// IMPORTANT: Exclude the pivot from further sorting.
void QuickSort(int* Data, size_t Length)
{
    if (Length <= 1)
        return;

    const size_t pivot = Partition(Data, Length);
    QuickSort(Data, pivot);
    
    QuickSort(Data + pivot + 1, Length - pivot - 1);
}

void printArray(int *array, int size){
    for (int i = 0; i < size; i++) {
        printf("%i\n", array[i]); 
    }
}

// Test QuickSort
// Generate a list of random values.
// Sort the list using QuickSort.
// Verify that values are ordered.
int main()
{
    size_t testLength;

    printf("Enter size: ");
    scanf("%llu", &testLength);

    int testArray[testLength];
    for (size_t i = 0; i < testLength; ++i)
        testArray[i] = rand();

    QuickSort(testArray, testLength);

    for (size_t i = 1; i < testLength; ++i)
    {
        if (testArray[i] < testArray[i - 1])
            return 1;
    }
    printArray(testArray, testLength);

    system("pause");
    return 0;
}