/**
 * Title: Algorithm Efficiency and Sorting
 * Author: Burak Yetistiren
 * ID: 21802608
 * Section: 1
 * Assignment: 1
 * Description: driver
 */
#include "sorting.h"
#include <iostream>
#include <cstdlib>
#include "auxArrayFunctions.h"
using namespace std;

int main() {

    int arrInsertion[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};

    int arrMerge[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};

    int arrQuick[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};

    int comps = 0;
    int moves = 0;

    cout << "Array for insertionSort: " << endl;
    insertionSort(arrInsertion, 16, comps, moves);
    displayArray(arrInsertion, 16);
    cout << "Number of key comparassions: ";
    cout << comps << endl;
    cout << "Number of data moves: ";
    cout << moves << endl;

    comps = 0; moves = 0;

    cout << "Array for quickSort: " << endl;
    quickSort(arrQuick, 16, comps, moves);
    displayArray(arrQuick, 16);

    cout << "Number of key comparassions: ";
    cout << comps << endl;
    cout << "Number of data moves: ";
    cout << moves << endl;

    comps = 0; moves = 0;

    cout << "Array for mergeSort: " << endl;
    mergeSort(arrMerge, 16, comps, moves);
    displayArray(arrMerge, 16);

    cout << "Number of key comparassions: ";
    cout << comps << endl;
    cout << "Number of data moves: ";
    cout << moves << endl;

    comps = 0; moves = 0;

    performanceAnalysis();
    return 0;
}

