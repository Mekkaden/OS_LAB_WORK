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

    int completed = 0, time = 0; 
    float sumWT = 0, sumTAT = 0;

    // The Master Clock ticks one by one
    while(completed < n) {
        int idx = -1;
        int max_pr = -1;

        // Check who is available at the CURRENT time
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].done == 0) {
                if(p[i].pr > max_pr) {
                    max_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++; // Idle time
            continue;
        }

        // PREEMPTIVE STEP: Process for only 1 unit of time
        p[idx].remaining_bt--;
        time++;

        // If the process is finished
        if(p[idx].remaining_bt == 0) {
            p[idx].ct = time;
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