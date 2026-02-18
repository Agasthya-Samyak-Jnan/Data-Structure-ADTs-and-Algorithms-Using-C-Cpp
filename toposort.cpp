#include<bits/stdc++.h>

using namespace std;
/* SOURCE REMOVAL ALGORITHM */
// void toposort (vector<vector<int>>& g, int n) {

//     vector<int> indegree(n,0);
//     vector<int> removed(n,0);

//     int remaining = n;
    
//     // Construct Indegree table - Efficient Identification of Source Vertex
//     for (int i=0;i<n;i++) {
//         for (int j=0;j<n;j++) {
//             indegree[i] += g[j][i];
//         }
//     }
    
//     // Source Removal - Remove 0-indegree Vertex in each Iteration
//     while (remaining) {
//         bool cyclic = 1;
//         for (int i=0;i<n;i++) {
//             // Select Vertex that is IN graph and Has NO INCOMING EDGES.
//             if (!removed[i] && !indegree[i]) {
//                 cyclic = 0;
//                 // Remove the Edges from this Vertex to other Vertices
//                 for (int j=0;j<n;j++) {
//                     if (g[i][j]) { indegree[j]--; }
//                 }
//                 // Remove Vertex From Graph
//                 removed[i] = 1;
//                 // Get the Topological Order
//                 cout<<i<<" ";
//                 // Number of Vertices in Graph Decrease
//                 remaining--;
//                 break;
//             }
//         }
//         if (cyclic) { cout<<"Cyclic Graph!\n"; return; }
//     }
// }

/* DFS-BASED ALGORITHM */
bool dfs (vector<vector<int>>& g, vector<int>& visited, int i, int n, stack<int>& s, vector<int>& r) {
    visited[i] = 1;
    r[i] = 1;
    for (int j=0;j<n;j++) {
        if (g[i][j]) {
            if (!visited[j]) { if(dfs(g,visited,j,n,s,r)) { return true; } }
            else if (r[j]) { return true; } 
        }
    }
    r[i] = 0;
    s.push(i);
    return false;
}

void toposort (vector<vector<int>>& g, int n) {

    vector<int> visited(n,0);
    vector<int> r(n,0);
    stack<int> s;
    
    for (int i=0;i<n;i++) {
        if (!visited[i]) { if(dfs(g,visited,i,n,s,r)) { cout<<"Cyclic Graph!\n"; return; } }
    }
    
    while (!s.empty()) {
        cout<<s.top()<<" ";
        s.pop();
    }
}

int main () {

    int n;
    cin>>n;

    vector<vector<int>> g(n,vector<int>(n));
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cin>>g[i][j];
        }
    }

    toposort(g,n);

    return 0;
}