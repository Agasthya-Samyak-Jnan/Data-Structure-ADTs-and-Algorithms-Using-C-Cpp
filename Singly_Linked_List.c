#include<stdio.h>
#include<stdlib.h>

int i,j;

struct head {
    int count;
    struct node* h_link;
};

struct node {
    int a;
    struct node* link;
};

struct node* newloc () {
    struct node*p = (struct node*)malloc(sizeof(struct node));
    return p;
}

//Create the List
void createlist(struct head** q) {
    int z;
    printf("Enter value to put to 1st node:");
    scanf("%d", &z);
    *q = (struct head*)malloc(sizeof(struct head));
    struct node *p = newloc();
    (*q)->h_link = p;
    (*q)->count = 1;
     p->a = z;
     p->link = NULL;
}

//Insert by Position
void ins_pos(struct head** q, int pos, int z) {
    
    struct node *s = (*q)->h_link;
    struct node* p = newloc();
    if (pos == 1) 
    {
        p->link = s;
        p->a = z;
        (*q)->h_link = p;
        (*q)->count++;
        return;
    }

    int i = 1;
    while (i < pos - 1) 
    {
        if (s->link == NULL) { break; }
        s = s->link;
        i++;
    }

    if (s->link != NULL) 
    {
        p->link = s->link;
        s->link = p;
        p->a = z;
        (*q)->count++;
        return;
    }
    else 
    {
        s->link = p;
        p->a = z;
        p->link = NULL;
        (*q)->count++;
        return;
    }
}

//Delete by Position
void del_pos(struct head** q, int pos) {
   
    if ((*q)->h_link == NULL) 
      {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
      }

    if ((*q)->count < pos) 
      {
        printf("Invalid Position! Try Again!\n");
        return;
      }

    struct node* p = (*q)->h_link;
    struct node* s;
    if (pos == 1) {
        s = p->link;
        free(p);
        (*q)->h_link = s;
        (*q)->count--;
        return;
    }
     i = 1;
    while (i < pos - 1) {
        p = p->link;
        i++;
    }
    if (p->link->link != NULL) 
    {
        s = p->link;
        s = s->link;
        free(p->link);
        p->link = s;
        (*q)->count--;
    }
    else 
    {
        free(p->link);
        p->link = NULL;
        (*q)->count--;
    }
}

//Delete by Key
void del_key(struct head** q) {

    if ((*q)->h_link == NULL) 
    {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
    }

    int key;
    printf("Enter Key value to delete:");
    scanf("%d", &key);
    struct node* p = (*q)->h_link;
    struct node* s;
     i = 1;
    while (p != NULL) 
    {
        if (p->a == key) { break; }
        p = p->link;
        i++;
    }
    if (p == NULL) {
        printf("Key Value not Present!\n");
        return;
    }
    del_pos(q, i);
}

//Search by Key
void search_key(struct head* q) {

    if ((q)->h_link == NULL) 
       {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
       }

    int key;
    printf("Enter Key value to search:");
    scanf("%d", &key);
    struct node* p = q->h_link;
    int i = 1;
    while (p->a != key) 
    {
        if (p->link == NULL) {
            printf("Key value not present in list!\n");
            break;
        }
        p = p->link;
        i++;
    }
    if (p->a == key) { printf("Key %d is at %d position.\n", p->a, i); }
}

//Create a Ordered List
void orderedlist (struct head** q, struct head** t) {

if ((*q)->h_link == NULL) 
       {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
       }


*t = (struct head*)malloc(sizeof(struct head));
struct node* u = newloc();
struct node* s = (*q)->h_link;
(*t)->count = (*q)->count;
(*t)->h_link = u;
u->a = s->a;
u->link = NULL;
s = s->link;
struct node* prev, *newnode;

while (s != NULL) 
 {   
    u = (*t)->h_link;
    if (s->a < (*t)->h_link->a) 
    {
        newnode = newloc();
        newnode->a = s->a;
        newnode->link = u;
        (*t)->h_link = newnode;
        u = newnode;
        s = s->link;
    }

    else 
    { 
     prev = u;
     while (u != NULL )
       {  
        if(s->a > u->a) 
        {
         prev = u;
         u = u->link;
         continue;
        }
        break;
       }
     newnode = newloc();
     newnode->link = u;
     prev->link = newnode;
     newnode->a = s->a;
     s = s->link;
    }
 }
}

//Reverse the List
void reverselist(struct head** q) {

    if ((*q)->h_link == NULL) 
       {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
       }

    struct node* prev = NULL, *current = (*q)->h_link, *next = NULL;
    while (current != NULL) 
    {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }
    (*q)->h_link = prev;
}

//Copy the List
void copylist (struct head** q, struct head** s) {  

    if ((*q)->h_link == NULL) 
      {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
      }

   *s = (struct head*)malloc(sizeof(struct head));  
   struct node* p = newloc();
   struct node* x = (*q)->h_link;
   (*s)->h_link = p;
   struct node* y = (*s)->h_link;
   (*s)->count = 1;

   while (x->link != NULL) 
   { 
     p = newloc();
     y->a = x->a;
     y->link = p;
     x = x->link;
     y = y->link;
     (*s)->count++;
   }
    p->a = x->a ;
    y->link = NULL;
}

//Display the List
void display(struct head* q) {

    if ((q)->h_link == NULL) 
      {
        printf("List is Empty! Please insert nodes to continue (Press 3)!\n");
        return;
      }

    struct node* p = q->h_link;
    while (p->link != NULL) 
    {
        printf("%d ", p->a);
        p = p->link;
    }
    printf("%d \n", p->a);
}

//Free the Whole List
void freelist(struct head** q) {
    struct node* current = (*q)->h_link, *next = current->link;
    while (current != NULL) 
    {
        free(current);
        current = next;
        next = next->link;
    }
    free(*q);
    *q = NULL; 
}

//DRIVER CODE
int main() {
    int pos, z,x;
    struct head* q, *t, *s;

    printf("- 0 : EXIT.\n");
    printf("- 1 : Create List\n");
    printf("- 2 : Display List\n");
    printf("- 3 : Insert By Position\n");
    printf("- 4 : Delete By Position\n");
    printf("- 5 : Delete By Key\n");
    printf("- 6 : Search By Key\n");
    printf("- 7 : Reverse the List\n");
    printf("- 8 : Create Ordered List\n");
    printf("- 9 : Create a Copy of List\n");
//MENU
    while (1) {
        scanf("%d", &x);
        switch (x) {
        case 0: { 
                  freelist(&q); 
                  freelist(&s); 
                  freelist(&t); 
                  return 0; 
                }
        case 1: { createlist(&q); break; }
        case 2: { display(q); break; }
        case 3: { 
                  printf("Enter the position and value to insert:");
                  scanf("%d %d", &pos, &z);
                  ins_pos(&q,pos,z); 
                  break; 
                }
        case 4: {
                  printf("Enter Node Position to delete:");
                  scanf("%d", &pos);
                  del_pos(&q, pos); break;
                }
        case 5: { del_key(&q); break; }
        case 6: { search_key(q); break; }
        case 7: { reverselist(&q); break; }
        case 8: { 
                  orderedlist(&q, &t); 
                  display(t);
                  break; 
                }
        case 9: { 
                  copylist(&q, &s);
                  display(s);
                  break; 
                }
        default : { break; }
        }
    }                
    return 0;
}



