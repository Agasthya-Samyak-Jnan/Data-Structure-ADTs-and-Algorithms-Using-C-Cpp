//STATIC NORMAL QUEUE
#include<stdio.h>
#include<stdlib.h>

int front = 0, rear = -1, n,i;

void display (int q[]) {
    for(i=front;i<rear;i++){
        printf("%d ", q[i]);
    }
    printf("\n");
}

void enqueue (int q[], int a){
    if (rear >= n-1){printf("Queue Overflow!\n"); return;}
    q[++rear] = a;
    display(q);
}

int dequeue (int q[]) {
    if (front > n-1 || front > rear) {printf("Queue Underflow!\n"); return -1;}
    display(q);
    return q[front++];

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
            case 1 : { printf("Enter value to Enqueue:");
                       scanf("%d", &a);
                       enqueue(q,a); 
                       break;
                     }
            case 2 : { printf("Removed %d\n",dequeue(q)); 
                       break;
                     }
        } 
    }
}