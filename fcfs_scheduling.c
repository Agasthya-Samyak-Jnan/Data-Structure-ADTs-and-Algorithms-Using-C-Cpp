#include<stdio.h>

// FCFS Process Structure
typedef struct node {
int at,bt,ct,wt,tat,rt,id; }process;

void fcfs (process p[], int n) {

 int totaltat = 0, totalwt = 0, totalrt = 0, et = 0;
 float avgtat = 0, avgrt = 0, avgwt = 0;
 
 // GANTT CHART BUILDER
 printf("\nGantt Chart :\n");
 for (int i=0;i<n;i++) {
    // If Process has arrived to execute
     if (et >= p[i].at) {
        int prev_et = et;
     	et += p[i].bt;
     	printf("|(%d) P%d (%d)|",prev_et, i+1, et);
        p[i].rt = prev_et - p[i].at;
        p[i].ct = et;
     	  p[i].tat = p[i].ct - p[i].at;
     	  p[i].wt = p[i].tat - p[i].bt;

        totaltat += p[i].tat;
        totalrt += p[i].rt;
        totalwt += p[i].wt;
     }
    // If NO Process available to execute
     else {
        printf("|(%d) idle (%d)|", et, et+(p[i].at-et));
        et += (p[i].at-et);
        i--; // VERY IMPORTANT - PROCESS WAS NOT COMPLETED
     }
 }
 printf("\n\n");
 
 // TABLE BUILDER
 printf("- - - PROCESS TABLE - - -\n");
 printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
 for (int i=0;i<n;i++) {
     printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
 }
 printf("\n");

 // FINAL CALCULATIONS
 avgtat = (float)totaltat/n;
 avgwt = (float)totalwt/n;
 avgrt = (float)totalrt/n;

 printf("Average TurnAround Time : %.2f\n", avgtat);
 printf("Average Response Time : %.2f\n", avgtat);
 printf("Average Waiting Time : %.2f\n", avgwt);
  
}

void main () {

printf("Enter Number of Processes:\n");
int n;
scanf("%d", &n);
process p[n];


for (int i=0;i<n;i++) {
p[i].id = i+1;
printf("\nProcess %d:\n", i+1);
printf("Enter AT :");
scanf("%d", &p[i].at);
printf("Enter BT :");
scanf("%d", &p[i].bt);
}

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

fcfs(p,n);

}