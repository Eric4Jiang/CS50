/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool binarySearch(int values[], int min, int max, int value){
    int middle = (min + max)/2;
    if(min > max){
        return false;
    }
    if(values[middle] == value){
        return true;
    }
    else if(values[middle] > value){
        return binarySearch(values, min, middle -1, value);
    }
    else if(values[middle] < value){
        return binarySearch(values, middle + 1, max, value);
    }
    else
        return false;
}

bool search(int value, int values[], int n)
{
    if(n < 0){
        return false;
    }
    int min = 0, max = n - 1;
    return binarySearch(values, min, max, value);
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0; i < n; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(values[j] < values[min]){
                min = j;
            }
        }
        int temp = values[i];
        values[i] = values[min];
        values[min] = temp;
    }
    return;
}
