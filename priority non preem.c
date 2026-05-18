#include <stdio.h>
#include <limits.h>

struct process {
    int pid, at, bt, pr, ct, tat, wt, done;
};

int main(void) {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    struct process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter AT BT PR of P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i + 1;
        p[i].done = 0;
    }

    int completed = 0, currenttime = 0;
    float sumWT = 0, sumTAT = 0;

    // --- LAZY GANTT CHART SETUP ---
    printf("\n--- Gantt Chart ---\n");
    printf("0");

    // --- PRIORITY SCHEDULING LOGIC ---
    while(completed < n) {
        int idx = -1, max_pr = -1; 

        for(int i = 0; i < n; i++) { 
            if(p[i].at <= currenttime && p[i].done == 0 && p[i].pr > max_pr) {
                max_pr = p[i].pr;
                idx = i;
            }
        }

        if(idx == -1) {
            currenttime++;
            // --- LAZY GANTT: IDLE PRINT ---
            printf(" --IDLE-- %d", currenttime);
            continue; 
        }

        // --- THE STANDARDIZED FCFS MATH BLOCK ---
        p[idx].ct = currenttime + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        currenttime = p[idx].ct;

        p[idx].done = 1; // Mark as done for Priority

        // --- LAZY GANTT: PROCESS PRINT ---
        printf(" --P%d-- %d", p[idx].pid, currenttime);
        // ----------------------------------------

        sumWT += p[idx].wt; 
        sumTAT += p[idx].tat;
        completed++;
    }

    // --- TABLE PRINTING ---
    // Added \n\n to make sure the table doesn't crash into the Gantt chart
    printf("\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].pr,
            p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", sumTAT / n);
    printf("\nAverage WT  = %.2f\n", sumWT / n);

    return 0;
}