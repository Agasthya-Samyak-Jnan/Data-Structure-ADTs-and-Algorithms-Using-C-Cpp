//STATIC DOUBLE QUEUE
#include<stdio.h>
#include<stdlib.h>

int front = 0, rear = 0, n,i;

void display (int q[]) {
    for(i=front;i<rear;i++){
        printf("%d ", q[i]);
    }
    printf("\n");
}
 
void enqueue_from_front (int q[], int a) {
    if (front <= 0){printf("Queue Overflow!\n"); return;}
    q[--front] = a;
}

int dequeue_from_front (int q[]) {
    if (rear <= front || (rear == 0 && front == 0)){printf("Queue Empty!\n"); rear=0; front=0; return -1;}
    if (front > n-1) {printf("Queue Underflow!\n"); return -1;}
    return q[front++]; }

void enqueue_from_rear (int q[], int a) {
    if(rear > n-1) {printf("Queue Overflow!\n"); return;}
    q[rear++] = a;
}

int dequeue_from_rear (int q[]) {
    if (rear <= front || (rear == 0 && front == 0)){printf("Queue Empty!\n"); rear=0; front=0; return -1;}
    if(rear <= 0){printf("Queue Underflow!\n"); return -1;}
    return q[--rear];
}

int main () {
    int a,x;
    printf("Enter Queue Size:");
    scanf("%d", &n);
    int q[n];
    printf("-0 : EXIT\n-1 : Enqueue\n-2 : Dequeue\n");
    while (1) {
        scanf("%d", &x);
        switch (x) {
            case 0 : { return 0; }
            case 3 : { printf("Enter value to Enqueue:");
                       scanf("%d", &a);
                       enqueue_from_front(q,a); 
                       display(q);
                       break;
                     }
            case 2 : { printf("Removed %d\n",dequeue_from_front(q)); 
                       display(q);
                       break;
                     }
            case 1 : { printf("Enter value to Enqueue:");
                       scanf("%d", &a);
                       enqueue_from_rear(q,a); 
                       display(q);
                       break;
                     } 
            case 4 : { printf("Removed %d\n",dequeue_from_rear(q)); 
                       display(q);
                       break;
                     }
        } 
    }
}