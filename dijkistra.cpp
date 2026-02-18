#include<bits/stdc++.h>
#define INF 101

using namespace std;

void min_heapify_up (vector<pair<int,int>>& a, int i) {
    while (i>0) {
        int k = i;
        if (a[(i-1)/2].first > a[k].first) { k = (i-1)/2; }
        if (k != i) { swap(a[i],a[k]); i=k; }
        else { break; }
    }
}

void min_heapify_down (vector<pair<int,int>>& a, int i, int n) {
    while (1) {
        int k = i;
        if (2*i+1 < n && a[2*i+1].first < a[k].first) { k = 2*i+1; }
        if (2*i+2 < n && a[2*i+2].first < a[k].first) { k = 2*i+2; }
        if (k != i) { swap(a[i],a[k]); i=k; }
        else { break; }
    }
}

vector<int> dijkistra (vector<vector<int>>& g, int src, int n) {

    vector<int> path(n,INF);
    vector<pair<int,int>> pq; // {Edge Weight, End Vertex}

    path[src] = 0;
    pq.push_back({path[src],src});

    while (!pq.empty()) {

        int curr = pq[0].second, min_dist = pq[0].first; // Get Nearest Vertex and its Distance
        swap(pq[0],pq[pq.size()-1]);
        pq.pop_back();
        min_heapify_down(pq,0,pq.size());

        if (min_dist > path[curr]) { continue; } // Don't Find Paths for this. This is NOT valid entry. (Shortest Path was already found!)

        for (int i=0;i<n;i++) { // Check if you can find any Nearer Paths for Vertices that are Reachable from Current Vertex.
            if (g[curr][i] != INF && g[curr][i] != 0 && g[curr][i] + path[curr] < path[i]) { 
                path[i] = g[curr][i] + path[curr]; 
                pq.push_back({path[i],i});  // {Shortest Distance, Shortest Path or Nearest Vertex}
                min_heapify_up(pq,pq.size()-1); // Maintain Nearest Element on Top(Root Position or pq[0]) Every Time.
            }
        }
    } 

    return path;
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

    vector<int> paths = dijkistra(g,0,n); cout<<"\n";
    
    for (auto i : paths) { cout<<i<<" "; }

    return 0;
}