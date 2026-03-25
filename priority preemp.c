#include <stdio.h>

struct process {
    int pid, at, bt, pr, ct, tat, wt, done;
    int remaining_bt; // Essential for preemptive
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter AT BT PR of P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i + 1;
        p[i].done = 0;
        p[i].remaining_bt = p[i].bt; // Initialize remaining time
    }

    int completed = 0, currenttime = 0; 
    float sumWT = 0, sumTAT = 0;

    // The Master Clock ticks one by one
    while(completed < n) {
        int idx = -1;
        int max_pr = -1;

        // Check who is available at the CURRENT time
        for(int i = 0; i < n; i++) {
            if(p[i].at <= currenttime && p[i].done == 0) {
                if(p[i].pr > max_pr) {
                    max_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            currenttime++; // Idle time
            continue;
        }

        // PREEMPTIVE STEP: Process for only 1 unit of time
        p[idx].remaining_bt--;
        currenttime++;

        // If the process is finished
        if(p[idx].remaining_bt == 0) {
            p[idx].ct = currenttime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt; // Use original bt
            p[idx].done = 1;

            sumWT += p[idx].wt;
            sumTAT += p[idx].tat;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].pr,
            p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", sumTAT / n);
    printf("\nAverage WT  = %.2f\n", sumWT / n);

    return 0;
}



// Algorithm: Preemptive Priority Scheduling

// Step 1: Start

// Step 2: Read the number of processes (n)

// Step 3: For each process, read:
//         a) Process ID (PID)
//         b) Arrival Time (AT)
//         c) Burst Time (BT)
//         d) Priority (PR)

// Step 4: Initialize for each process:
//         Remaining Burst Time = Burst Time
//         Mark process as not completed

// Step 5: Initialize:
//         Current Time = 0
//         Completed Processes = 0

// Step 6: Repeat until all processes are completed:

//         a) From the set of processes that have arrived (AT ≤ current time)
//            and are not completed, select the process with the highest priority

//         b) If no such process is available:
//                 Increment current time by 1 and repeat Step 6

//         c) Allocate CPU to the selected process for 1 unit of time

//         d) Decrease its Remaining Burst Time by 1

//         e) Increment current time by 1

//         f) If Remaining Burst Time becomes 0:
//                 i)   Completion Time (CT) = current time
//                 ii)  Turnaround Time (TAT) = CT - AT
//                 iii) Waiting Time (WT) = TAT - BT
//                 iv)  Mark process as completed
//                 v)   Increment completed count

// Step 7: Compute:
//         Average Waiting Time = (Sum of all WT) / n
//         Average Turnaround Time = (Sum of all TAT) / n

// Step 8: Display PID, AT, BT, PR, CT, TAT, WT

// Step 9: Stop