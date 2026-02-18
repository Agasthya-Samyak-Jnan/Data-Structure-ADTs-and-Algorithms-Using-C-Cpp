#include<stdio.h>
#include<limits.h>

typedef struct node {
    int at,bt,ct,tat,wt,rt,priority,id,done;
}process;

void pnp (process p[], int n) {
    int et = 0, totaltat = 0, totalwt = 0, totalrt = 0, remaining = n;
    float avgtat = 0, avgwt = 0, avgrt = 0;

    printf("Gantt Chart: \n");

    while (remaining) {

        int curr = -1, minpriority = INT_MAX;
        for (int i=0;i<n;i++) {
            if (!p[i].done && p[i].at <= et) {
                if (minpriority > p[i].priority) { minpriority = p[i].priority; curr = i; }
            }
        }

        if (curr != -1) {
            int prev_et = et;
            et += p[curr].bt;
            printf("|(%d) P%d (%d)|", prev_et, p[curr].id, et);

            p[curr].ct = et;
            p[curr].tat = p[curr].ct - p[curr].at;
            p[curr].wt = p[curr].tat - p[curr].bt;
            p[curr].rt = p[curr].wt;
            
            totaltat += p[curr].tat;
            totalrt += p[curr].rt;
            totalwt += p[curr].wt;

            p[curr].done = 1;
            remaining--;
        }
        else { printf("|(%d) IDLE (%d)|", et, ++et); }
        
    }
    
    printf("\n\n\t - - - PROCESS TABLE - - - \n");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i=0;i<n;i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    avgtat = (float)totaltat/n;
    avgwt = (float)totalwt/n;
    avgrt = (float)totalrt/n;
  
    printf("\nAverage Turnaround Time : %.2f\n", avgtat);
    printf("Average Waiting Time : %.2f\n", avgwt);
    printf("Average Response Time : %.2f\n", avgrt);
}

int main () {

    printf("Enter Number of Processes: ");
    int n;
    scanf("%d", &n);
    process p[n];

    printf("\n - Low Number = High Priority - \n");

    for (int i=0;i<n;i++) {
        printf("Process %d\n", i+1);
        p[i].id = i+1;
        printf("Enter AT:");
        scanf("%d", &p[i].at);
        printf("Enter BT:");
        scanf("%d", &p[i].bt);
        printf("Enter PRIORITY:");
        scanf("%d", &p[i].priority);
        p[i].done = 0;
        printf("\n");
    }

    pnp(p,n);

    return 0;
}