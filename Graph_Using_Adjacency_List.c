//GRAPH ADT - FUNCTIONS AND OPERATIONS

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int n,i=0,j=0;

struct head {
    int vertices,edges;
    struct node* h_link;
};

struct node {
    int a;
    struct node* f_link, *s_link;
};

//TO FREE A LINKED LIST
void freelist (struct node* q) {
    struct node* prev = q;
    while (prev != NULL) {
        q = q->s_link;
        free(prev);
        prev = q;
    }
}

//TO ADD NEW VERTICES TO THE GRAPH
void add_vertex (struct head* q,int a) {
    struct node* s = q->h_link,* prev = q->h_link;
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->a = a; p->s_link = NULL; p->f_link = NULL;

    if (q->h_link == NULL) { q->h_link = p; }
    else {
     while (s != NULL) {
        prev = s;
        s = s->f_link;
     }

     prev->f_link = p;
     p->f_link = NULL;
    } 
    q->vertices++;
}

//TO ADD NEW EDGES BETWEEN VERTICES ALREADY PRESENT IN THE GRAPH
void add_edge (struct head* q, int a, int b) {

    if (q->h_link == NULL) {printf("Empty Graph!\n"); return; }
     
    struct node* s = q->h_link,*temp;
    bool ap=false, bp=false;
    while (s != NULL) {
       if (s->a == a) { ap = true; temp = s;}
       if (s->a == b) { bp = true; }
       if (ap && bp) { s = temp; break; }
       s = s->f_link;
    }
    if (s == NULL) { printf("Invalid Vertex!\n"); return; }

        while ( s->s_link != NULL) {
            s = s->s_link;
        }
    struct node* p  = (struct node*)malloc(sizeof(struct node));
    p->s_link = NULL; p->f_link = NULL; p->a = b;
    s->s_link = p;
    q->edges++;
}

//TO DELETE AN EXISTING VERTEX FROM GRAPH IF IT EXISTS
void del_vertex (struct head* q, int a) {

    if (q->h_link == NULL) { printf("Empty Graph!\n"); return; }

    struct node* s = q->h_link,*prev,*temp;

    while (s != NULL) {
        if (s->a == a) { break; }
        prev = s;
        s = s->f_link;
    }
    if (s == NULL) { printf("Invalid Vertex!\n"); return; } 

    else {
       if (s == q->h_link) { q->h_link = s->f_link; freelist(s); }
       else { prev->f_link = s->f_link; freelist(s); }
    }
    s = q->h_link; prev = s;

    while (s != NULL) {

        while (prev != NULL && prev->s_link != NULL) {
         if (prev->s_link->a == a) 
         {
          temp = prev->s_link;
          prev->s_link = temp->s_link;
          free(temp);
          q->edges--;
         }
        prev = prev->s_link;
        }
        s = s->f_link;
        prev = s;
    }
    q->vertices--;
}

//TO DELETE AN EXISTING EDGE BETWEEN GIVEN TWO VERTICES IN GRAPH IF IT EXISTS
void del_edge (struct head* q, int a, int b) {

    if (q->h_link == NULL) { printf("Graph Empty!\n"); return; }

    struct node* s = q->h_link,*temp;

    while ( s != NULL ) {
         if(s->a == a){ break; } 
         s = s->f_link;
    }
    if (s == NULL) { printf("Invalid Vertex Given!\n"); return; }
    else { 
        while (s != NULL && s->s_link != NULL) {
            if (s->s_link->a == b) 
            {
             temp = s->s_link;
             s->s_link = temp->s_link;
             free(temp);
             q->edges--;
            }
            s = s->s_link;
        }
    }
}

//TO CHECK IF GIVEN VERTEX IS PRESENT IN GRAPH OR NOT
void find_vertex (struct head* q, int a) {
  
  if (q->h_link == NULL) { printf("Graph Empty!\n"); return; }

  struct node* s = q->h_link;

  while (s != NULL && s->a != a) { s = s->f_link; }
  if (s == NULL) { printf("Vertex Not Present!\n"); }
  else { printf("Vertex is Present!\n"); }
}

//BREADTH FIRST SEARCH + QUEUE UTILITY FOR THE SEARCH FUNCTION

//QUEUE UTILITY
int Q[50] = {}, front = -1, rear = -1;

void enqueue (int a) {
    if (rear > 49) { printf("Queue Overflow!\n"); return; }
    Q[++rear] = a;
}

int dequeue () {
    if (front >= rear) { return -1; }
    return Q[++front];
}

//BFS FUNCTION
void breadth_first_search (struct head* q, int a) {

   if (q->h_link == NULL) { printf("Graph Empty!\n"); return; }

   struct node* s = q->h_link; 
   front = rear = -1; 
   enqueue(a);

   while (front <= rear) {
        
        int temp = dequeue();
        if (temp == -1) { return; }
        printf("%d ", temp);

        s = q->h_link;
        while (s != NULL && s->a != temp) { s = s->f_link; }
        if (s == NULL) { printf("Invalid Vertex!\n"); return; }
        
        while (s->s_link != NULL) {
        s = s->s_link;
        for (i=0;i<=rear;i++) { if (s->a == Q[i]) { break; } }
        if ( i > rear) { enqueue(s->a); }
        }
   }  
}

//DEPTH FIRST SEARCH + STACK UTILITY FOR THE SEARCH FUNCTION

//STACK UTILTIY
int S[50] = {}, top = -1;

void push (int a) {
    if (top > 49) { printf("Stack Overflow!\n"); return; }
    S[++top] = a;
}

int pop () {
    if (top < 0) { printf("Stack Underflow!\n"); return -1; }
    return S[top--];
}
//DFS FUNCTION
void depth_first_search (struct head* q, int a) {

   if (q->h_link == NULL) { printf("Graph Empty!\n"); return; }

   struct node* s = q->h_link;
   top = front = rear = -1; 
   push(a); enqueue(a);

   while (top > -1) {

     int temp = pop();
     if (temp == -1) { return; }
     printf("%d ", temp);
    
     s = q->h_link;
     while (s != NULL && s->a != temp) { s = s->f_link; }
     if ( s == NULL) { printf("Invalid Vertex!\n"); return; }

     while (s->s_link != NULL) {
        s = s->s_link;
        for (i=0;i<=rear;i++) { if (s->a == Q[i]) { break; } }
        if (i > rear) { push(s->a); enqueue(s->a); }
     }
   }
}

//TO DISPLAY THE GRAPH IN FORM OF ADJAENCY LINKED LIST
void display (struct head* q) {

if (q->h_link == NULL) { printf("Graph Empty!\n"); return; }

struct node*s = q->h_link,*p = s;

while (s != NULL) {
    p = s;
    printf("%d-> ", s->a);
   while (s != NULL) {
    s = s->s_link;
    if (s != NULL) { printf("%d - ",  s->a);}
   } 
   printf("\n");
   s = p;
   s = s->f_link;
}
printf("Vertices: %d\n", q->vertices);
printf("Edges: %d\n\n", q->edges);
}

//TO FREE THE MEMORY ALLOCATION OF FULL GRAPH AUTOMATICALLY
void freegraph (struct head* q) {
    struct node* s = q->h_link,*prev = s;

    while ( prev != NULL) {
        s = s->f_link;
        freelist(prev);
        prev = s;
    }
    free(q);
}


//DRIVER CODE
int main () {

   int a,x;

   struct head* q = (struct head*)malloc(sizeof(struct head));
   q->h_link = NULL; q->vertices = 0; q->edges = 0; 

   while (1) {
    scanf("%d", &x);
    switch (x) 
    {
        case 0 : { freegraph(q); return 0; }
        case 1 : { printf("Enter Vertex Value to Add:"); 
                   scanf("%d", &a);
                   add_vertex(q,a);
                   break;
                 }
        case 2 : { printf("Enter Vertex value to Delete:");
                   scanf("%d", &a);
                   del_vertex(q,a);
                   break;
                 }
        case 3 : { printf("Enter Vertices to Add Edge between them:"); 
                   scanf("%d %d", &a, &x);
                   add_edge(q,a,x);
                   break;
                 }
        case 4 : { printf("Enter Vertices Values to Remove Edge between them:");
                   scanf("%d %d", &a, &x);
                   del_edge(q,a,x);
                   break; 
                 }
        case 5 : { printf("Enter Vertex Value to Check if its present:");
                   scanf("%d", &a);
                   find_vertex(q,a);
                   break;         
                 }
        case 6 : { display(q); break; }
        case 7 : { printf("Enter Value to Start from for BFS:");
                   scanf("%d", &a);
                   breadth_first_search(q,a); 
                   printf("\n");
                   break;
                 }
        case 8 : { printf("Enter Value to Start from for DFS:");
                   scanf("%d", &a);
                   depth_first_search(q,a);
                   printf("\n"); 
                   break;}
        default : break;
    }
   }
    return 0;
}
