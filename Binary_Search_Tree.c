//BINARY SEARCH TREE ADT
#include<stdio.h>
#include<stdlib.h>

struct node {
    int a;
    struct node* right, * left; 
};

//FUNCTION TO INSERT VALUES IN BS TREE
void insertnode (struct node* root, int a) {

    if (root == NULL) { printf("Tree was Destoryed!\n"); return; }

    struct node* prev = root, *n = (struct node*)malloc(sizeof(struct node));
    n->a = a; n->left= n->right = NULL;

    while (root != NULL) {
        if (a >= root->a) { prev = root; root = root->right; }
        else { prev = root; root = root->left; }
    }

    if (a >= prev->a) { prev->right = n; }
    else { prev->left = n; }
}

//FUNCTION TO DELETE GIVEN VALUE IN BS TREE
struct node* deletenode (struct node* root, int a) {

    struct node* prev = root, *preserved_Root = root;

    if (root == NULL) { printf("Tree was Destoryed!\n"); return NULL; }

    if (root->a == a) { 
        if (root->right != NULL) { preserved_Root = root->right; }
        else { preserved_Root = root->left; }
     }

    while (root != NULL && root->a != a) {
        if (a >= root->a) { prev = root; root = root->right; }
        else { prev = root; root = root->left; }
    }

    if (root == NULL) { printf("Given Value Not Found!\n"); }

    else if (root->left == NULL || root->right == NULL) {
        if (root->right != NULL) 
        { 
         if (root->a >= prev->a) { prev->right = root->right; }
         else { prev->left = root->right; }
        }
        else 
        {
         if (root->a >= prev->a) { prev->right = root->left; }
         else { prev->left = root->left; }
        }
        free(root);
    }

    else {
        if (root->a >= prev->a) { prev->right = root->right; prev = prev->right; }
        else { prev->left = root->right; prev = prev->left; }
        
        while ( prev->left != NULL) { prev = prev->left; }
        prev->left = root->left;
        free(root);
    }
    
    return preserved_Root;
}

//RECURSIVE METHOD TO SEARCH GIVEN VALUE IN TREE
void search_key (struct node* root, int a) {
    if (root == NULL) { printf("Value Not Present!\n"); return; }
    if (root->a == a) { printf("Value Present!\n"); return; }
    else if (root->a < a) { search_key(root->right,a); return; }
    else if (root->a > a) { search_key(root->left,a); return; }
}

//RECURSIVE METHOD TO FREE THE TREE ALLOCATION
void freetree (struct node* root) {
    if (root == NULL) { return; }
    freetree(root->left);
    freetree(root->right);
    free(root);
}

//DISPLAY TRAVERSALS (PRE, POST, IN)
void inorder (struct node* root) {
    if (root == NULL) {return;}
    inorder(root->left);
    printf("%d ", root->a);
    inorder(root->right);
}


void preorder (struct node* root) {
    if (root == NULL) {return;}
    printf("%d ", root->a);
    preorder(root->left);
    preorder(root->right);
}


void postorder (struct node* root) {
    if (root == NULL) {return;}
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->a);
}

//FUNCTION TO COUNT NODES
int n = 0;
void countnode (struct node* root) {
    if (root == NULL) { return; }
    countnode(root->left);
    countnode(root->right);
    n++;
}

//FUNCTION TO FIND HEIGHT OF TREE
int treeheight (struct node* root) {
    if (root == NULL) { return 0; }
    int left = 1 + treeheight(root->left);
    int right = 1 + treeheight(root->right);

    if (left >= right) { return left; }
    else { return right; }  
}


//DRIVER CODE
int main () {

int a,x;

struct node* root = (struct node*)malloc(sizeof(struct node));
printf("Enter Value of First Node:");
scanf("%d", &a); 
root->a = a; root->left = root->right = NULL;

while (1) {
    scanf("%d", &x);
    switch (x) 
    {
        case 0 : { freetree(root); return 0; }
        case 1 : { 
                  printf("Enter Value to Insert:");
                  scanf("%d", &a);
                  insertnode(root,a); 
                  break;
                 }  
        case 2 : {
                  printf("Enter Value to Delete:");
                  scanf("%d", &a);
                  root = deletenode(root,a);
                  break;
                 } 
        case 3 : {
                  if (root == NULL) { printf("Tree was Destroyed!\n"); break; }
                  printf("Enter Value to Search:");
                  scanf("%d", &a);
                  search_key(root,a);
                  break;
                 }
        case 4 : {
                  if (root == NULL) { printf("Tree was Destroyed!\n"); break; }
                  printf("Inorder:"); inorder(root); printf("\n");
                  printf("Preorder:"); preorder(root); printf("\n");
                  printf("Postorder:"); postorder(root); printf("\n");
                  break;
                 }
        case 5 : {
                  countnode(root);
                  printf("Total Nodes: %d\n", n); n=0;
                  break;
                 }
        case 6 : {
                  printf("Current Height of Tree: %d\n", treeheight(root));
                  break;
                 }
        default: break; 
    }
}

    return 0;
}