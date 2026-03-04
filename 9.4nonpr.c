#include <stdio.h>

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
    struct process p[100], temp;
    int n, i, j;
    int time = 0, completed = 0;
    int total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);

        // crucial
        p[i].rt = p[i].bt;
    }

    while (completed < n)
    {
        // sort arrived processes by remaining time
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                // check whether it has arrived and which has less burst
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

        for (i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0)
            {
                // -------- NON PREEMPTIVE CHANGE --------
                time += p[i].rt;   // run full burst
                p[i].rt = 0;

                completed++;
                p[i].ct = time;
                p[i].tat = p[i].ct - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
                break;
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}