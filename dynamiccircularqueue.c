#include<stdio.h>
#include<stdlib.h>

int i,j;

struct head { int  count; struct node* front,*rear; };
struct node { int a; struct node* link; };

void enqueue (struct head*s, int a) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->a = a;
    if(s->rear == NULL) 
    {
      s->front = p;
      s->rear = p;
      p->link = p;
      s->count++;
    }
    else 
    {
      p->link = s->rear->link;
      s->rear->link = p;
      s->rear = p;
      s->count++;
    }
}

int dequeue (struct head* s) {
    if (s->front == NULL) { printf("Queue Empty!\n"); return -1; }
    int a;
    if (s->front->link == s->front) 
    {
        a = s->front->a;
        free(s->front);
        s->front = NULL;
        s->rear = NULL;
        s->count--;
    }
    else 
    {
        struct node* p = s->front;
        a = p->a;
        s->front = p->link;
        s->rear->link = p->link;
        free(p);
        s->count--;
    }
    return a;
}

void display (struct head* s) {
    if (s->front == NULL) { printf("Queue Empty!\n"); return; }
    struct node* p = s->front;
    do {
        printf("%d ", p->a);
        p = p->link;
    } while ( p != s->front);
    printf("\n");
}

void freequeue (struct head* s) {
    if (s->front == NULL) { free(s); s=NULL; return; }
    struct node* p = s->front, *prev = p;
    do {
        p = p->link;
        free(prev);
        prev = p;
    } while ( prev != s->front);
    free (s); s = NULL; 
}




int main () {
int a,x;
struct head* s = (struct head*)malloc(sizeof(struct head));
s->count = 0; s->front = NULL; s->rear = NULL; 
while (1) {
    scanf("%d", &x);
    switch (x) {
        case 0 : { freequeue(s); return 0;}
        case 1 : { printf("Enter Value To Enqueue:");
                   scanf("%d", &a);
                   enqueue(s,a);
                   display(s);
                   break;
                 }
        case 2 : { a = dequeue(s);
                   if (a != -1) { printf("Removed %d\n", a);}
                   display(s);
                   break;
                 }
        default : break;
    }
}




}