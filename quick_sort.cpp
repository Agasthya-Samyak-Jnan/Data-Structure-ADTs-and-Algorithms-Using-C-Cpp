#include<bits/stdc++.h>

using namespace std;

void bc (vector<int>& a, int start, int end) {
    if (start < end) {
        int mid = (start+end)/2;
        swap(a[mid],a[end]);
        bc(a,start,mid-1);
        bc(a,mid,end);
    }
}


void quick_sort (vector<int>& a, int start, int end) {
    if (start < end) {

        int pivot = a[end], i = start-1;

        for (int j=start;j<end;j++) {
            if (a[j] < pivot) {
                i++;
                swap(a[i],a[j]);
            }
        }
        swap(a[i+1],a[end]);

        quick_sort(a,start,i);
        quick_sort(a,i+2,end);
    }
}

int main () {

    int n;

    cin>>n;
    vector<int> a(n);
    for (int i=0;i<n;i++) { cin>>a[i]; }

    quick_sort (a,0,n);

    for (auto i : a) { cout<<i<<" "; }

    return 0;
}