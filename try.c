#include <stdio.h>

struct process {
    int pid;
    int wt;
    int bt;
    int at;
    int ct;
    int tat;
};

int main(void) {
    int n;
    int t = 0;
    float twt = 0;  // Changed to float for accurate average division later
    float ttat = 0; // Changed to float for accurate average division later

    printf("Enter the no of processes: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Declaring array AFTER getting the value of n
    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter the pid, at, bt of process %d: ", i + 1);
        scanf("%d", &p[i].pid);
        scanf("%d", &p[i].at);
        scanf("%d", &p[i].bt);
    }

    // Bubble sort logic - FIXED: changed i to j
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculations logic
    for (int i = 0; i < n; i++) {
        if (t < p[i].at) {
            t = p[i].at;
        }
        p[i].ct = t + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        ttat += p[i].tat;
        twt += p[i].wt;

        t = p[i].ct;
    }

    float awt = twt / n;
    float atat = ttat / n;

    // Header for the table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    // FIXED: Added missing loop for printing the table rows
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    // FIXED: Used correct variable names (awt and atat)
    printf("\nAverage Waiting Time = %.2f\n", awt);
    printf("Average TAT Time = %.2f\n", atat);

    // --- GANTT CHART PRINTING ---
    printf("\n--- Gantt Chart ---\n ");
    
    int gantt_time = 0;
    
    // 1. Print Top Timeline Bar
    for (int i = 0; i < n; i++) {
        if (gantt_time < p[i].at) {
            printf("| IDLE "); 
            gantt_time = p[i].at;
        }
        printf("|  P%d  ", p[i].pid);
        gantt_time = p[i].ct;
    }
    printf("|\n "); 

    // 2. Print Bottom Time Markers
    gantt_time = 0;
    for (int i = 0; i < n; i++) {
        if (gantt_time < p[i].at) {
            printf("%-7d", gantt_time); 
            gantt_time = p[i].at;
        }
        printf("%-7d", gantt_time); 
        gantt_time = p[i].ct;
    }
    printf("%d\n\n", gantt_time); 

    return 0;
}