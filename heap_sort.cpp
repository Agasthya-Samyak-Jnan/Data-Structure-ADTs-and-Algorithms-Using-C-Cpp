#include<bits/stdc++.h>

using namespace std;

void max_heapify (vector<int>& a,int n, int i) {
    while (1) {
        int k = i;
        if ( 2*i+1 < n && a[2*i+1] > a[k]) { k = 2*i+1; }
        if ( 2*i+2 < n && a[2*i+2] > a[k]) { k = 2*i+2; }
        if (k != i) { swap(a[i],a[k]); i=k; }
        else { break; }
    }
}

void heap_sort (vector<int>& a, int n) {
     for (int i=n/2-1;i>=0;i--) { max_heapify(a,n,i); }

     for (int i=n-1;i>0;i--) {
        swap(a[i],a[0]);
        max_heapify(a,i,0);
     }
}


int main () {

    int n;
    cin>>n;
    vector<int> a(n);
    for (int i=0;i<n;i++) { cin>>a[i]; }
 
    heap_sort (a,n);
      
    for (int i=0;i<n;i++) { cout<<a[i]<<" "; }
 
    return 0;
}