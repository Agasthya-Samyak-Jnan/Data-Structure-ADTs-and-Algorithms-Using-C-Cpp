#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

typedef struct node {
    int at,bt,ct,tat,wt,rt,id,remt,arrived;
}process; 

int* q, front = -1, rear = -1, n, inq = 0;

void push (int id) {
    front = (front+1)%n;
    q[front] = id;
    inq++;
}

int pop () {
    inq--;
    rear = (rear+1)%n;
    return q[rear];
}

// int empty () {
//     return inq == 0 ? 1 : 0;
// }

void rr (process p[], int n, int tq) {

    int et = 0, totaltat = 0, totalrt = 0, totalwt = 0, remaining = n;
    float avgtat = 0, avgwt = 0, avgrt = 0;

    printf("\n Gantt Chart : \n");
    printf("(0) ");

    push(0);
    p[0].arrived = 1;
    // // 
    while (remaining) {
        
        int curr = pop();

        if (p[curr].at > et) { push(curr); curr = -1; }
        
        if (curr != -1) {

            if (p[curr].remt == p[curr].bt) { p[curr].rt = et - p[curr].at; }
            
            if (p[curr].remt >= tq) { et += tq; p[curr].remt -= tq; }
            else { et += p[curr].remt; p[curr].remt = 0; }

            printf("P%d (%d) ", p[curr].id, et);

            for (int i=0;i<n;i++) {
                if (!p[i].arrived && p[i].at <= et) { push(i); p[i].arrived = 1; }
            }

            if (p[curr].remt == 0) {

                p[curr].ct = et;
                p[curr].tat = p[curr].ct - p[curr].at;
                p[curr].wt = p[curr].tat - p[curr].bt;

                totaltat += p[curr].tat;
                totalwt += p[curr].wt;
                totalrt += p[curr].rt;

                remaining--;
            }

            else { push(curr); }
        }
        else { printf("IDLE (%d) ", ++et); }   
    }

    // // 

    printf("\n\n\t - - - PROCESS TABLE - - - \n\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i=0;i<n;i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

    avgtat = (float)totaltat/n;
    avgrt = (float)totalrt/n;
    avgwt = (float)totalwt/n;

    printf("\nAverage Turnaround Time : %.2f\n", avgtat);
    printf("Average Waiting Time : %.2f\n", avgwt);
    printf("Average Response Time : %.2f\n", avgrt);

}

int main () {

    printf("Enter Number of Processes:");
    scanf("%d", &n);

    process p[n];
    q = (int*)calloc(n,sizeof(int));

    printf("\n");
    for (int i=0;i<n;i++) {
        printf("Process %d :\n", i+1);
        printf("Enter AT : ");
        scanf("%d", &p[i].at);
        printf("Enter BT : ");
        scanf("%d", &p[i].bt);
        p[i].id = i+1;
        p[i].remt = p[i].bt;
        p[i].arrived = 0;
        printf("\n");
    }

    printf("\nEnter Time Quantum Per Process : ");
    int tq;
    scanf("%d", &tq);
    
    // Sort by Arrival Time - Realistic Scenario
    for (int i=0;i<n;i++) {
        int swapped = 0;
        for (int j=0;j<n-1-i;j++) {
            if (p[j].at > p[j+1].at) {
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) { break; }
    }
    
    // Round-Robin Scheduling
    rr(p,n,tq);

    return 0;
}