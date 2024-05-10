//STACK USING STRUCTURES-LINKED LIST (DYNAMIC)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct head {
    int count;
    struct node* top;
};

struct node {
    int a;
    struct node* link;
};

bool push (struct head* s) {
    int a;
    printf("Enter Value to Push:");
    scanf("%d", &a);
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if(p==NULL){printf("Allocation Failed!\n"); return false;}
    p->a = a;
    p->link = s->top;
    s->top = p;
    s->count++;
    return true;
}

int pop (struct head* s) {
    if(s->top == NULL){printf("Cannot Pop, Stack Underflow! (EMPTY)\n"); return -1;} 
    struct node* temp = s->top;
    int a = temp->a; 
    s->top = s->top->link;
    free(temp);
    s->count--;       
    return a;
}

void display (struct head* s) {
    struct node* p = s->top;
    while (p != NULL) {
        printf("%d ", p->a);
        p = p->link;
    }
    printf(" (%d)\n", s->count);
}

void freestack (struct head* s) {
    struct node* p = s->top,*prev = NULL;
    while (prev != NULL){
       prev = p;
       p = p->link;
       free(prev);
    }
    free(s); s = NULL;
}

int main () {

int x;
struct head* s = (struct head*)malloc(sizeof(struct head));
s->count = 0; s->top = NULL;

while (1){
    scanf("%d", &x);
    switch (x) {
        case 0: { freestack(s); return 0; }
        case 1: { display(s); break; }
        case 2: { if(push(s)){display(s);}
                  else{printf("Allocation Failed!\n");}
                  break;
                }
        case 3: { x = pop(s);
                  if(x != -1){printf("Popped %d -\n", x); display(s);}
                  break;
                }
        default: break;
    }
}
}