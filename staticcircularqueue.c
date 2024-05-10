//STATIC CIRCULAR QUEUE
#include<stdio.h> 
#include<stdbool.h>

int n, front = -1, rear = -1, i;
bool overflow = 0;

void display (int q[]) {
    if (front == -1 && rear == -1) { printf("Queue Empty!\n"); return; }
    for (i = front+1; i <= rear ; i++) {
        if(i == -1 || i == n) { i = 0; }
        printf("%d ", q[i]);
    }
    printf("\n");
}


void enqueue (int q[], int a) {
    if (front == -1 && rear == -1) {q[++rear] = a; return; }
    if (front == rear || (rear == n-1 && front == -1)) { overflow = true; printf("Queue Overflow!\n"); return; }
    if (rear == front-1) { overflow = true; }
    if (rear >= n-1) {rear = -1;}
    q[++rear] = a;
}

int dequeue (int q[]) {
    if (front == -1 && rear == -1) { printf("Queue Empty!\n"); return -1; }
    if (front == rear && !overflow ) { printf("Queue Underflow!\n"); front = -1; rear = -1; return -1; }
    if (front == n-1) { front = -1; }
    if (overflow) { overflow = false; }
    return q[++front];

}

int main () {
   int a,x;
   printf("Enter Queue Size:");
   scanf("%d", &n);
   int q[n];
   while (1) {
    scanf("%d", &x);
    switch (x) {
        case 0 : {return 0;}
        case 1 : {
                  printf("Enter Value to Enqueue:");
                  scanf("%d", &a);
                  enqueue(q,a);
                  display(q);
                  break;
                 }
        case 2 : { a = dequeue(q);
                   if (a != -1){printf("Removed %d\n", a);}
                   display(q);
                   break;
                 }
        default :{break;}
    }
   }
}