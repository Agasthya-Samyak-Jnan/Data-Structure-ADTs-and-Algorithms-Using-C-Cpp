#include<stdio.h>
#include<limits.h>

typedef struct node {
    int at,bt,ct,tat,wt,rt,id,done;
}process;

void sjfnp (process p[], int n) {

    int et = 0, totaltat = 0, totalwt = 0, totalrt = 0, remaining = n;
    float avgtat = 0, avgwt = 0, avgrt = 0;

    printf("Gantt Chart:\n");
    
    while (remaining) {
        int curr = -1, minbt = INT_MAX;

        // Find Shortest Job First
        for (int i=0;i<n;i++) {
            if (!p[i].done && p[i].at <= et) {
                if (minbt > p[i].bt) { curr = i; minbt = p[i].bt; }
            }
        }
        
        // If a Job was Found, then COMPLETE IT FULLY.
        if (curr != -1) {

            int prev_et = et;
            et += p[curr].bt;
            printf("|(%d) P%d (%d)|", prev_et, p[curr].id, et);

            p[curr].ct = et;
            p[curr].tat = p[curr].ct - p[curr].at;
            p[curr].wt = p[curr].tat - p[curr].bt;
            p[curr].rt = p[curr].wt; // p[curr].rt = prev_et - p[curr].at

            p[curr].done = 1;
            remaining--;

            totalrt += p[curr].rt;
            totaltat += p[curr].tat;
            totalwt += p[curr].wt;

        }
        // If a Job was NOT FOUND yet, stay idle for a second.
        else { printf("|(%d) IDLE (%d)|", et, ++et); }
    }

    printf("\n");
    printf("\n\t - - - PROCESS TABLE - - - \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i=0;i<n;i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id ,p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\n");

    avgtat = (float)totaltat/n;
    avgwt = (float)totalwt/n;
    avgrt = (float)totalrt/n;
    
    printf("\nAverage Turnaround Time: %.2f\n", avgtat);
    printf("Average Waiting Time: %.2f\n", avgwt);
    printf("Average Response Time: %.2f\n", avgrt);

}

void main () {
     
     printf("Enter Number of Processes:");
     int n;
     scanf("%d", &n);
     process p[n];

     printf("\n");
     
     // Take Process Details
     for (int i=0;i<n;i++) {
        printf("Process %d\n", i+1);
        p[i].id = i+1;
        p[i].done = 0;
        printf("Enter AT :");
        scanf("%d", &p[i].at);
        printf("Enter BT :");
        scanf("%d", &p[i].bt);
        printf("\n");
     }
     
     // Sorting Processes by thier Arrival Time to simulate real-life situations.
     for (int i=0;i<n;i++) {
        int swapped = 0;
        for (int j=0;j<n-1-i;j++) {
            if (p[j].bt > p[j+1].bt) {
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
     }
     
     // Peform SHORTEST JOB FIRST SCHEDULING - NON-PREEMPTIVE
     sjfnp(p,n);
}