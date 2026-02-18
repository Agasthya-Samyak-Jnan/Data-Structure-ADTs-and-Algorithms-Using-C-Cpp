#include<bits/stdc++.h>

using namespace std;

/* SEARCHING ALGORITHMS */


/* LINEAR SEARCH ALGORITHM */
int linear_search (int* arr, int size, int key) {
    for(int i=0;i<size;i++) {
        if (arr[i] == key) { return i; }
    }
    return -1;
}

/* BINARY SEARCH - ITERATIVE ALGORITHM */
int binary_search (int* arr, int size, int key) {
    int low=0, high=size-1, mid;
    
    while (low < high) {
        mid = (low+high)/2;
        if (arr[mid] == key) { return mid; }
        if (arr[mid] > key) { high = mid; }
        else { low = mid + 1; }
    }
    return -1;
}

/* BINARY SEARCH - RECURSIVE ALGORITHM */
int binary_search (int* arr, int low, int high, int key) {
    if (arr[(low+high)/2] == key) { return (low+high)/2; }
    if (low >= high) { return -1; }
    if (arr[(low+high)/2] < key) { binary_search(arr, (low+high)/2 + 1, high, key); }
    else { binary_search(arr, low, (low+high)/2 , key); }
}

// DRIVER CODE
int main () {
    int n = 8;
    int arr[8] = {1,9,2,3,4,1,5,11};
    printf("%d\n", linear_search(arr,n,3));
    printf("%d\n", binary_search(arr,n,3));
    printf("%d\n", binary_search(arr,0,n-1,3));

    return 0;
}