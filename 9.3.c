#include <stdio.h>   // Library for printf and scanf

// -------- Structure Definition --------
// This structure stores all information about a process
struct process
{
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time (Total CPU time needed)
    int rt;    // Remaining Time (initially same as burst time)
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
} p[50];       // Array of structures (max 50 processes)

int main()
{
    int n;          // Number of processes
    int tq;         // Time Quantum
    int time = 0;   // Current CPU time
    int remain;     // Number of processes remaining to finish
    int i;          // Loop variable
    int flag;       // Used to check if any process executed in loop

    // -------- Step 1: Input number of processes --------
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // -------- Step 2: Input Time Quantum --------
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    // -------- Step 3: Input process details --------
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;   // Assign process ID automatically

        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;  // Initially remaining time = burst time
    }

    remain = n;   // Initially all processes are unfinished

    // -------- Step 4: Round Robin Execution --------
    // Continue loop until all processes finish
    while (remain > 0)
    {
        flag = 0;   // Assume no process executed in this cycle

        // Check each process one by one
        for (i = 0; i < n; i++)
        {
            // Condition:
            // Process must still have remaining time
            // AND must have already arrived
            if (p[i].rt > 0 && p[i].at <= time)
            {
                flag = 1;   // At least one process ran

                // -------- Case 1: Process finishes in this quantum --------
                if (p[i].rt <= tq)
                {
                    time += p[i].rt;  // Advance time by remaining time
                    p[i].rt = 0;      // Process finished

                    p[i].ct = time;   // Completion Time

                    // Turnaround Time = Completion - Arrival
                    p[i].tat = p[i].ct - p[i].at;

                    // Waiting Time = Turnaround - Burst
                    p[i].wt = p[i].tat - p[i].bt;

                    remain--;  // One process finished
                }

                // -------- Case 2: Process not finished --------
                else
                {
                    time += tq;      // Run for time quantum
                    p[i].rt -= tq;   // Reduce remaining time
                }
            }
        }

        // -------- CPU Idle Condition --------
        // If no process executed in this cycle
        if (flag == 0)
            time++;   // Move time forward until next process arrives
    }

    // -------- Step 5: Display Results --------
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float total_wt = 0, total_tat = 0;

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // -------- Step 6: Average Times --------
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;   // Program ends successfully
}