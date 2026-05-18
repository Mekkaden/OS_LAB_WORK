#include <stdio.h>

struct process {
    int pid, at, bt, ct, tat, wt, done;
    int remaining_bt; // This is the 'rt'
};

int main(void) {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    struct process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter AT and BT of P%d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].done = 0;
        p[i].remaining_bt = p[i].bt; // Crucial: Initialize remaining time
    }

    int completed = 0, currenttime = 0; 
    float sumWT = 0, sumTAT = 0;

    // --- LAZY GANTT CHART SETUP ---
    printf("\n--- Gantt Chart ---\n");
    printf("0"); // Start the timeline at 0

    // The Master Clock ticks one by one
    while(completed < n) {
        int idx = -1;
        int min_rt = 99999; 

        // Check who is available at the CURRENT time
        for(int i = 0; i < n; i++) {
            // SRTF LOGIC: Find the arrived process with the SMALLEST remaining time
            if(p[i].at <= currenttime && p[i].done == 0 && p[i].remaining_bt < min_rt) {
                min_rt = p[i].remaining_bt;
                idx = i;
            }
        }

        if(idx == -1) {
            currenttime++; // CPU is idle
            
            // --- LAZY GANTT: IDLE TICK ---
            printf(" --IDLE-- %d", currenttime); 
            continue;
        }

        // PREEMPTIVE STEP: Process for only 1 unit of time
        p[idx].remaining_bt--;
        currenttime++;
        
        // --- LAZY GANTT: PROCESS TICK ---
        printf(" --P%d-- %d", p[idx].pid, currenttime);

        // If the process is finished
        if(p[idx].remaining_bt == 0) {
            // EXACT SAME MATH BLOCK AS BEFORE
            p[idx].ct = currenttime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt; 
            p[idx].done = 1;

            sumWT += p[idx].wt;
            sumTAT += p[idx].tat;
            completed++;
        }
    }

    // --- TABLE PRINTING ---
    // Added an extra \n here so the table doesn't smash into the Gantt chart
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