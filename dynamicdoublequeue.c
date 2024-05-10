//DYNAMIC DOUBLE QUEUE
#include<stdio.h>
#include<stdlib.h>

int i,j;

struct head { int count; struct node* front,*rear; };
struct node { int a; struct node* link; };

void enqueue_front (struct head* s, int a) {
    struct node*  p = (struct node*)malloc(sizeof(struct node));
    p->a = a;
    if (s->front == NULL) { s->front = p; s->rear = p; p->link = NULL;}
    p->link = s->front;
    s->front = p;
}

int dequeue_front (struct head* s) {
    if (s->front == NULL){ printf("Queue Empty!\n"); return -1; }
    struct node* p  = s->front;
    int a = p->a;
    s->front = s->front->link;
    free(p);
    return a;
}

void enqueue_rear (struct head* s, int a) {
    struct node*  p = (struct node*)malloc(sizeof(struct node));
    p->a = a;
    if (s->front == NULL) { s->front = p; s->rear = p; p->link = NULL;}
    else 
    {
    p->link = NULL;
    s->rear->link = p;
    s->rear = p;
    }
}

int dequeue_rear (struct head* s) {
    if (s->front == NULL){ printf("Queue Empty!\n"); return -1; }
    int a;
    if (s->front->link == NULL) { a = s->front->a; free(s->front); s->front = NULL;} 
    else 
    {
     struct node* p = s->front;
     while (p->link->link != NULL) {p = p->link;}
     a = p->link->a;
     free(p->link);
     p->link = NULL;
     s->rear = p;
    }
    return a;
}


void display (struct head* s) {
    if (s->front == NULL){ printf("Queue Empty!\n"); return; }
    struct node* p = s->front;
    while (p != NULL) {
        printf("%d ", p->a);
        p = p->link;
    }
    printf("\n");
}

void freequeue (struct head* s) {
     if (s->front == NULL){ free(s); s=NULL; return; }
     struct node* p = s->front, * prev = p;
     while (prev != NULL) {
        p = p->link;
        free(prev);
        prev = p;
     }
     free(s); s= NULL; 
}

int main () {
    int a,x;
    struct head* s = (struct head*)malloc(sizeof(struct head));
    s->count = 0; s->rear  = NULL; s->front = NULL;
    while (1) {
        scanf("%d", &x);
        switch (x) {
            case 0 : { freequeue(s); return 0; }
            case 1 : {
                       printf("Enter Value to Enqueue:");
                       scanf("%d", &a);
                       enqueue_rear(s,a);
                       display(s);
                       break;
                     }
            case 2 : {
                       a = dequeue_front(s);
                       if ( a!= -1) { printf("Removed %d\n", a); }
                       display(s);
                       break;
                     } 
            case 3 : {
                       printf("Enter Value to Enqueue:");
                       scanf("%d", &a);
                       enqueue_front(s,a);
                       display(s);
                       break;
                     }
            case 4 : {
                       a = dequeue_rear(s);
                       if ( a!= -1) { printf("Removed %d\n", a); }
                       display(s);
                       break;
                     } 
            default : break;
        }
    }
}