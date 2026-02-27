#include <stdio.h>

struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main(void){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // Taking input
    for(int i = 0; i < n; i++){
        printf("\nProcess %d\n", i+1);
        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);  
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    // Sort by Arrival Time (FCFS rule) - CORRECTED
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(p[j].at > p[j+1].at){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int currenttime = 0;
    float totalwt = 0;

    for(int i = 0; i < n; i++){

        if(currenttime < p[i].at){ //meaning cpu is idle
            currenttime = p[i].at;   
        }
        //in fcfs start time = current time
        p[i].ct = currenttime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        currenttime = p[i].ct;
        totalwt += p[i].wt;
    }

    float avgwt = totalwt / n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgwt);

    return 0;
}