#include<bits/stdc++.h>

using namespace std;

// template <typename iterator>
// void quickselect (iterator begin, iterator end, int n) {
//     if (begin < end) {

//         int size = end - begin;
//         int pivot_index = rand()%size, pivot = *(begin+pivot_index);
//         int i = -1, j;

//         for (j=0;j<size;j++) {
//             if (*(begin+j) < pivot) {
//                 i++;
//                 swap(*(begin+i),*(begin+j));
//             }
//         }

//         swap(*(begin+i+1),*(begin+pivot_index));

//         if (n < i+1) { quickselect(begin,begin+i,n); }
//         else if (n > i+1) { quickselect(begin+i+2,end,n); }
//     }
// }

void quickselect (vector<int>& nums, int begin = 0, int end, int n) {
    if (begin < end) {

        int pivot_index = begin+(rand()%(end-begin)), pivot = nums[pivot_index];
        int i = begin-1, j;

        swap(nums[pivot_index],nums[end]);

        for (j=begin;j<=end;j++) {
            if (nums[j] < pivot) {
                i++;
                swap(nums[i],nums[j]);
            }
        }

        swap(nums[++i],nums[pivot_index]);
        
        if (n < i) { quickselect(nums,begin,i-1,n); }
        else if (n > i) { quickselect(nums,i+1,end,n); }
    }
}

int main () {

    int n;
    vector<int> nums = {20,1,-1,0,4,5,5};

    cin>>n;
    quickselect(nums,nums.size()-1,n);
    cout<<nums[n];

    return 0;

}