#include<bits/stdc++.h>

using namespace std;


void merge_sort (vector<int>& a, int start, int end) {
    
    // Sort Only if Partition has more than 1 element.
    if (start < end) {
     
        // Divide the Array
        int mid = (start+end)/2;
        merge_sort(a,start,mid);
        merge_sort(a,mid+1,end);
       
        // Copy Left and Right Partitions
        vector<int> left, right;
        for (int i=start;i<=mid;i++) { left.push_back(a[i]); }
        for (int j=mid+1;j<=end;j++) { right.push_back(a[j]); }
        
        // Compare and Sort Partitions
        int i = 0 , j = 0, mi = start, l = left.size(), r = right.size();
        while (i<l && j<r) {
            if (left[i]<right[j]) { a[mi++] = left[i++]; }
            else { a[mi++] = right[j++]; }
        }

        // Fill Remaining Elements
        while (i<l) { a[mi++] = left[i++]; }
        while (j<r) { a[mi++] = right[j++]; }
    }

}


int main () {

    int n;

    cin>>n;
    vector<int> a(n);
    for (int i=0;i<n;i++) { cin>>a[i]; }

    merge_sort (a,0,n-1);

    for (auto i : a) { cout<<i<<" "; }

    return 0;
}