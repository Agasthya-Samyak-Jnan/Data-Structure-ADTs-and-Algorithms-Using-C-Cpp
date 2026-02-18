#include<stdio.h>
#include<limits.h>

typedef struct node {
    int at,bt,ct,tat,wt,rt,priority,id,remt;
}process;

void pp (process p[], int n) {

    int et = 0, totaltat = 0, totalwt = 0, totalrt = 0, remaining = n;
    float avgtat = 0, avgwt = 0, avgrt = 0;
    
    printf("Gantt Chart: \n");

    while (remaining) {
        
        // Check every milisecond if Higher Priority Process has arrived or not. Preemption Occurs Here.
        int curr = -1, minpriority = INT_MAX;
        for (int i=0;i<n;i++) {
            if (p[i].remt > 0 && p[i].at <= et) {
                if (minpriority > p[i].priority || (minpriority == p[i].priority && p[i].at < p[curr].at)) { 
                    minpriority = p[i].priority; curr = i; 
                }
            }
        }
        
        // "Time and Tide Waits for none." - it keeps elapsing one second at a time :)
        et++;
        
        // If a Higher Priority Process or any process found,
        if (curr != -1) {

            if (p[curr].remt == p[curr].bt) { p[curr].rt = et - p[curr].at; }

            p[curr].remt--;
            printf("| P%d (%d) ", p[curr].id, et);

            if (p[curr].remt == 0) {

                p[curr].ct = et;
                p[curr].tat  = p[curr].ct - p[curr].at;
                p[curr].wt = p[curr].tat - p[curr].bt;

                totalrt += p[curr].rt;
                totaltat += p[curr].tat;
                totalwt += p[curr].wt;
                    
                remaining--;
            }
        }  
        else { printf("| IDLE (%d) ", et); }   
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
        p[i].remt = p[i].bt;
        printf("\n");
    }

    pp(p,n);

    return 0;
}