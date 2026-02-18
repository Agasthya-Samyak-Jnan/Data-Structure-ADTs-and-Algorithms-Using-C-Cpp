#include<stdio.h>
#include<limits.h>

typedef struct node {
    int at,bt,ct,tat,wt,rt,id,remt;
}process;

void sjfp (process p[], int n) {
    int et = 0, totaltat = 0, totalwt = 0, totalrt = 0, remaining = n;
    float avgtat = 0, avgwt = 0, avgrt = 0;

    printf("Gantt Chart: \n");

    while (remaining) {

        int curr = -1, minbt = INT_MAX;
        // Find Shortest Remaining Time Job First
        for (int i=0;i<n;i++) {
            if (p[i].remt && p[i].at <= et) {
                if (minbt > p[i].remt) { curr = i; minbt = p[i].remt; }
            }
        }

        et++;

        if (curr != -1) {

            if (p[curr].remt == p[curr].bt) { p[curr].rt = et - p[curr].at; }

            p[curr].remt--;
            printf("| P%d (%d) ", p[curr].id, et);

            if (p[curr].remt == 0) {
                
                p[curr].ct = et;
                p[curr].tat = p[curr].ct - p[curr].at;
                p[curr].wt = p[curr].tat - p[curr].bt;
                
                totaltat += p[curr].tat;
                totalwt += p[curr].wt;
                totalrt += p[curr].rt;
                
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

    printf("Enter Number of Processes:");
    int n;
    scanf("%d", &n);
    process p[n];

    printf("\n");

    for (int i=0;i<n;i++) {
        printf("Process %d\n", i+1);
        p[i].id = i+1;
        printf("Enter AT:");
        scanf("%d", &p[i].at);
        printf("Enter BT:");
        scanf("%d", &p[i].bt);
        p[i].remt = p[i].bt;
        printf("\n");
    }

    for (int i=0;i<n;i++) {
        for (int j=0;j<n-1-i;j++) {
            if (p[j].at > p[j+1].at) {
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    sjfp(p,n);

    return 0;
}