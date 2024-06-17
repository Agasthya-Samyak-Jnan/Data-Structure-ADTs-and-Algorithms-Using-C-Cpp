#include<bits/stdc++.h>

using namespace std;

class node {
    public:
    int a;
    int weight;
    node* f_link, *s_link;

    node () {
        a = 0;
        weight = 0;
        f_link = s_link = nullptr;
    }

    node (int data) {
        a = data;
        weight = 0;
        f_link = s_link = nullptr;
    }

    node (int data,int w) {
        a = data;
        weight = w;
        f_link = s_link = nullptr;
    }

//TO FREE A LINKED LIST
    void freelist () {    
        node *q = this,*prev = this;
        while (prev != nullptr) {
         q = q->s_link;
         free(prev);
         prev = q;
        }
    }
};

class head {
    public:
    int vertices,edges;
    node* h_link;

    head () {
        cout<<"Initializing Graph...\n";
        cout<<"<- Graph Ready to Use ->\n";
        vertices = 0;
        edges = 0;
        h_link = nullptr;
    }

    //TO CHECK IF GRAPH IS EMPTY
    bool empty () {
        return (this->h_link == nullptr);
    }

    //TO ADD NEW VERTICES TO THE GRAPH
    void add_vertex (int a) {
        node* s = this->h_link,* prev = this->h_link;
        node* p = new node(a);

        if (this->h_link == nullptr) { this->h_link = p; }
        else {
          while (s != nullptr) {
            prev = s;
            s = s->f_link;
          }

          prev->f_link = p;
          p->f_link = nullptr;
        } 
        this->vertices++;
    }

    //TO ADD NEW EDGES BETWEEN VERTICES ALREADY PRESENT IN THE GRAPH
    bool add_edge (int a, int b) {

        if (this->h_link == nullptr) { return false; }
     
        node* s = this->h_link,*temp;
        bool ap=false, bp=false;
        while (s != nullptr) {
            if (s->a == a) { ap = true; temp = s;}
            if (s->a == b) { bp = true; }
            if (ap && bp) { s = temp; break; }
            s = s->f_link;
        }
        if (s == nullptr) { return false; }

        while ( s->s_link != nullptr) {
            s = s->s_link;
        }
        struct node* p  = new node(b);
        s->s_link = p;
        this->edges++;
        return true;
    }

    //TO ADD UNDIRECTED EDGES BETWEEN VERTICES ALREADY PRESENT IN GRAPH
    bool add_undirected_edge (int a, int b) {
        if ( this->add_edge(a,b) ) { this->add_edge(b,a); return true; }
        return false;
    }

    //TO DELETE AN EXISTING VERTEX FROM GRAPH IF IT EXISTS
    bool del_vertex (int a) {

        if (this->h_link == nullptr) { return false; }

        node* s = this->h_link,*prev,*temp;

        while (s != nullptr) {
            if (s->a == a) { break; }
            prev = s;
            s = s->f_link;
        }
        if (s == nullptr) { return false; } 

        else {
            if (s == this->h_link) { this->h_link = s->f_link; s->freelist(); }
            else { prev->f_link = s->f_link; s->freelist(); }
        }
        s = this->h_link; prev = s;

        while (s != nullptr) {

            while (prev != nullptr && prev->s_link != nullptr) {
                if (prev->s_link->a == a) 
                {
                 temp = prev->s_link;
                 prev->s_link = temp->s_link;
                 delete(temp);
                 this->edges--;
                }
             prev = prev->s_link;
            }
            s = s->f_link;
            prev = s;
        }
        this->vertices--;
        return true;
    }

    //TO DELETE AN EXISTING EDGE BETWEEN GIVEN TWO VERTICES IN GRAPH IF IT EXISTS
    bool del_edge (int a, int b) {

        if (this->h_link == nullptr) { cout<<"Graph Empty!\n"; return false; }

        node* s = this->h_link,*temp; 
        bool is_deleted = false;

        while ( s != nullptr ) {
            if(s->a == a){ break; } 
            s = s->f_link;
        }
        if (s == nullptr) { return false; }
        else { 
            while (s != nullptr && s->s_link != nullptr) {
                if (s->s_link->a == b) 
                {
                 temp = s->s_link;
                 s->s_link = temp->s_link;
                 delete(temp);
                 this->edges--;
                 is_deleted = true;
                }
                s = s->s_link;
            }
        }
        return is_deleted;
    }

    //TO DELETE UNDIRECTED EDGE IF IT EXISTS IN THE GRAPH
    bool del_undirected_edge (int a, int b) {
        if ( this->del_edge(a,b) ) {
            // if it existed
            if ( this->del_edge(b,a) ) { return true; }
            //if it DID NOT exist
            this->add_edge(a,b);
            return false;
        }
        return false;
    }

    //TO CHECK IF GIVEN VERTEX IS PRESENT IN GRAPH OR NOT
    bool find_vertex (int a) {
  
        if (this->h_link == nullptr) { return false; }

        node* s = this->h_link;

        while (s != nullptr && s->a != a) { s = s->f_link; }
        if (s == nullptr) { return false; }
        else { return true; }
    }

    //BREADTH FIRST SEARCH + QUEUE UTILITY FOR THE SEARCH FUNCTION

//QUEUE UTILITY
int Q[50] = {}, front = -1, rear = -1;

void enqueue (int a) {
    if (rear > 49) { cout<<"Queue Overflow!\n"; return; }
    Q[++rear] = a;
}

int dequeue () {
    if (front >= rear) { return -1; }
    return Q[++front];
}

//BFS FUNCTION
void BFS (int a) {

     if (this->h_link == nullptr) { cout<<"Graph Empty!\n"; return; }

     node* s = this->h_link;
     int i;
     vector<int> factors(2,0);

     breadth_first_search(a,factors);
     while (s != nullptr) {
        for (i=0;i<=rear;i++) {
            if (s->a == Q[i]) { break; }
        }
        if (i > rear) {  
            breadth_first_search(s->a,factors); 
        }
        s = s->f_link;
     }
     if (factors[0]) { cout<<"Graph is Cyclic - "<<factors[0]<<"\n"; }
     else { cout<<"Graph is Acyclic."<<"\n"; }
     if (factors[1]) { cout<<"Graph is Connected."<<"\n"; }
     else { cout<<"Graph is Disconnected."<<"\n"; }
}

void breadth_first_search (int a, vector<int> &factors) {
   
   node* s = this->h_link; 
   front = rear = -1; 
   int nodes = 0,prev,temp;
   enqueue(a);

   while (front <= rear) {
        
        prev = temp;
        temp = dequeue();
        // Traversal Ends Here
        if (temp == -1) { 
            if(nodes==this->vertices) { factors[1] = 1; } 
            cout<<"\n";
            return; 
        }
        cout<<temp<<" ";
        nodes++;

        s = this->h_link;
        while (s != nullptr && s->a != temp) { s = s->f_link; }
        if (s == nullptr) { cout<<"Invalid Vertex! - Starting From Default Vertex ->\n"; return; }
        
        while (s->s_link != nullptr) {
        s = s->s_link;
        int i;
        for (i=0;i<=rear;i++) { 
            if (s->a == Q[i]) { 
                if (s->a  != prev) { factors[0] += 1; }
                break; 
            } 
        }
        if ( i > rear) { enqueue(s->a); }
        }
   }
}

//DEPTH FIRST SEARCH + STACK UTILITY FOR THE SEARCH FUNCTION

//STACK UTILTIY
int S[50] = {}, top = -1;

void push (int a) {
    if (top > 49) { cout<<"Stack Overflow!\n"; return; }
    S[++top] = a;
}

int pop () {
    if (top < 0) { cout<<"Stack Underflow!\n"; return -1; }
    return S[top--];
}

//DFS FUNCTION
void DFS (int a) {

     if (this->h_link == nullptr) { cout<<"Graph Empty!\n"; return; }

     node* s = this->h_link;
     int i;
     vector<int> factors(2,0);

     depth_first_search(a,factors);
     while (s != nullptr) {
        for (i=0;i<=rear;i++) {
            if (s->a == Q[i]) { break; }
        }
        if (i > rear) {  
            depth_first_search(s->a,factors); 
        }
        s = s->f_link;
     }
     if (factors[0]) { cout<<"Graph is Cyclic - "<<factors[0]<<"\n"; }
     else { cout<<"Graph is Acyclic."<<"\n"; }
     if (factors[1]) { cout<<"Graph is Connected."<<"\n"; }
     else { cout<<"Graph is Disconnected."<<"\n"; }
}

void depth_first_search (int a, vector<int> &factors) {

   node* s = this->h_link;
   top = front = rear = -1; 
   int nodes = 0,prev,temp;
   push(a); enqueue(a);

   while (top > -1) {
     prev = temp;
     temp = pop();
     if (temp == -1) { cout<<"Invalid Vertex! - Starting From Default Vertex ->\n"; return; }
     cout<<temp<<" ";
     nodes++;
    
     s = this->h_link;
     while (s != nullptr && s->a != temp) { s = s->f_link; }
     if ( s == nullptr) { cout<<"Invalid Vertex!\n"; return; }

     while (s->s_link != nullptr) {
        s = s->s_link;
        int i;
        for (i=0;i<=rear;i++) { 
            if (s->a == Q[i]) { 
                if (s->a != prev) { factors[0] += 1; }
                break; 
            } 
        }
        if (i > rear) { push(s->a); enqueue(s->a); }
     }
   }
   if (nodes == this->vertices) { factors[1] = 1; }
   cout<<"\n";
}

//TO DISPLAY THE GRAPH IN FORM OF ADJAENCY LINKED LIST
void display () {

if (this->h_link == nullptr) { cout<<"Graph Empty!\n"; return; }

node *s = this->h_link,*p = s;

while (s != nullptr) {
    p = s;
    printf("%d-> ", s->a);
   while (s != nullptr) {
    s = s->s_link;
    if (s != nullptr) { cout<<s->a<<" - "; }
   } 
   printf("\n");
   s = p;
   s = s->f_link;
}
 cout<<"Vertices: "<<this->vertices<<"\n";
 cout<<"Edges: "<<this->edges<<"\n";
}

//TO FREE THE MEMORY ALLOCATION OF FULL GRAPH AUTOMATICALLY - DESTRUCTOR
  ~head () {

    cout<<"Deleting Graph...\n";

    node* s = this->h_link,*prev = s;

    while ( prev != nullptr) {
        s = s->f_link;
        prev->freelist();
        prev = s;
    }

    cout<<"<- Cleanup Complete ->\n- Exiting the Program -";
  } 
};

//DRIVER CODE
int main () {

   int a,x;
{
   head* q = new head();
   while (1) {
    cin>>x;
    switch (x) 
    {
        case 0 : { delete q; return 0; }
        case 1 : { cout<<"Enter Vertex Value to Add:"; 
                   cin>>a;
                   q->add_vertex(a);
                   break;
                 }
        case 2 : { cout<<"Enter Vertex value to Delete:";
                   cin>>a;
                   if (!q->del_vertex(a)) { cout<<"Given Vertex does NOT Exist!\n"; }
                   break;
                 }
        case 3 : { cout<<"Enter Vertices to Add Edge between them:"; 
                   cin>>a>>x;
                   if (!q->add_edge(a,x)) { cout<<"Given Vertices Do NOT Exist!\n"; }
                   break;
                 }
        case 4 : { cout<<"Enter Vertices Values to Remove Edge between them:";
                   cin>>a>>x;
                   if(!q->del_edge(a,x)) { cout<<"Given Edge does Not Exist!\n"; }
                   break; 
                 }
        case 5 : { cout<<"Enter Vertices to Add Undirected Edge between them:";
                   cin>>a>>x;
                   if(!q->add_undirected_edge(a,x)) { cout<<"Given Vertices Do NOT Exist!\n"; }
                   break;
                 }
        case 6 : { cout<<"Enter Vertices to Remove Undirected Edge between them:";
                   cin>>a>>x;
                   if(!q->del_undirected_edge(a,x)) { cout<<"Edge was not Undirected / Didn't Exist!\n"; }
                   break;
                 }
        case 7 : { cout<<"Enter Vertex Value to Check if its present:";
                   cin>>a;
                   if(q->find_vertex(a)) { cout<<"Vertex is Present!\n"; }
                   else { cout<<"Vertex is NOT Present!\n"; }
                   break;         
                 }
        case 8 : { q->display(); 
                   break; 
                 }
        case 9 : { cout<<"Enter Value to Start from for BFS:";
                   cin>>a;
                   q->BFS(a); 
                   break;
                 }
        case 10 : { cout<<"Enter Value to Start from for DFS:";
                   cin>>a;
                   q->DFS(a);
                   break;
                 }
        default : break;
    }
   }
}
    return 0;
}
