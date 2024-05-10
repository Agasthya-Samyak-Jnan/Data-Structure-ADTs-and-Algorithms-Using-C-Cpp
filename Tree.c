// PROGRAM FOR BFS,DFS,PRE-IN-POST ORDER TRAVERSALS FOR STRICT BINARY TREE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


// TREE DEFINITIONS AND UTILITIES

struct node {
    int a;
    struct node* left;
    struct node* right; 
};

struct node* createtree (int a) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->a = a;
    p->left = p->right = NULL; 
    return p;
}

void addnode (struct node* root , int a, bool drn) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->a = a;
    p->left = p->right = NULL;
    if (!drn) { root->left = p; }
    else { root->right = p; }
}

void preorder (struct node* root) {
    if (root == NULL) {return;}
    printf("%d ", root->a);
    preorder (root->left);
    preorder (root->right);
}

void inorder (struct node* root) {
    if (root == NULL) {return;}
    inorder (root->left);
    printf("%d ", root->a);
    inorder (root->right);
}

void postorder (struct node* root) {
    if (root == NULL) {return;} 
    postorder (root->left);
    postorder (root->right);
    printf("%d ", root->a);
}

void freetree (struct node* root) {
    if (root == NULL) { return; }
    freetree(root->left);
    freetree(root->right);
    free(root); 
    root =NULL;
}

//QUEUE UTILITIES FOR BREADTH-FIRST SEARCH

struct node*  q[50] = {} ;
int rear = -1, front = -1;

void enqueue (struct node* a) {
    if (rear >= 49) { printf("Queue Full!\n"); return; }
    q[++rear] = a;
}

struct node* dequeue () {
    if ( front >= rear ) { printf("Queue Empty!\n"); return 0; }
    return q[++front];
}

//BREADTH-FIRST SEARCH

void breadth_first_search (struct node* root) {

  q[++rear] = root;
  printf("%d ", root->a);

  while (rear > front) 
  {
    root = dequeue();

    if (root != NULL) 
    { 
    if (root->left != NULL) { printf("%d ", root->left->a); }
    if (root->right != NULL) { printf("%d ", root->right->a); }

    if (root->left != NULL) { enqueue (root->left); }
    if (root->right != NULL) { enqueue (root->right); }
    }
    
  }

}

//STACK UTILITIES FOR DEPTH-FIRST SEARCH 
struct node* s[50] = {};
int top = -1;

void push (struct node* a) {
     if (top > 49) { printf("Stack Overflow!\n"); return; }
     s[++top] = a;
}

struct node* pop () {
    if (top <= -1) { printf("Stack Underflow!\n"); return 0; }
    return s[top--];
}

//DEPTH-FIRST SEARCH

void depth_first_search (struct node* root) {

push(root);

while (top > -1) 
{
   root = pop(); 

   if (root != NULL) 
   {
     printf("%d ", root->a);
     if (root->right != NULL) { push(root->right); }
     if (root->left != NULL) { push(root->left); }
   }
}
}

int main () {

int a,x;
int q[50] = {};

//DRAW THE TREE FOR BETTER UNDERSTANDING 
// LAST PARAMETER IN addnode FUNCTION , 0 = Left, 1 = Right
struct node* root = createtree(1);
addnode(root,2,0);
addnode(root->left,3,0);
addnode(root->left->left,4,0);
addnode(root->left->left->left,5,0);
addnode(root->left,6,1);
addnode(root->left->right,7,0);
addnode(root->left->right->left,8,0);
addnode(root->left->right,9,1);
addnode(root,10,1);

while (1) {
    scanf("%d", &x);
    switch (x) {
        case 0 : { freetree(root); return 0; }
        case 1 : { printf("Preorder: ");  preorder(root); printf("\n");  break; }
        case 2 : { printf("Inorder: ");   inorder(root);  printf("\n");  break; }
        case 3 : { printf("Postorder: "); postorder(root); printf("\n"); break; }
        case 4 : { printf("Breadth-First Search: "); breadth_first_search(root); printf("\n"); break; }
        case 5 : { printf("Depth-First Search: "); depth_first_search(root); printf("\n"); break; }
        default : break;
    }
}

}

