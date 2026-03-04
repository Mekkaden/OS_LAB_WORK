#include <stdio.h>

struct process
{
    int pid, at, bt, rt, ct, tat, wt;
} p[50];

int main()
{
    int n, tq;
    int queue[100];
    int front = 0, rear = 0;

    int time = 0, completed = 0;
    int i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;
    }

    // Insert processes arriving at time 0
    for (i = 0; i < n; i++)
        if (p[i].at == 0)
            queue[rear++] = i;

    while (completed < n)
        {
            // CPU idle
            if (front == rear)
            {
                time++;

                for (i = 0; i < n; i++)
                    if (p[i].at == time)
                        queue[rear++] = i;

                continue;
            }

        int idx = queue[front++];   // dequeue

        if (p[idx].rt <= tq)
        {
            time += p[idx].rt;
            p[idx].rt = 0;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
        }
        else
        {
            time += tq;
            p[idx].rt -= tq;
        }

        // Add newly arrived processes
        for (i = 0; i < n; i++)
            if (p[i].at > time - tq && p[i].at <= time)
                queue[rear++] = i;

        // Reinsert unfinished process
        if (p[idx].rt > 0)
            queue[rear++] = idx;
    }

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

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}