//DYNAMIC NORMAL QUEUE
#include<stdio.h>
#include<stdlib.h>

struct head  {
    int count; 
    struct node* rear,* front; };

struct node {
    int a; 
    struct node* link; };

void display (struct head* s) {
    if (s->front == NULL) {printf("Queue Empty!\n"); return;}
    struct node* p = s->front;
    while (p != NULL) {
        printf("%d ", p->a);
        p = p->link;
    }
    printf("\n");
}

void enqueue (struct head* s, int a) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if(s->rear == NULL) {s->rear = p;}
    p->link = s->front;
    s->front = p;
    p->a = a;
    s->count++;
    display(s);
}

int dequeue (struct head* s) {
    if (s->front == NULL) {printf("Queue Underflow!\n"); return -1;}
    struct node* c = s->front, *p = c;
    while (c->link != NULL){
        p = c;
        c = c->link;
    }
    int a = c->a;
    free(c);
    if (s->front == c){s->front = NULL;}
    else 
    { 
      p->link = NULL;
      s->rear = p;
      s->count--;
    }
    display(s);
    return a;
}

void freequeue (struct head* s) {
    if (s->rear == NULL) {free(s); s =NULL; return;}
    struct node* p = s->front, * prev=p;
    while (prev != NULL)
    {
      p = p->link;
      free(prev);
      prev = p;
    }
    free(s); s = NULL;
}

int main () {
    int a,x;
    struct head* s = (struct head*) malloc (sizeof(struct head));
    s->front = NULL; s->rear = NULL;s->count = 0;
    printf("-0 : EXIT\n-1 : Enqueue\n-2 : Dequeue\n");
    while (1) {
        scanf("%d", &x);
        switch (x) {
            case 0 : { freequeue(s); return 0; }
            case 1 : { printf("Enter value to Enqueue:");
                       scanf("%d", &x);
                       enqueue(s,x); 
                       break;
                     }
            case 2 : { printf("Removed %d\n",dequeue(s)); 
                       break;
                     }
        } 
    }
}