#include <stdio.h>
#include <limits.h>

struct process {
    int pid, at, bt, ct, tat, wt, done; // No 'rt' needed, just 'done'
};

int main(void) {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    struct process p[n]; // Declared AFTER scanning n

    for(int i = 0; i < n; i++) {
        printf("Enter AT and BT of P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].done = 0; // Initialize as not finished
    }

    int completed = 0, currenttime = 0;
    float sumWT = 0, sumTAT = 0;

    // --- SJF SCHEDULING LOGIC ---
    while(completed < n) {
        int idx = -1;
        int min_bt = 9999; 

        // Search for the arrived process with the SHORTEST burst time
        for(int i = 0; i < n; i++) { 
            if(p[i].at <= currenttime && p[i].done == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if(idx == -1) {
            currenttime++;
            continue; // CPU is idle
        }

        // --- THE STANDARDIZED FCFS MATH BLOCK ---
        p[idx].ct = currenttime + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        currenttime = p[idx].ct;

        p[idx].done = 1; // Mark as done
        // ----------------------------------------

        sumWT += p[idx].wt;
        sumTAT += p[idx].tat;
        completed++;
    }

    // --- THE MAGIC TRICK: Sort by Completion Time (Execution Order) ---
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].ct > p[j+1].ct) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // --- TABLE PRINTING ---
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt,
            p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", sumTAT / n);
    printf("\nAverage WT  = %.2f\n", sumWT / n);


    printf("\n--- Gantt Chart ---\n ");
    
    int gantt_time = 0;
    
    // 1. Print Top Timeline Bar
    for(int i = 0; i < n; i++){
        int start_time = p[i].ct - p[i].bt; 
        
        if(gantt_time < start_time){
            printf("| IDLE "); 
            gantt_time = start_time;
        }
        printf("|  P%d  ", p[i].pid);
        gantt_time = p[i].ct;
    }
    printf("|\n "); 

    // 2. Print Bottom Time Markers
    gantt_time = 0;
    for(int i = 0; i < n; i++){
        int start_time = p[i].ct - p[i].bt;
        
        if(gantt_time < start_time){
            printf("%-7d", gantt_time); 
            gantt_time = start_time;
        }
        printf("%-7d", gantt_time); 
        gantt_time = p[i].ct;
    }
    printf("%d\n\n", gantt_time); 

    return 0;
}