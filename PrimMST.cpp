#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> primMST (vector<vector<int>>& g, int n) {

    vector<vector<int>> MST(n,vector<int>(n,-1));

    vector<bool> inMST(n,false); // To Track Vertices added to MST
    vector<int> minEdges(n,101); // Minimum Weight of all Edges from a Given Vertex
    vector<int> toVertex(n,-1); // Destination Vertex of Minimum Edge from Given Vertex

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    pq.push({101,0});

    while (!pq.empty()) {

        // Find Vertex with Minimum Cost Edge,
        int current_vertex = pq.top().second; pq.pop();
        if (inMST[current_vertex]) { continue; }
        inMST[current_vertex] = true; 


        // Add the Minimum Edge Associated with the CURRENT_VERTEX to the MST,
        // Weight of Edge = minEdge[current_vertex],
        // Other Vertex of Edge = toVertex[current_vertex].
        if (toVertex[current_vertex] != -1) { 
            MST[current_vertex][toVertex[current_vertex]] = g[current_vertex][toVertex[current_vertex]]; 
            MST[toVertex[current_vertex]][current_vertex] = g[toVertex[current_vertex]][current_vertex];
        }

        // Update the Minimum Edge Table if any Edge with cost less than in the table associated with current_vertex
        for (int j=0;j<n;j++) {
            if ( g[current_vertex][j] != 101 && !inMST[j] && g[current_vertex][j] < minEdges[j]) {
                minEdges[j] = g[current_vertex][j];
                toVertex[j] = current_vertex;
                pq.push({minEdges[j],j});
            }
        }
    }
    return MST;
} 

int main () {

    vector<vector<int>> g;
    int n,a;
    
    cout<<"Enter Number Of Vertices:";
    cin>>n;
    
    cout<<"Enter Graph:";
    for (int i=0;i<n;i++) {
        vector<int> row;
        for (int j=0;j<n;j++) {
            cin>>a;
            row.push_back(a);
        }
        g.push_back(row);
    }

    g = primMST(g,n); cout<<"\n";
    
    for (auto i : g) {
        for (auto j : i) {
            cout<<j<<" ";
        }
        cout<<"\n";
    }

    return 0;
}
