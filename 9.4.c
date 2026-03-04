#include <stdio.h>

// -------- STEP 1: Define process structure --------
struct process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main()
{
    // -------- STEP 2: Declare variables --------
    struct process p[100], temp;
    int n, i, j;
    int time = 0, completed = 0;
    int total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    // -------- STEP 3: Read number of processes --------
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // -------- STEP 4: Input arrival time and burst time --------
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);

        //crucial
        // STEP 5: Initialize remaining time
        p[i].rt = p[i].bt;
    }

    // -------- STEP 6: Execute processes until all complete --------
    while (completed < n)
    {
        // STEP 7: Sort arrived processes based on remaining time
        // sort arrived processes by remaining time
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                //crucial
                //check whether it has arrived and if arrived which have less remaining time
                if (p[j].at <= time &&
                    p[j+1].at <= time &&
                    p[j].rt > p[j+1].rt)
                {
                    temp = p[j];
                    p[j] = p[j+1];
                    p[j+1] = temp;
                }
            }
        }

        // -------- STEP 8: Execute the process with shortest remaining time --------
        for (i = 0; i < n; i++)
        {
            //cruc
            if (p[i].at <= time && p[i].rt > 0)
            {
                // STEP 9: Execute process for 1 time unit
                p[i].rt--;

                // STEP 10: If process finishes
                if (p[i].rt == 0)
                {
                    completed++;
                    p[i].ct = time + 1;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
                break;
            }
        }

        // -------- STEP 11: Move time forward --------
        time++;
    }

    // -------- STEP 12: Display process details --------
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // -------- STEP 13: Calculate averages --------
    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    // -------- STEP 14: Print averages --------
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}