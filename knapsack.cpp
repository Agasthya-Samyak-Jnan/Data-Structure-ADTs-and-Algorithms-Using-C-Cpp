#include <bits/stdc++.h>
using namespace std;

int countz = 0;

/* Recursive Solution */
// int knapsack_solver(int i, int remaining_capacity, vector<int>& w, vector<int>& p) {
//     countz++;

//     if (i < 0 || remaining_capacity < 1) { return 0; }

//     if (w[i] > remaining_capacity) { return knapsack_solver(i-1,remaining_capacity,w,p); }

//     else { return max(p[i]+knapsack_solver(i-1,remaining_capacity-w[i],w,p),knapsack_solver(i-1,remaining_capacity,w,p)); }
// }


/* Recursive - Memoisation Solution [TOP-DOWN] */
// int knapsack_solver(int i, int remaining_capacity, vector<int>& w, vector<int>& p, vector<vector<int>>& dp) {
//     countz++;

//     if (i < 0 || remaining_capacity < 1) { return 0; }
     
//     if (dp[i][remaining_capacity] != -1) { return dp[i][remaining_capacity]; }

//     if (w[i] > remaining_capacity) { dp[i][remaining_capacity] = knapsack_solver(i-1,remaining_capacity,w,p,dp); }

//     else { dp[i][remaining_capacity] = max(p[i]+knapsack_solver(i-1,remaining_capacity-w[i],w,p,dp),knapsack_solver(i-1,remaining_capacity,w,p,dp));}
    
//     return dp[i][remaining_capacity];

// }

/* Iterative - Tabulation Solution [BOTTOM-UP] */
int knapsack_solver (int capacity,vector<int>& w, vector<int>& p) {

    int n = w.size();
    vector<vector<int>>dp (n+1,vector<int>(capacity+1,0));

    for (int i=1;i<=n;i++) {
        for (int j=1;j<=capacity;j++) {
            if (w[i] <= j) { dp[i][j] = max(dp[i-1][j],p[i-1]+dp[i-1][j-w[i-1]]); }
            else { dp[i][j] = dp[i-1][j]; }
        }
    }
    
    return dp[n][capacity];
}

int main() {
    vector<int> weights = {1,2,3,4};
    vector<int> profits = {10, 8, 12, 6};
    int capacity = 4;

    cout << "Answer : " << knapsack_solver(capacity, weights, profits) << endl;
    cout << "Count = " << countz << endl;

    return 0;
}
