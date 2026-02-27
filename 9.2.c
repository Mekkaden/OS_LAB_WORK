#include <stdio.h>

struct Process
{
    int pid;
    int bt;
    int at;
    int pr;
    int wt;
    int tat;
    int st;
    int ct;
};

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
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

    // Sort by Priority (ascending)
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(p[j].pr > p[j + 1].pr)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int total_wt = 0;
    int total_tat = 0;

    // First process starts at time 0
    p[0].st = 0;
    p[0].wt = 0;
    p[0].ct = p[0].bt;
    p[0].tat = p[0].ct;   // since arrival time = 0;    

    total_wt += p[0].wt;
    total_tat += p[0].tat;

    // Remaining processes
    for(int i = 1; i < n; i++)
    {
        p[i].st = p[i-1].ct;
        p[i].wt = p[i].st;
        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    float avg_wt = (float) total_wt / n;
    float avg_tat = (float) total_tat / n;

    printf("\nPriority Scheduling Result:\n");
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

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}