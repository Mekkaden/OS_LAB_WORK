#include <stdio.h>   // Standard input/output library

// -------- Structure Definition --------
// Stores information of each process
struct process {
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int rt;    // Remaining Time
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
};

// Global array to store processes
struct process p[100];


// -------- Function to Print Results --------
void print_process(struct process p[100], int n)
{
    int i;
    int total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    // Print details of each process
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Calculate averages
    avg_wt = (float) total_wt / n;
    avg_tat = (float) total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
}


// -------- SRTF Scheduling Function --------
void srtf(struct process p[100], int n)
{
    int time = 0;        // Current CPU time
    int completed = 0;   // Count of completed processes
    int i, j;
    struct process temp; // Used for swapping

    // Continue until all processes finish
    while (completed < n)
    {
        // -------- Sort arrived processes by remaining time --------
        // This ensures smallest remaining time process runs first
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (p[j].at <= time &&
                    p[j + 1].at <= time &&
                    p[j].rt > p[j + 1].rt)
                {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }

        // -------- Execute process --------
        for (i = 0; i < n; i++)
        {
            // Choose first arrived process with remaining time
            if (p[i].at <= time && p[i].rt > 0)
            {
                p[i].rt--;  // Run process for 1 time unit

                // If process finishes
                if (p[i].rt == 0)
                {
                    completed++;          // Increase finished count
                    p[i].ct = time + 1;   // Completion time

                    // Turnaround Time
                    p[i].tat = p[i].ct - p[i].at;

                    // Waiting Time
                    p[i].wt = p[i].tat - p[i].bt;
                }
                break;   // Only one process runs at a time
            }
        }

        time++;  // Increase CPU time
    }

    // Print final table
    print_process(p, n);
}


// -------- Main Function --------
int main()
{
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);

        // Initially remaining time = burst time
        p[i].rt = p[i].bt;
    }

    // Call SRTF scheduling
    srtf(p, n);

    return 0;
}