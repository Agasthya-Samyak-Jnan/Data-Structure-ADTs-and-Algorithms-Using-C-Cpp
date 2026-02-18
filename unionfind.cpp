#include<bits/stdc++.h>

using namespace std;

// Union-Finder Disjoint Set (Rank Method + Path Compression)
class UFS {
public:
    // Disjoint Set Data Structures
    int n;
    vector<int> parent;
    vector<int> rank;

    // Initialise Disjoint Set
    UFS (int n) {
        this->n = n;
        parent = vector<int>(n);
        rank = vector<int>(n,0);
        iota(parent.begin(),parent.end(),0);
    }

    // Combine/Union thier Families
    void Union (int a, int b) {  
        int A = find(a), B = find(b);
        if (A == B) { return; }
        if (rank[A] > rank[B]) { parent[B] = A; }
        else {
            if (rank[A] == rank[B]) { rank[B]++; }
            parent[A] = B;
        } 
    }

    // Find Upper-Most Parent 
    int find (int a) {  
        if (a == parent[a]) { return a;}
        parent[a] = find(parent[a]); // Compress the Recursive Path to parent by directly connecting this node to its parent.
        return parent[a];
    }
};

// DRIVER CODE
int main () {

    int n,x;
    cin>>n;

    UFS* u = new UFS(n);

    while (1) {
        cin>>x;
        switch (x) {
            case 1 : {
                        int a,b;
                        cout<<"Union of : ";
                        cin>>a;
                        cin>>b;
                        u->Union(a,b);
                        break;
                     }
            case 2 : {
                        int a;
                        cout<<"Find Parent of : ";
                        cin>>a;
                        cout<<"Parent of "<<a<<" : "<<u->find(a)<<"\n";
                        break;
                     }
            default : { return 0; }
        }
    }

    return 0;
}