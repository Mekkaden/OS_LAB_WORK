#include <stdio.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int pr;
    int wt;
    int tat;
    int ct;
    int completed;
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Priority (lower number = higher priority): ");
        scanf("%d", &p[i].pr);

        p[i].completed = 0;
    }

    int time = 0;
    int completed = 0;
    int total_wt = 0, total_tat = 0;

    while(completed < n)
    {
        int idx = -1;
        int highest_pr = 9999;

        // Find highest priority process that has arrived
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time && p[i].completed == 0)
            {
                if(p[i].pr < highest_pr)
                {
                    highest_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1)
        {
            // Execute selected process
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = 1;
            completed++;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        }
        else
        {
            // CPU idle
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].pr,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}