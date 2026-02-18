#include<bits/stdc++.h>

using namespace std;

void dfs (vector<vector<int>>& g, int i, int n, vector<int>& visited, vector<int>& r, bool& cyclic) {

    visited[i] = 1;
    r[i] = 1;
    cout<<i<<" "; // Output the Vertex in Traversal

    for (int j=0;j<n;j++) {
        if (g[i][j]) {
            if (!visited[j]) {
                dfs(g,j,n,visited,r,cyclic);
            }
            else if (r[j]) { cyclic = true; }
        }
    }   
    r[i] = 0;
}

void DFS(vector<vector<int>>& g, int n) {

    vector<int> visited(n,0);
    vector<int> r(n,0);
    int components = 0;
    bool cyclic = false;

    for (int i=0;i<n;i++) {
        if (!visited[i]) { components++; dfs(g,i,n,visited,r,cyclic); }
    }

    if (cyclic) { cout<<"\nCyclic Graph!\n"; }
    else { cout<<"\nAcyclic Graph!\n"; }
    if (components > 1) { cout<<"\nDisconnected Graph!\n"; }
    else { cout<<"\nConnected Graph!\n"; }
    
}

void bfs (vector<vector<int>>& g, int i, int& n, vector<int>& visited, queue<int>& q, bool& connected, bool& cyclic) {

    q.push(i);
    vector<int> inq(n,0);
    inq[i] = 1;
    int nodes = 1;

    while (!q.empty()) {

        int current = q.front(); q.pop();
        visited[current] = 1;
        cout<<current<<" ";

        for (int j=0;j<n;j++) {
            if (g[current][j]) { 
                if (inq[j] && visited[j]) { cyclic = true; }
                else if (!inq[j]) { nodes++; inq[j] = 1; q.push(j); } 
            }
        }
    }
    cout<<"\n";

    if (nodes == n) { connected = true; }
}

void BFS(vector<vector<int>>& g, int n) {

    vector<int> visited(n,0);
    queue<int> q;
    int nodes = 0;
    bool connected = false; 
    bool cyclic = false;

    cout<<"BFS : \n";

    for (int i=0;i<n;i++) {
        if (!visited[i]) { bfs(g,i,n,visited,q,connected,cyclic); }
        if (connected) { break; }
    }

    if (cyclic) { cout<<"\n\nCyclic Graph!\n"; }
    else { cout<<"\nAcyclic Graph!\n"; }
    if (!connected) { cout<<"Disconnected Graph!\n"; }
    else { cout<<"Connected Graph!\n"; }

}

int main () {

    int n;
    cin>>n;

    vector<vector<int>> g(n,vector<int>(n,0));

    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cin>>g[i][j];
        }
    }

    BFS(g,n);
    //DFS(g,n);

    return 0;

}