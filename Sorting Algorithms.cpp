#include<bits/stdc++.h>

using namespace std;

/* All Sorting Algorithms are Sorting in Ascending Order */

/* UTILTIES FOR SORTING */

int it = 0;

// Helper Function to Print Array
inline void print (int* arr, int n) {
    for(int i=0;i<n;i++) { printf("%d ", arr[i]); }
    printf("\n");
}

/* BUBBLE SORT ALGORITHM */
void bubble_sort (int* arr, int size) {
    for (int i=0;i<size-1;i++) {
        int swapped = 0; // Optimization
        for (int j=0;j<size-i-1;j++) { it++;
            if (arr[j] > arr[j+1]) {
                swap(arr[j],arr[j+1]);
                swapped = 1; // Optimization
            }
        }
        if (!swapped) { return; } // Optimization
    }
}

/* SELECTION SORT ALGORITHM */
void selection_sort (int* arr, int size) {
    for (int i=0;i<size;i++) {
        int pos=i;
        for (int j=i+1;j<size;j++) { it++;
            if (arr[j] < arr[pos]) { pos=j; }
        }
        int temp = arr[pos];
        arr[pos] = arr[i];
        arr[i] = temp;
    }
}

/* QUICK SORT ALGORITHM */
void quick_sort (int* arr, int start, int end) {
    if (start<end) {                    // Condition to Check if Partition has at least 2 Elements.
        int i = start-1;                // Choosing Left Side Limit of Partition in each Function Call.
        int pivot = arr[end];           // Choosing Pivot Element to compare with and sort element.
        
        for (int j=start;j<=end;j++) { 
            it++;                       // Sort the Elements such that,
            if (arr[j] < pivot) {       // Elements Lesser than PIVOT are at Left Half of Current Partitioned Array.
                i++;                    // Elements Greater than PIVOT are at Right Half of Current Partitioned Array.
                swap(arr[i],arr[j]);  // Swapping elements to arrange in the above way.
            }
        }
        swap(arr[i+1],arr[end]);      // Set the Pivot Element to Position where it divides array into Two Intended Partitions.

        quick_sort(arr,start,i+1-1);    // Sort and Solve the LEFT PARTITION.
        quick_sort(arr,i+1+1,end);      // Sort and Solve the RIGHT PARTITION.
    }
}

/* MERGE SORT ALGORITHM */
void merge_sort (int* arr, int start, int end) {
    
    if (start<end) {                          // If Partition has more than one Element
        merge_sort(arr,start,(start+end)/2);  // Partition First Half
        merge_sort(arr,(start+end)/2+1,end);  // Partition Second Half
         
        int left_size = ((start+end)/2)-start, right_size = end-((start+end)/2);  // Left and Right Partition Size
        int* left_arr = new int[left_size];     // Left Partition Temporary Array
        int* right_arr = new int[right_size];   // Right Partition Temporary Array

        for ( int i=0,j=0; i<left_size && j<right_size; i++,j++ ) {  // Copy Values accordingly for sorting
              left_arr[i] = arr[start+i];
              right_arr[j] = arr[(start+end)/2 + j];
        }

        int i = 0, j = 0, merged_index = start;                   // Index for Left, Right Partitions and Original Array

        while (i < left_size && j < right_size) {                 // Sort and Fill Values Back to Original Array
            if (left_arr[i] < right_arr[i]) { arr[merged_index] = left_arr[i]; i++; }
            else { arr[merged_index] = right_arr[j]; j++; }
            merged_index++;
        }

        // If Right Partition has Some elements not compared, Copy them as they are.
            while (j < right_size) {
                arr[merged_index] = right_arr[j];  
                merged_index++;
                j++;
            }

        // If Left Partition has Some elements not compared, Copy them as they are.
            while (i < left_size) {
                arr[merged_index] = left_arr[i];
                merged_index++;
                i++;
            }

            delete left_arr;
            delete right_arr;
    }
}

/* HEAP SORT ALGORITHM */
// Convert Heap to Max Heap 
void max_heapify (vector<int>& arr, int i, int n) {
     int largest = i;  // Assume Current PARENT is LARGEST.          Note: In Array, 2i+1 = LEFT, 2i+2 = RIGHT.
     if ((2*i+1)<n && arr[largest]<arr[2*i+1]) { largest = 2*i+1; }  // Check if LEFT child > Current PARENT , if so LEFT Child is now the LARGEST.
     if ((2*i+2)<n && arr[largest]<arr[2*i+2]) { largest = 2*i+2; }  // Check if RIGHT child > Current LARGEST , if so RIGHT Child is LARGEST of 3.
     if (largest != i) {  // If PARENT node was NOT LARGEST, ONLY then SWAP to make it LARGEST.
        swap(arr[largest],arr[i]); // Swap the LARGEST value to PARENT node. (Max Heap Rule : Parent Always Greater than Children. ( Applies to Real Life as well, but not in exceptional cases. ))
        max_heapify(arr,largest,n); // Convert Modified Heap to Max Heap to maintain MAX value at ROOT.
     }
}

// Heap Sorting Algorithm
void heap_sort (vector<int>& arr,int n) {
    
    /* First We Have to Construct Heap Such That LARGEST value is at the ROOT. Construct = Rearrange in this case of Array Representation.
       Checking from (n/2-1) would be enough because of Two Reasons:
       1. 0-indexed Array, hence '-1' from 'n/2' should be start point.
       2. A Heap is always a Complete Tree and there will be no more than 1 Height difference in any case, 'n/2' always will be
          one level before the last leaf node in any heap, hence 'n/2'.
    */
    for (int i=n/2-1;i>=0;i--) { max_heapify(arr,i,n); }
    
    /* After building heap as needed, Start Sorting: 
       *. Heap was Constructed such that initially the MAX element is at root. Hence, 1st Step is to Remove MAX element at root.
       1. Remove MAX element at ROOT (arr[0] in Array) by SWAPPING it with LAST LEAF NODE (arr[i]) that is present at present state (i) of heap.
       2. Max Heapify the Modified Heap.
       3. Invalidate the Sorted Node or Number by decrementing 'i'.
       4. Repeat until all Elements are Removed or Invalidated from Heap.
    */
    for (int i=n-1;i>0;i--) {
        swap(arr[0],arr[i]);
        max_heapify(arr,0,i);
    }
}

// DRIVER CODE
int main () {
    int n = 8;
    int arr[8] = {8,7,6,5,4,3,2,1};
    merge_sort(arr,0,8);
    print(arr,n);

    return 0;
}