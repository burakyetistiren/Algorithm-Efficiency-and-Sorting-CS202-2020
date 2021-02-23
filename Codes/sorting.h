/**
 * Title: Algorithm Efficiency and Sorting
 * Author: Burak Yetistiren
 * ID: 21802608
 * Section: 1
 * Assignment: 1
 * Description: Header for sorting.cpp
 */

#ifndef SORTING_H_
#define SORTING_H_

void insertionSort(int *arr, int size, int &compCount, int &moveCount);

// QuickSort
void quickSort(int *arr, int size, int &compCount, int &moveCount);
void quickSortOrig(int *arr, int first, int last, int &compCount, int &moveCount);
void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount);

// MergeSort
void mergeSort(int *arr, int size, int &compCount, int &moveCount);
void mergeSortOrig(int *arr, int low, int high,  int &compCount, int &moveCount);
void merge(int *arr, int low, int mid, int high, int &compCount, int &moveCount);


// printArray function
void printArray(int *arr, int size);

// performanceAnalysis
void performanceAnalysis();

#endif /* sorting_h */
