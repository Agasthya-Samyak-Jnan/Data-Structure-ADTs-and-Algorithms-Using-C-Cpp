#include<bits/stdc++.h>

using namespace std;

/* DIVIDE AND CONQUER BASED DATA STRUCTURE */

/* Static Segment Tree API - Recursive , 4N Space , Intuitive (Works on Fixed Array of Numbers and Supports Changes only, addition/removal of elements NOT allowed) */
class SegmentTree {
    public:
        // t = Array that logically represents Segment Tree, arr = Original Array
        vector<int> t;
        int n;
    
        SegmentTree (vector<int>& arr) {    
            n = arr.size();
            t = vector<int>(4*n);
            build(0,0,n-1,arr);
        }
    
        // Build Segment Tree from Given Array - O(N) Time, O(2N) Space - Divide and Conquer ideology.
        int build (int i, int start, int end, vector<int>& a) {
            
            if (start < end) {
                int mid = (start+end)/2, left = 2*i+1, right = 2*i+2;
                t[left] = build(left,start,mid,a); 
                t[right] = build(right,mid+1,end,a);  
                return t[i] = t[left] + t[right];
            }
    
            return t[i] = a[start];
        }
    
        // Sum of Range = [left,right] (both inclusive) - O(logN) Time, O(logN) Space.
        int sumRange (int left, int right) {
            return sum(0,left,right,0,n-1);
        }
        int sum (int i, int left, int right, int start, int end) {
            if (right < start or end < left) { return 0; } // Current Range[start,end] does is NOT a part our Range[left,right]
            if (left <= start and right >= end) { return t[i]; } // Current Range[start,end]  is FULLY a part of our Range[left,right]
            int mid = (start+end)/2;
            // Sum up the Ranges on LEFT and RIGHT of current Range[start,end] that are parts of our Range[left,right]
            return sum(2*i+1,left,right,start,mid) + sum(2*i+2,left,right,mid+1,end); // Current Range[start,end]  is PARTIALLY a part of our Range[left,right]
        }
    
        // Update Value - O(logN) Time, O(1) Space.
        void set (int idx, int value) {
            update(0,idx,value,0,n-1);
        }
        void update (int i, int idx, int value, int start, int end) {
            
            // Reached the Value of the Array to be Updated. Change it and Go Back.
            if (start == end) { t[i] = value; return; }
            
            // Find Midpoint to decide direction.
            int mid = (start+end)/2, left = 2*i+1, right = 2*i+2;
            
            // Binary Search Logic - Less than Mid is Left, otherwise number is on Right.
            if (idx <= mid) { update(left,idx,value,start,mid); }
            else { update(right,idx,value,mid+1,end); }
            
            // *AFTER* Updation of Ranges that FORM THIS Range[start,end], update THIS range.
            t[i] = t[left] + t[right];
        }
};

/* Static Segment Tree API - Iterative , 2N Space , Optimized (Works on Fixed Array of Numbers and Supports Changes only, addition/removal of elements NOT allowed) */
class SegmentTree {
    public:
        // t = Array that logically represents Segment Tree, arr = Original Array
        vector<int> t;
        int n;
    
        SegmentTree (vector<int>& arr) {    
            n = arr.size();
            t = vector<int>(2*n);
            build(arr);
        }
    
        // Build Segment Tree from Given Array - O(N) Time, O(2N) Space - Divide and Conquer but Bottom-Up.
        void build (vector<int>& a) {
            for (int i=0;i<n;i++) { t[n+i] = a[i]; }
            for (int i=n-1;i>0;i--) {
                t[i] = t[2*i] + t[2*i+1];
            }

        }

        int sum (int left, int right) {
            left += n;
            right += n;
            int s = 0;
            while (left <= right) {
                if (left % 2 == 1) {
                    s += t[left];
                    left++;
                }
                if (right % 2 == 0) {
                    s += t[right];
                    right--;
                }
                left /= 2;
                right /= 2;
            }
            return s;
        }

        void update (int idx, int val) {
            int i = n + idx;
            t[i] = val;
            while (i > 1) {
                i /= 2;
                t[i] = t[2*i] + t[2*i+1];
            }
        }
};

/* DIVIDE AND CONQUER BASED DATA STRUCTURE */

/* Modified Segment Tree for finding MAX number in Ranged Queries API */
class MaxSegmentTree {
    public:
        // t = Array that logically represents Segment Tree, arr = Original Array
        vector<int> t;
        int n;
    
        MaxSegmentTree (vector<int>& arr) {    
            n = arr.size();
            t = vector<int>(4*n);
            build(0,0,n-1,arr);
        }
    
        // Build Segment Tree from Given Array - O(N) Time, O(2N) Space - Divide and Conquer ideology.
        int build (int i, int start, int end, vector<int>& a) {
            
            if (start < end) {
                int mid = (start+end)/2, left = 2*i+1, right = 2*i+2;
                t[left] = build(left,start,mid,a); 
                t[right] = build(right,mid+1,end,a);  
                return t[i] = max(t[left],t[right]);
            }
    
            return t[i] = a[start];
        }
    
        // Max of Range = [left,right] (both inclusive) - O(logN) Time, O(logN) Space.
        int RangeMax (int left, int right) {
            return Max(0,left,right,0,n-1);
        }
        int Max (int i, int left, int right, int start, int end) {
            if (right < start or end < left) { return 0; } // Current Range[start,end] does is NOT a part our Range[left,right]
            if (left <= start and right >= end) { return t[i]; } // Current Range[start,end]  is FULLY a part of our Range[left,right]
            int mid = (start+end)/2;
            // Max of the Ranges on LEFT and RIGHT of current Range[start,end] that are parts of our Range[left,right]
            return max(Max(2*i+1,left,right,start,mid),Max(2*i+2,left,right,mid+1,end)); // Current Range[start,end]  is PARTIALLY a part of our Range[left,right]
        }
    
        // Update Value - O(logN) Time, O(1) Space.
        void set (int idx, int value) {
            update(0,idx,value,0,n-1);
        }
        void update (int i, int idx, int value, int start, int end) {
            
            // Reached the Value of the Array to be Updated. Change it and Go Back.
            if (start == end) { t[i] = value; return; }
            
            // Find Midpoint to decide direction.
            int mid = (start+end)/2, left = 2*i+1, right = 2*i+2;
            
            // Binary Search Logic - Less than Mid is Left, otherwise number is on Right.
            if (idx <= mid) { update(left,idx,value,start,mid); }
            else { update(right,idx,value,mid+1,end); }
            
            // *AFTER* Updation of Ranges that FORM THIS Range[start,end], update THIS range.
            t[i] = max(t[left],t[right]);
        }
};

/* Dynamic Segment Tree API (Works on Given Domain of Numbers, dynamic memory allocation for stored numbers ONLY, supports Addition/Removal of elements */
class DST {
public:
    DST () { val = 0; freq = 0; left = right = nullptr; }
    DST (int x) { val = x; freq = 1; left = right = nullptr; }
    DST (int x, DST* l, DST* r) { val = x; freq = 1; left = l; right = r; }

    void add (int value) { update(this,range_l,range_r,value,1); }
    void erase (int value) { update(this,range_l,range_r,value,-1); }
    int Sum (int left, int right) { return sum(this,left,right,range_l,range_r); }
    int Count (int left, int right) { return count(this,left,right,range_l,range_r); }

private:
    static const int range_l = 0, range_r = 1e9;
    int val, freq;
    DST* left, *right;

    /* To find Range Sum */
    int sum (DST* root, int left, int right, int start, int end) {
        if (right < start or left > end) { return 0; }
        if (left <= start and end <= right) { return root->val; }
        int mid = (start+end)/2, s = 0;
        s += (root->left) ? sum(root->left,left,right,start,mid) : 0;
        s += (root->right) ? sum(root->right,left,right,mid+1,end) : 0;
        return s;
    }

    /* To find Count of Numbers in a Range (including duplicates) */
    int count (DST* root, int left, int right, int start, int end) {
        if (right < start or left > end) { return 0; }
        if (left <= start and end <= right) { return root->freq; }
        int mid = (start+end)/2, c = 0;
        c += (root->left) ? count(root->left,left,right,start,mid) : 0;
        c += (root->right) ? count(root->right,left,right,mid+1,end) : 0;
        return c;
    }

    /* To add/remove a Number from DST */
    void update (DST* root, int start, int end, int value, int flag) { // flag = +1 -> add, flag = -1 -> remove
        if (start == end) {  
            root->freq += (flag == 1 ? 1 : -1);
            root->val = value * root->freq; 
            return;
        }
        int mid = (start+end)/2;
        if (value <= mid) {
            if (!root->left) { root->left = new DST(); } 
            update(root->left,start,mid,value,flag); 
        }
        else { 
            if (!root->right) { root->right = new DST(); }
            update(root->right,mid+1,end,value,flag); 
        }

        root->val = (root->left ? root->left->val : 0) + (root->right ? root->right->val : 0);
        root->freq = (root->left ? root->left->freq : 0) + (root->right ? root->right->freq : 0);
    }
};

// DRIVER CODE
int main () {

    vector<int> arr = {6,1,5,2,0,-1};
    int n = arr.size();

    SegmentTree s(arr);

    cout<<s.sumRange(2,5)<<"\n";
    s.set(4,3);
    cout<<s.sumRange(2,4)<<"\n";

}