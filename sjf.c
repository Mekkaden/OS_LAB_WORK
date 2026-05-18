#include <stdio.h>
#include <limits.h>

struct process {
    int pid, at, bt, ct, tat, wt, done;
};

int main(void) {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    struct process p[n]; 

    for(int i = 0; i < n; i++) {
        printf("Enter AT and BT of P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].done = 0; 
    }

    int completed = 0, currenttime = 0;
    float sumWT = 0, sumTAT = 0;

    // --- LAZY GANTT CHART SETUP ---
    printf("\n--- Gantt Chart ---\n");
    printf("0");

    // --- SJF SCHEDULING LOGIC ---
    while(completed < n) {
        int idx = -1;
        int min_bt = 99999; 

        // Search for the arrived process with the SHORTEST burst time
        for(int i = 0; i < n; i++) { 
            if(p[i].at <= currenttime && p[i].done == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
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

        p[idx].done = 1; 

        // --- LAZY GANTT: PROCESS PRINT ---
        // It prints the chunk it just finished
        printf(" --P%d-- %d", p[idx].pid, currenttime);
        // ----------------------------------------

        sumWT += p[idx].wt;
        sumTAT += p[idx].tat;
        completed++;
    }

    // NOTICE: We completely deleted the sorting loop here! 

    // --- TABLE PRINTING ---
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt,
            p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", sumTAT / n);
    printf("\nAverage WT  = %.2f\n", sumWT / n);

    return 0;
}