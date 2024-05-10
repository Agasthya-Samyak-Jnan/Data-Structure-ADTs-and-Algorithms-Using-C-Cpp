//STATIC PRIORITY QUEUE - DESCENDING ORDER, HIGH NUMBER PRIORITY 
#include<stdio.h>

int rear = -1, n, i;

void display (int q[]) {
    for(i=0;i<=rear;i++) {
        printf("%d ", q[i]);
    }
    printf("\n");
}

void enqueue (int q[], int a) {
   if (rear == n-1) { printf("Queue Overflow!\n"); return; }
   int temp;
   if (rear == -1) { q[0] = a; rear++; return; }
   for (i=0;i<=rear;i++) {
    if (a > q[i]) {continue;}
    else {break;} } 
    for (temp = rear; temp>=i; temp--) {
        q[temp+1] = q[temp];
    }
    q[i] = a;
    rear++;
}

int dequeue (int q[]) {
    if(rear == -1) { printf("Queue Empty!\n"); return -1; }
    return q[rear--];
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
            case 1 : {printf("Enter Value to Enqueue:");
                      scanf("%d", &a);
                      enqueue(q,a);
                      display(q);
                      break;
                     }
            case 2 : {a = dequeue(q);
                      if(a != -1){ printf("Removed %d\n", a); }
                      display(q);
                      break;
                     }
            default : break;
        }
    }
}