#include <stdio.h>   // For input and output

// Define structure for Process
struct Process
{
    int pid;   // Process ID
    int bt;    // Burst Time
    int at;    // Arrival Time (accepted as per algorithm)
    int pr;    // Priority
    int wt;    // Waiting Time
    int tat;   // Turnaround Time
    int st;    // Start Time
    int ct;    // Completion Time
};

int main()
{
    int n;   // Number of processes

    // Step 2: Accept number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Create array of structure
    struct Process p[n];

    // Step 3: Accept process details
    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Priority: ");
        scanf("%d", &p[i].pr);
    }

    // Step 4: Sort processes by ascending priority (Bubble Sort)
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(p[j].pr > p[j + 1].pr)
            {
                // Swap entire structure
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int total_wt = 0;    // Total waiting time
    int total_tat = 0;   // Total turnaround time

    // Step 5: First process
    p[0].wt = 0;                   // Waiting time of first process = 0
    p[0].st = 0;                   // Start time = 0
    p[0].ct = p[0].bt;             // Completion time = burst time
    p[0].tat = p[0].bt;            // Turnaround time = burst time

    total_wt += p[0].wt;
    total_tat += p[0].tat;

    // Step 6: Calculate for remaining processes
    for(int i = 1; i < n; i++)
    {
        // Waiting time = previous waiting time + previous burst time
        p[i].wt = p[i - 1].wt + p[i - 1].bt;

        // Start time = waiting time
        p[i].st = p[i].wt;

        // Turnaround time = waiting time + burst time
        p[i].tat = p[i].wt + p[i].bt;

        // Completion time = turnaround time
        p[i].ct = p[i].tat;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Step 8: Calculate averages
    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;

    // Display scheduling table
    printf("\n\nPriority Scheduling Result:\n");
    printf("PID\tAT\tBT\tPR\tWT\tTAT\tST\tCT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].pr,
               p[i].wt,
               p[i].tat,
               p[i].st,
               p[i].ct);
    }

    // Step 7: Print Gantt Chart
    printf("\nGantt Chart:\n");
    for(int i = 0; i < n; i++)
    {
        printf("P%d (%d - %d)  ",
               p[i].pid,
               p[i].st,
               p[i].ct);
    }

    printf("\n");

    // Print averages
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    // Step 9: Stop
    return 0;
}

