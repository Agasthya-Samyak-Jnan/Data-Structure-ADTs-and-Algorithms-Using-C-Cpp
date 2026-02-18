#include<bits/stdc++.h>
#define INF 101

using namespace std;

void min_heapify_up (vector<pair<int,int>>& a, int i) {
    while (i>0) {
        if (a[(i-1)/2].first > a[i].first) { 
            swap(a[i],a[(i-1)/2]); 
            i = (i-1)/2; 
        }
        else { break; }
    }
}

void min_heapify_down (vector<pair<int,int>>& a, int n, int i) { 
    while (1) {
        int least = i;
        if (2*i+1 < n && a[2*i+1].first < a[least].first) { least = 2*i+1; }
        if (2*i+2 < n && a[2*i+2].first < a[least].first) { least = 2*i+2; }
        if (least != i) { swap(a[i],a[least]); i=least; }
    }
}

vector<vector<int>> primMST (vector<vector<int>>& g, int n) {

    vector<vector<int>> MST(n,vector<int>(n,INF));

    vector<int> inMST(n,0);
    vector<pair<int,int>> pq;
    vector<int> minEdge(n,INF);
    vector<int> toVertex(n,-1);

    pq.push_back({0,0});
    minEdge[0] = 0;

    while (!pq.empty()) {

        int curr = pq[0].second; 
        swap(pq[0],pq[pq.size()-1]); pq.pop_back();
        min_heapify_down(pq,pq.size(),0);

        if (inMST[curr]) { continue; }
        inMST[curr] = 1;

        if (toVertex[curr] != -1) {
            MST[curr][toVertex[curr]] = MST[toVertex[curr]][curr] = g[curr][toVertex[curr]];
        }

        for (int j=0;j<n;j++) {
            if (g[curr][j] != INF && !inMST[j] && g[curr][j] < minEdge[j]) {
                minEdge[j] = g[curr][j];
                toVertex[j] = curr;
                pq.push_back({minEdge[j],j});
                min_heapify_up(pq,pq.size()-1);
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

/*
101 101 101 10 8 101
101 101 5 3 101 101
101 5 101 6 8 2
10 3 6 101 7 3
8 101 8 7 101 1
101 101 2 3 1 101
*/