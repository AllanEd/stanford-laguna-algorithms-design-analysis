#include <fstream>
#include <iostream>

using namespace std;

long long sortAndCount(int array[], int sortedArray[], int pointer, int endIndex);

long long mergeAndCountSplitInversions(int array[], int sortedArray[], int pointer, int splitIndex, int endIndex);

int main() {
    int INTEGER_ARRAY_LENGTH = 100000;
    string INTEGER_ARRAY_FILE = "IntegerArray.txt";

    ifstream in(INTEGER_ARRAY_FILE);
    int integerArray[INTEGER_ARRAY_LENGTH];
    int sortedArray[INTEGER_ARRAY_LENGTH];

    for (int i = 0; i < INTEGER_ARRAY_LENGTH; i++)
        in >> integerArray[i];

    long long numberOfInversions = sortAndCount(integerArray, sortedArray, 0, INTEGER_ARRAY_LENGTH - 1);

    cout << " Number of inversions: " << numberOfInversions << endl;

    return 0;

}

long long sortAndCount(int array[], int sortedArray[], int pointer, int endIndex) {
    long long splitIndex;
    long long numberOfInversions = 0;

    if (endIndex > pointer) {
        splitIndex = (endIndex + pointer) / 2;

        numberOfInversions += sortAndCount(array, sortedArray, pointer, splitIndex);
        numberOfInversions += sortAndCount(array, sortedArray, splitIndex + 1, endIndex);

        numberOfInversions += mergeAndCountSplitInversions(array, sortedArray, pointer, splitIndex + 1, endIndex);
    }

    return numberOfInversions;
}

long long mergeAndCountSplitInversions(int array[], int sortedArray[], int pointer, int splitIndex, int endIndex) {
    int leftHalfPointer = pointer;
    int rightHalfPointer = splitIndex;
    int mergePointer = pointer;
    long long inv_count = 0;

    while ((leftHalfPointer <= splitIndex - 1) && (rightHalfPointer <= endIndex)) {
        if (array[leftHalfPointer] <= array[rightHalfPointer]) {
            sortedArray[mergePointer++] = array[leftHalfPointer++];
        } else {
            sortedArray[mergePointer++] = array[rightHalfPointer++];
            inv_count = inv_count + (splitIndex - leftHalfPointer);
        }
    }

    while (leftHalfPointer <= splitIndex - 1)
        sortedArray[mergePointer++] = array[leftHalfPointer++];

    while (rightHalfPointer <= endIndex)
        sortedArray[mergePointer++] = array[rightHalfPointer++];

    for (leftHalfPointer = pointer; leftHalfPointer <= endIndex; leftHalfPointer++)
        array[leftHalfPointer] = sortedArray[leftHalfPointer];

    return inv_count;
}
