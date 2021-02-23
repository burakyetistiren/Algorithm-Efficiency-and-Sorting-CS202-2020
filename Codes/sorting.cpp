/**
 * Title: Algorithm Efficiency and Sorting
 * Author: Burak Yetistiren
 * ID: 21802608
 * Section: 1
 * Assignment: 1
 * Description: sorting algorithms and performance analysis
 */
#include "sorting.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include "auxArrayFunctions.h"
using namespace std;


void insertionSort(int *arr, int size, int &compCount, int &moveCount) {

  for (int unsorted = 1; unsorted < size; ++unsorted) {

    int nextItem = arr[unsorted];
    int loc = unsorted;

    if ( arr[loc-1] > nextItem)
        ++compCount;

    for (  ;(loc > 0) && (arr[loc-1] > nextItem); --loc)
    {
        arr[loc] = arr[loc-1];
        ++moveCount;
        ++compCount;
    }
    arr[loc] = nextItem;
  }
}


void merge(int *arr, int low, int mid, int high, int &compCount, int &moveCount) {

    int firstBegin = low;
    int firstEnd = mid;

    int secondBegin = mid + 1;
    int secondEnd = high;

    int curIndex = 0;

    int *tempArray = new int[high - low + 1];

    for (; (firstBegin <= firstEnd) && (secondBegin <= secondEnd); ++curIndex) {

        compCount++;
        if (arr[firstBegin] < arr[secondBegin]) {
            tempArray[curIndex] = arr[firstBegin];
            ++firstBegin;
        } else {
            tempArray[curIndex] = arr[secondBegin];
            ++secondBegin;
        }
        moveCount++;
    }


    for (; secondBegin <= secondEnd; ++curIndex) {
        tempArray[curIndex] = arr[secondBegin];
        ++secondBegin;
        moveCount++;
    }

    for (; firstBegin <= firstEnd; ++curIndex) {
        tempArray[curIndex] = arr[firstBegin];
        ++firstBegin;
        moveCount++;
    }

    for (int i = low; i <= high; ++i) {
        arr[i] = tempArray[i - low];
        moveCount++;
    }
}

// signature in the slides
void mergeSortS(int *arr,  int low, int high, int &compCount, int &moveCount) {

    if (low < high) {
        int mid = (low + high) / 2;

        mergeSortS(arr, low, mid, compCount, moveCount);
        mergeSortS(arr, mid + 1, high, compCount, moveCount);

        merge(arr, low, mid, high, compCount, moveCount);
    }
}

// required signature in homework
void mergeSort(int *arr,  int size, int &compCount, int &moveCount) {
    compCount = 0;
    moveCount = 0;
    mergeSortS(arr, 0, size - 1, compCount, moveCount);
}

void quickSort(int *arr, int size, int &compCount, int &moveCount) {
    compCount = 0;
    moveCount = 0;
    quickSortOrig(arr, 0, size - 1, compCount, moveCount);
}

void quickSortOrig(int *arr, int first, int last, int &compCount, int &moveCount) {
    int pivotIndex;

    if (first < last) {
        partition(arr, first, last, pivotIndex, compCount, moveCount);

        quickSortOrig(arr, first, pivotIndex - 1, compCount, moveCount);
        quickSortOrig(arr, pivotIndex + 1, last, compCount, moveCount);
    }
}

void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount) {

    int pivot = arr[first];
    moveCount++;

    int lastS1 = first; // S1 is empty
    int firstUnknown = first + 1; //

    // partitioning the array based on the pivot value
    for (int index = firstUnknown; index <= last; index++) {
        compCount++;
        if (arr[index] < pivot) {
            lastS1++;
            int temp = arr[lastS1];
            arr[lastS1] = arr[index];
            arr[index] = temp;
            moveCount+=3;
        }
    }

    int temp = arr[first];
    arr[first] = arr[lastS1];
    arr[lastS1] = temp;
    moveCount+=3;

    pivotIndex = lastS1; // set pivot index
}

void performanceAnalysis()
{
    int *arrInsertion;
    int *arrMerge;
    int *arrQuick;
    int *tempMerge;
    int *tempQuick;
    int *tempMerge1;
    int *tempQuick1;
    int *tempMerge2;
    int *tempQuick2;
    int *tempMerge3;
    int *tempQuick3;
    int *tempMerge4;
    int *tempQuick4;
    int *tempMerge5;
    int *tempQuick5;

    double **times = new double*[4];

    for (int i = 0; i < 4; i++)
        times[i] = new double[6];

    int **insertionData = new int*[2];
    int **mergeData = new int*[2];
    int **quickData = new int*[2];

    for (int i = 0; i < 2; i++)
    {
        insertionData[i] = new int[6];
        mergeData[i] = new int[6];
        quickData[i] = new int[6];
    }


    createRandomArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 5000);

    tempMerge = new int[5000];
    tempQuick = new int[5000];

    for ( int i = 0; i < 5000; i++)
    {
        tempMerge[i] = arrMerge[i];
        tempQuick[i] = arrQuick[i];
    }

    int noOfMoves = 0;
    int noOfComparasions = 0;
    double duration;

    //Insertion
    clock_t startTime = clock();

    insertionSort(arrInsertion, 5000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][0] = duration;

    insertionData[0][0] = noOfComparasions;
    insertionData[1][0] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 5000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][0] = duration;

    mergeData[0][0] = noOfComparasions;
    mergeData[1][0] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 5000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][0] = duration;

    quickData[0][0] = noOfComparasions;
    quickData[1][0] = noOfMoves;


    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createRandomArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 10000);

    tempMerge1 = new int[10000];
    tempQuick1 = new int[10000];

    for ( int i = 0; i < 10000; i++)
    {
        tempMerge1[i] = arrMerge[i];
        tempQuick1[i] = arrQuick[i];
    }

    //noOfMoves = 0;
    //noOfComparasions = 0;

    //Insertion
    startTime = clock();

    insertionSort(arrInsertion, 10000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][1] = duration;

    insertionData[0][1] = noOfComparasions;
    insertionData[1][1] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 10000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge1;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][1] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][1] = noOfComparasions;
    mergeData[1][1] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 10000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick1;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][1] = duration;
//
//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][1] = noOfComparasions;
    quickData[1][1] = noOfMoves;

    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------


    createRandomArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 15000);

    tempMerge2 = new int[15000];
    tempQuick2 = new int[15000];

    for ( int i = 0; i < 15000; i++)
    {
        tempMerge2[i] = arrMerge[i];
        tempQuick2[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    insertionSort(arrInsertion, 15000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][2] = duration;

    insertionData[0][2] = noOfComparasions;
    insertionData[1][2] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 15000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge2;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][2] = duration;
//
//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][2] = noOfComparasions;
    mergeData[1][2] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 15000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick2;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][2] = duration;
//
//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][2] = noOfComparasions;
    quickData[1][2] = noOfMoves;


    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createRandomArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 20000);

    tempMerge3 = new int[20000];
    tempQuick3 = new int[20000];

    for ( int i = 0; i < 20000; i++)
    {
        tempMerge3[i] = arrMerge[i];
        tempQuick3[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    insertionSort(arrInsertion, 20000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][3] = duration;

    insertionData[0][3] = noOfComparasions;
    insertionData[1][3] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 20000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge3;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][3] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][3] = noOfComparasions;
    mergeData[1][3] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 20000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick3;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][3] = duration;
//
//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][3] = noOfComparasions;
    quickData[1][3] = noOfMoves;

    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createRandomArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 25000);

    tempMerge4 = new int[25000];
    tempQuick4 = new int[25000];

    for ( int i = 0; i < 25000; i++)
    {
        tempMerge4[i] = arrMerge[i];
        tempQuick4[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    insertionSort(arrInsertion, 25000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][4] = duration;

    insertionData[0][4] = noOfComparasions;
    insertionData[1][4] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 25000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge4;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][4] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][4] = noOfComparasions;
    mergeData[1][4] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 25000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick4;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][4] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][4] = noOfComparasions;
    quickData[1][4] = noOfMoves;

    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createRandomArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 30000);

    tempMerge5 = new int[30000];
    tempQuick5 = new int[30000];

    for ( int i = 0; i < 30000; i++)
    {
        tempMerge5[i] = arrMerge[i];
        tempQuick5[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    insertionSort(arrInsertion, 30000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][5] = duration;

    insertionData[0][5] = noOfComparasions;
    insertionData[1][5] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 30000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge5;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][5] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][5] = noOfComparasions;
    mergeData[1][5] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 30000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick5;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][5] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][5] = noOfComparasions;
    quickData[1][5] = noOfMoves;

    cout << endl;
    cout << endl;
    cout << "RESULTS FOR RANDOM ARRAYS:" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "Part c - Performance Analysis for insertionSort Algorithm" << endl;
    cout << setw(10) << "Array Size" << setw(18) << "Elapsed Time" <<  setw(18) << "compCount" << setw(18) << "moveCount" << endl;

    for (int size = 5000, i = 0; size <= 30000; size += 5000, i++) {
        cout.precision(4);
        cout << setw(10) << size << setw(15) << fixed << times[0][i]<< " ms" << setw(18) << insertionData[0][i] << setw(18) << insertionData[1][i] << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "Part c - Performance Analysis for quickSort Algorithm" << endl;
    cout << setw(10) << "Array Size" << setw(18) << "Elapsed Time" <<  setw(18) << "compCount" << setw(18) << "moveCount" << endl;

    for (int size = 5000, i = 0; size <= 30000; size += 5000, i++) {
        cout.precision(4);
        cout << setw(10) << size << setw(15) << fixed << times[2][i]<< " ms" << setw(18) << quickData[0][i] << setw(18) << quickData[1][i] << endl;
    }
    cout << "Part c - ----------------------------------------------------------------" << endl;
    cout << "Performance Analysis for mergeSort Algorithm" << endl;
    cout << setw(10) << "Array Size" << setw(18) << "Elapsed Time" <<  setw(18) << "compCount" << setw(18) << "moveCount" << endl;

    for (int size = 5000, i = 0; size <= 30000; size += 5000, i++) {
        cout.precision(4);
        cout << setw(10) << size << setw(15) << fixed << times[1][i] << " ms" << setw(18) << mergeData[0][i] << setw(18) << mergeData[1][i] << endl;
    }

    createAlreadySortedArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 5000);

    tempMerge = new int[5000];
    tempQuick = new int[5000];

    for ( int i = 0; i < 5000; i++)
    {
        tempMerge[i] = arrMerge[i];
        tempQuick[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();
    for ( int i = 0; i < 600; i++)
        insertionSort(arrInsertion, 5000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 600);

    times[0][0] = duration;

    insertionData[0][0] = noOfComparasions;
    insertionData[1][0] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 5000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][0] = duration;

    mergeData[0][0] = noOfComparasions;
    mergeData[1][0] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 5000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][0] = duration;

    quickData[0][0] = noOfComparasions;
    quickData[1][0] = noOfMoves;


    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createAlreadySortedArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 10000);

    tempMerge1 = new int[10000];
    tempQuick1 = new int[10000];

    for ( int i = 0; i < 10000; i++)
    {
        tempMerge1[i] = arrMerge[i];
        tempQuick1[i] = arrQuick[i];
    }

    //noOfMoves = 0;
    //noOfComparasions = 0;

    //Insertion
    startTime = clock();

    for ( int i = 0; i < 600; i++)
        insertionSort(arrInsertion, 10000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 600);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][1] = duration;

    insertionData[0][1] = noOfComparasions;
    insertionData[1][1] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 10000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge1;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][1] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][1] = noOfComparasions;
    mergeData[1][1] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 10000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick1;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][1] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][1] = noOfComparasions;
    quickData[1][1] = noOfMoves;

    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------


    createAlreadySortedArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 15000);

    tempMerge2 = new int[15000];
    tempQuick2 = new int[15000];

    for ( int i = 0; i < 15000; i++)
    {
        tempMerge2[i] = arrMerge[i];
        tempQuick2[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    for ( int i = 0; i < 600; i++)
        insertionSort(arrInsertion, 15000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 600);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][2] = duration;

    insertionData[0][2] = noOfComparasions;
    insertionData[1][2] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 15000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge2;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][2] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][2] = noOfComparasions;
    mergeData[1][2] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 15000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick2;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][2] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][2] = noOfComparasions;
    quickData[1][2] = noOfMoves;


    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createAlreadySortedArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 20000);

    tempMerge3 = new int[20000];
    tempQuick3 = new int[20000];

    for ( int i = 0; i < 20000; i++)
    {
        tempMerge3[i] = arrMerge[i];
        tempQuick3[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    for ( int i = 0; i < 600; i++)
        insertionSort(arrInsertion, 20000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 600);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][3] = duration;

    insertionData[0][3] = noOfComparasions;
    insertionData[1][3] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 20000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge3;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][3] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][3] = noOfComparasions;
    mergeData[1][3] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 20000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick3;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][3] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][3] = noOfComparasions;
    quickData[1][3] = noOfMoves;

    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createAlreadySortedArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 25000);

    tempMerge4 = new int[25000];
    tempQuick4 = new int[25000];

    for ( int i = 0; i < 25000; i++)
    {
        tempMerge4[i] = arrMerge[i];
        tempQuick4[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    for ( int i = 0; i < 600; i++)
        insertionSort(arrInsertion, 25000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 600);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][4] = duration;

    insertionData[0][4] = noOfComparasions;
    insertionData[1][4] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 25000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge4;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][4] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    mergeData[0][4] = noOfComparasions;
    mergeData[1][4] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 25000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick4;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][4] = duration;

//    noOfComparasions = noOfComparasions / 200;
//    noOfMoves = noOfMoves / 200;

    quickData[0][4] = noOfComparasions;
    quickData[1][4] = noOfMoves;

    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------
    //----------------------------------------------------------------

    createAlreadySortedArrays(*&arrInsertion, *&arrMerge, *&arrQuick, 30000);

    tempMerge5 = new int[30000];
    tempQuick5 = new int[30000];

    for ( int i = 0; i < 30000; i++)
    {
        tempMerge5[i] = arrMerge[i];
        tempQuick5[i] = arrQuick[i];
    }

    noOfMoves = 0;
    noOfComparasions = 0;

    //Insertion
    startTime = clock();

    for ( int i = 0; i < 600; i++)
        insertionSort(arrInsertion, 30000, noOfComparasions, noOfMoves);

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 600);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    times[0][5] = duration;

    insertionData[0][5] = noOfComparasions;
    insertionData[1][5] = noOfMoves;

    //Merge
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        mergeSort(arrMerge, 30000, noOfComparasions, noOfMoves);
        arrMerge = tempMerge5;
    }

    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[1][5] = duration;

    //    noOfComparasions = noOfComparasions / 200;
    //    noOfMoves = noOfMoves / 200;

    mergeData[0][5] = noOfComparasions;
    mergeData[1][5] = noOfMoves;

    //Quick
    startTime = clock();

    for ( int i = 0; i < 10; i++)
    {
        quickSort(arrQuick, 30000, noOfComparasions, noOfMoves);
        arrQuick = tempQuick5;
    }
    duration = 1000 * double( clock() - startTime ) / (CLOCKS_PER_SEC * 10);

    times[2][5] = duration;

    //    noOfComparasions = noOfComparasions / 200;
    //    noOfMoves = noOfMoves / 200;

    quickData[0][5] = noOfComparasions;
    quickData[1][5] = noOfMoves;

    // deallocating the arrays
//    delete []arrInsertion;
//    delete []arrMerge;
//    delete []arrQuick;
    cout << endl;
    cout << endl;
    cout << "RESULTS FOR SORTED ARRAYS:" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "Part c - Performance Analysis for insertionSort Algorithm" << endl;
    cout << setw(10) << "Array Size" << setw(18) << "Elapsed Time" <<  setw(18) << "compCount" << setw(18) << "moveCount" << endl;

    for (int size = 5000, i = 0; size <= 30000; size += 5000, i++) {
        cout.precision(4);
        cout << setw(10) << size << setw(15) << fixed << times[0][i]<< " ms" << setw(18) << insertionData[0][i] << setw(18) << insertionData[1][i] << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "Part c - Performance Analysis for quickSort Algorithm" << endl;
    cout << setw(10) << "Array Size" << setw(18) << "Elapsed Time" <<  setw(18) << "compCount" << setw(18) << "moveCount" << endl;

    for (int size = 5000, i = 0; size <= 30000; size += 5000, i++) {
        cout.precision(4);
        cout << setw(10) << size << setw(15) << fixed << times[2][i]<< " ms" << setw(18) << quickData[0][i] << setw(18) << quickData[1][i] << endl;
    }
    cout << "Part c - ----------------------------------------------------------------" << endl;
    cout << "Performance Analysis for mergeSort Algorithm" << endl;
    cout << setw(10) << "Array Size" << setw(18) << "Elapsed Time" <<  setw(18) << "compCount" << setw(18) << "moveCount" << endl;

    for (int size = 5000, i = 0; size <= 30000; size += 5000, i++) {
        cout.precision(4);
        cout << setw(10) << size << setw(15) << fixed << times[1][i] << " ms" << setw(18) << mergeData[0][i] << setw(18) << mergeData[1][i] << endl;
    }


    // deallocating elapsedTimes and compsAndMoves
    for (int i = 0; i < 2; i++) {
        delete [] quickData[i];
        delete [] mergeData[i];
        delete [] insertionData[i];
    }

    for (int i = 0; i < 4; i++)
        delete [] times[i];

    delete [] quickData;
    delete [] mergeData;
    delete [] insertionData;

    delete [] times;
}



