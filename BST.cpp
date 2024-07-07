//BINARY SEARCH TREE ADT
#include<bits/stdc++.h>

using namespace std;

class node {
    public:
    int val;
    node *left;
    node *right;
    node() : val(0), left(nullptr), right(nullptr) {}
    node(int x) : val(x), left(nullptr), right(nullptr) {}
    node(int x, node *left, node *right) : val(x), left(left), right(right) {}
};

class Tree {
    public:
    node* root;

    ~Tree () {
        freetree(this->root);
    }

// FUNCTION TO BALANCE BS TREE
    vector<int> BST;
    
    // Helper 1
    void inorder_sp (node* root) {
        if (!root) { return; }
        inorder_sp(root->left);
        BST.push_back(root->val);
        inorder_sp(root->right);
    }
    // Helper 2
    node* balanceorder (int i, int j) {  // Partitions Array Like Merge Sort
         if (i>j) { return nullptr; }
             int mid = (i+j)/2;
             node* root = new node(BST[mid]);
             root->left = balanceorder(i,mid-1);
             root->right = balanceorder(mid+1,j);
             return root;
    }
    // Main Balancer   
    void balanceBST(node* root) {    
        this->inorder_sp(root);
        freetree(this->root);
        this->root = balanceorder(0,BST.size()-1); // Works Similar to Merge Sort 
        BST.clear();         
    }

//FUNCTION TO INSERT VALUES IN BS TREE
void insertnode (int a) {

    if (root == nullptr) { printf("Tree was Destroyed!\n"); return; }

    node* root = this->root;

    struct node* prev = root, *n = (struct node*)malloc(sizeof(struct node));
    n->val = a; n->left = n->right = nullptr;

    while (root != nullptr) {
        if (a >= root->val) { prev = root; root = root->right; }
        else { prev = root; root = root->left; }
    }

    if (a >= prev->val) { prev->right = n; }
    else { prev->left = n; }
}

//FUNCTION TO DELETE GIVEN VALUE IN BS TREE
node* deletenode (struct node* root, int a) {

    struct node* prev = root, *preserved_Root = root;

    if (root == nullptr) { printf("Tree was Destroyed!\n"); return nullptr; }

    if (root->val == a) { 
        if (root->right != nullptr) { preserved_Root = root->right; }
        else { preserved_Root = root->left; }
     }

    while (root != nullptr && root->val != a) {
        if (a >= root->val) { prev = root; root = root->right; }
        else { prev = root; root = root->left; }
    }

    if (root == nullptr) { printf("Given Value Not Found!\n"); }

    else if (root->left == nullptr || root->right == nullptr) {
        if (root->right != nullptr) 
        { 
         if (root->val >= prev->val) { prev->right = root->right; }
         else { prev->left = root->right; }
        }
        else 
        {
         if (root->val >= prev->val) { prev->right = root->left; }
         else { prev->left = root->left; }
        }
        free(root);
    }

    else {
        if (root->val >= prev->val) { prev->right = root->right; prev = prev->right; }
        else { prev->left = root->right; prev = prev->left; }
        
        while ( prev->left != nullptr) { prev = prev->left; }
        prev->left = root->left;
        free(root);
    }
    
    return preserved_Root;
}

//RECURSIVE METHOD TO SEARCH GIVEN VALUE IN TREE
void search_key (node* root, int a) {
    if (root == nullptr) { cout<<"Value Not Present!\n"; return; }
    if (root->val == a) { cout<<"Value Present!\n"; return; }
    else if (root->val < a) { search_key(root->right,a); return; }
    else if (root->val > a) { search_key(root->left,a); return; }
}

//RECURSIVE METHOD TO FREE THE TREE ALLOCATION
void freetree (node* root) {
    if (root == nullptr) { return; }
    freetree(root->left);
    freetree(root->right);
    free(root);
}

//DISPLAY TRAVERSALS (PRE, POST, IN)

// ADVANCED : MORRIS INORDER TRAVERSAL - TC:O(N) , SC:O(1)
/* Intuition Behind Algorithm : 
   
   "Tree is a Directed Acyclic Graph" , hence once you go forward there is no way to come backwards. So, people initially
   came up with idea of remembering the addresses of parent nodes using Recursion and Iterative-Stack Traversals, (Regular Inorder)
   where they memorised all parents and ancestor node addresses to come backwards. (Like Teleporting Backwards!).

   Then, someone named "Morris" thought OUT-OF-BOX. He thought, what if we create "Ways" TO COME BACK TO WHERE WE NEED in a acyclic graph 
   i.e the Tree? and then this algorithm popped up in his mind. Creating "Cycles" TO COME BACK means he creates links to the required ancestor or parent nodes 
   he needs to go from bottom-most ending nodes (Leaf Nodes) to make a valid Inorder Traversal. In this way, he need not to remember all parent 
   and ancestor nodes and thier addresses - Constant Space O(1) and he could traverse through all nodes once using the newly created links.

   Even though the traversal is technically still UNI-directional, we are going back by looping over in a cycle. This algorithm also 
   removes extra links it formed during traversal itself, so that in the end of traversal, the Tree remains unmodified.
   
   Inorder : Left ROOT Right in Every Single Subtree.

*/
void morris_inorder () {

    node* root = this->root;
    node* fallback_from;

    while (root != nullptr) {

        // Always Left Nodes are to Displayed First in Inorder Traversal 
        if (root->left == nullptr) { // If a node doesn't have Left Child , then Next Up is ROOT node.
            cout<<root->val<<" ";    // Show ROOT node Value.
            root = root->right;    // Remaining Node to Explore is ROOT->Right
        }
        
        // If Left Child Exists , then Check which Leaf Node has to FALLBACK to this current ROOT node.
        else {
            fallback_from = root->left;
            
            // Always Inorder of a Subtree of any taken ROOT node Ends with its *Right-Most Leaf* Node.
            while (fallback_from->right != nullptr && fallback_from->right != root) { fallback_from = fallback_from->right; }
            
            // If there was no previous fallback links to ancestors i.e this is first time we came here, 
            if (fallback_from->right == nullptr) { 
                fallback_from->right = root;     // Link it back to Current ROOT , to traverse backwards later on.
                root = root->left;               // Explore Further in Inorder Fashion.
            }

            else {   // If we already came here before, and linked it up, 
                fallback_from->right = nullptr;  // Remove the link, we won't come here again for sure.
                cout<<root->val<<" "; // Show Value
                root = root->right; // Explore Further in Inorder Fashion.
            }
        }
    }
}


// Normal Inorder Traversal - TC:O(N) , SC:O(1)
void inorder (node* root) {
    if (root == nullptr) {return;}
    inorder(root->left);
    cout<<root->val<<" ";
    inorder(root->right);
}


void preorder (node* root) {
    if (root == nullptr) {return;}
    cout<<root->val<<" ";
    preorder(root->left);
    preorder(root->right);
}


void postorder (node* root) {
    if (root == nullptr) {return;}
    postorder(root->left);
    postorder(root->right);
    cout<<root->val<<" ";
}

//FUNCTION TO COUNT NODES
int n = 0;
void countnode (node* root) {
    if (root == nullptr) { return; }
    countnode(root->left);
    countnode(root->right);
    n++;
}

//FUNCTION TO FIND HEIGHT OF TREE
int treeheight (node* root) {
    if (root == nullptr) { return 0; }
    int left = 1 + treeheight(root->left);
    int right = 1 + treeheight(root->right);

    if (left >= right) { return left; }
    else { return right; }  
}
};

//DRIVER CODE
int main () {

int a,x;

Tree* tree = new Tree();
cout<<"Enter Value of First Node:";
cin>>a;
tree->root = new node(a);

while (1) {
    cin>>x;
    switch (x) 
    {
        case 0 : { delete tree; return 0; }
        case 1 : { 
                  cout<<"Enter Value to Insert:";
                  cin>>a;
                  tree->insertnode(a); 
                  break;
                 }  
        case 2 : {
                  cout<<"Enter Value to Delete:";
                  cin>>a;
                  tree->root = tree->deletenode(tree->root,a);
                  break;
                 } 
        case 3 : {
                  if (tree->root == nullptr) { cout<<"Tree was Destroyed!\n"; break; }
                  cout<<"Enter Value to Search:";
                  cin>>a;
                  tree->search_key(tree->root,a);
                  break;
                 }
        case 4 : {
                  if (tree->root == nullptr) { printf("Tree was Destroyed!\n"); break; }
                  cout<<"Morris Inorder:"; tree->morris_inorder(); cout<<"\n";
                  cout<<"Inorder:"; tree->inorder(tree->root); cout<<"\n";
                  cout<<"Preorder:"; tree->preorder(tree->root); cout<<"\n";
                  cout<<"Postorder:"; tree->postorder(tree->root); cout<<"\n";
                  break;
                 }
        case 5 : {
                  tree->countnode(tree->root);
                  cout<<"Total Nodes: "<<tree->n<<"\n"; tree->n=0;
                  break;
                 }
        case 6 : {
                  cout<<"Current Height of Tree: "<<tree->treeheight(tree->root)<<"\n";
                  break;
                 }
        case 7 : {
                  tree->balanceBST(tree->root);
                 }
        default: break; 
    }
}
    return 0;
}