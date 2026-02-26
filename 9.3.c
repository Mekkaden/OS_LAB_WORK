#include <stdio.h>   // For input and output

// Define structure for Process
struct Process
{
    int pid;        // Process ID
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int completed;  // Completion Flag (0 = not finished, 1 = finished)
};

int main()
{
    int n;              // Number of processes
    int quantum;        // Time Quantum
    int time = 0;       // Current Time
    int total_wt = 0;   // Total Waiting Time
    int total_tat = 0;  // Total Turnaround Time
    int done;           // Flag to check if all processes finished

    // Step 2: Accept number of processes and quantum
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    // Create structure array
    struct Process p[n];

    // Step 3: Accept process details
    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        // Step 4: Initialize remaining time and completion flag
        p[i].rt = p[i].bt;      // Remaining time initially equals burst time
        p[i].completed = 0;     // Not completed

        // Step 5: Initialize waiting and turnaround time
        p[i].wt = 0;
        p[i].tat = 0;
    }

    printf("\nGantt Chart:\n");

    // Step 6: Repeat until all processes are completed
    do
    {
        done = 1;   // Assume all done initially

        for(int i = 0; i < n; i++)
        {
            if(p[i].rt > 0)   // If process still has remaining time
            {
                done = 0;     // At least one process not finished

                int start_time = time;   // Record start time

                if(p[i].rt <= quantum)
                {
                    // If remaining time less than quantum
                    time = time + p[i].rt;   // Increase time
                    p[i].rt = 0;             // Process finished
                    p[i].completed = 1;

                    p[i].tat = time;         // Turnaround time = completion time
                    p[i].wt = p[i].tat - p[i].bt;  // Waiting time
                }
                else
                {
                    // If remaining time greater than quantum
                    time = time + quantum;   // Increase time by quantum
                    p[i].rt = p[i].rt - quantum;  // Reduce remaining time
                }

                int end_time = time;   // Record end time

                // Print Gantt chart details for this round
                printf("P%d (%d - %d)  ",
                       p[i].pid,
                       start_time,
                       end_time);
            }
        }

    } while(done == 0);   // Continue until all processes finished

    printf("\n\n");

    // Step 7: Print final waiting time and turnaround time
    printf("PID\tBT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].bt,
               p[i].wt,
               p[i].tat);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Step 8: Calculate averages
    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    // Step 9: Stop
    return 0;
}

