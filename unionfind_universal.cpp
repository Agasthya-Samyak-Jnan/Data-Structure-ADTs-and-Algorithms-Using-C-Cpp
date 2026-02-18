#include<bits/stdc++.h>

using namespace std;

// YOUR OWN OBJECT , DEFINED BY YOU
struct player {
    int player_no,health;
};

// Defining what equality means in context of "Your Own" Object.
bool operator==(const player &p1, const player &p2) {
     return p1.player_no == p2.player_no;
}

// Hash function for "Your Own" Object to use it in unordered_map.
namespace std {
    template <>
    struct hash<player> {
        size_t operator() (const player &p) {
            return hash<int>()(p.player_no);
        }
    };
}

// Union-Finder Disjoint Set (Rank Method + Path Compression) Generalized to any "Object"/Type Using TEMPLATES.
template <typename obj>
class UFS {
public:
    // Disjoint Set Data Structures
    unordered_map<obj,obj> parent;
    unordered_map<obj,int> rank;

    // Initialise Disjoint Set
    UFS () {}
    
    UFS (vector<obj>& nodes) {
        for (auto &i : nodes) {
            parent[i] = i;
            rank[i] = 0;
        }  
    }

    // Combine/Union thier Families
    void Union (obj a, obj b) {    
        obj A = find(a), B = find(b);
        if (A == B) { return; }
        if (rank[A] > rank[B]) { parent[B] = A; }
        else {
            if (rank[A] == rank[B]) { rank[B]++; }
            parent[A] = B;
        } 
    }

    // Find Upper-Most Parent 
    obj find (obj a) { 
        if (parent.find(a) == parent.end()) { 
            parent[a] = a; 
            rank[a] = 0;
        }
        return parent[a] = (a == parent[a]) ? a : find(parent[a]);
    }
};

// DRIVER CODE
int main () {

    int x;
    vector<player> all_players = {{0,100},{1,50},{2,75},{3,100},{4,10},{5,32}};
    UFS<player> u(all_players);

    while (1) {
        cin>>x;
        switch (x) {
            case 1 : {
                        int a,b;
                        cout<<"Union of : ";
                        cin>>a;
                        cin>>b;
                        u.Union(all_players[a],all_players[b]);
                        break;
                     }
            case 2 : {
                        int a;
                        cout<<"Find Parent of : ";
                        cin>>a;
                        cout<<"Parent of "<<a<<" : "<<u.find(all_players[a]).player_no<<"\n";
                        break;
                     }
            default : { return 0; }
        }
    }

    return 0;
}