#include <stdio.h>
#include <limits.h>   // For large initial value

// Define structure
struct Process
{
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int rt;    // Remaining Time
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
};

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;   // Initially remaining time = burst time
    }

    int completed = 0;      // Count of completed processes
    int current_time = 0;   // Current time
    int min_index;          // Index of shortest job
    int total_wt = 0;
    int total_tat = 0;

    printf("\nGantt Chart:\n");

    // Run until all processes are completed
    while(completed != n)
    {
        int min_rt = INT_MAX;   // Large initial value
        min_index = -1;

        // Find process with minimum remaining time
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= current_time &&   // Arrived
               p[i].rt > 0 &&               // Not finished
               p[i].rt < min_rt)            // Smallest remaining time
            {
                min_rt = p[i].rt;
                min_index = i;
            }
        }

        // If no process available at this time
        if(min_index == -1)
        {
            current_time++;   // CPU idle
            continue;
        }

        // Execute process for 1 unit time
        printf("P%d (%d - %d)  ",
               p[min_index].pid,
               current_time,
               current_time + 1);

        p[min_index].rt--;      // Reduce remaining time
        current_time++;         // Increase time

        // If process finishes
        if(p[min_index].rt == 0)
        {
            completed++;

            p[min_index].ct = current_time;              // Completion Time
            p[min_index].tat = p[min_index].ct - p[min_index].at;  // TAT
            p[min_index].wt = p[min_index].tat - p[min_index].bt;  // WT

            total_wt += p[min_index].wt;
            total_tat += p[min_index].tat;
        }
    }

    printf("\n\n");

    // Print final table
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
