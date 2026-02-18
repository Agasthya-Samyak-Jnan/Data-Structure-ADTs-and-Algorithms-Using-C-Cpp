#include<bits/stdc++.h>
#define INF 100

using namespace std;

vector<int> bellman_ford (int source, vector<vector<int>>& g, int n) {

    vector<int> dist(n,INF);
    dist[source] = 0;

    // Find Shortest Paths.
    for (int t=0;t<n-1;t++) {
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                if (dist[i] + g[i][j] < dist[j]) { dist[j] = dist[i] + g[i][j]; }
            }
        }
    }

    // Check if Graph contains Negative Cycles.
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (dist[i] + g[i][j] < dist[j]) { return {-1}; }
        }
    }

    return dist;
}

// CONCISE VERSION
vector<int> bellman_ford (int source, vector<vector<int>>& g, int n) {

    vector<int> dist(n,INF);
    dist[source] = 0;

    // Find Shortest Paths.
    for (int t=0;t<n;t++) {
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                if (dist[i] + g[i][j] < dist[j]) { 
                    if (t == n-1) { return {-1}; }
                    dist[j] = dist[i] + g[i][j]; 
                }
            }
        }
    }
    
    return dist;
}

int main () {

    int n;
    cout<<"Enter Number Of Vertices:";
    cin>>n;
    
    vector<vector<int>> g(n,vector<int>(n,INF));
    cout<<"Enter Graph:";
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cin>>g[i][j];
        }
    }

    vector<int> paths = bellman_ford(0,g,n);
    
    for (auto i : paths) { cout<<i<<" "; }

    return 0;
}