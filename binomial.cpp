#include<bits/stdc++.h>

using namespace std;

int countz = 0;

/* EXAMPLE OF TABULATION - DYNAMIC PROGRAMMING - CALCULATE nCr for given n,r - Combination Value */

// int binomial_coeff (int n, int k) {
//     countz++;
//     if (n==k || k==0) { return 1; }
//     if (n<k) { return 0; }
//     return binomial_coeff(n-1,k) + binomial_coeff(n-1,k-1);
// }

int binomial_coeff (int n,int k) {
    vector<vector<int>> dp(n+1,vector<int>(k+1,0));

    for (int i=0;i<=n;i++) {
        for (int j=0;j<=k;j++) {
            if (i<j) { break; }
            countz++;
            if (i==j || j==0) { dp[i][j] = 1; }
            else { dp[i][j] = dp[i-1][j] + dp[i-1][j-1]; }
        }
    }
    return dp[n][k];
}

int main () {
    cout<<"Enter n,k:";
    int n,k;
    cin>>n>>k;
    cout<<binomial_coeff(n,k)<<"\n";
    cout<<countz;
}