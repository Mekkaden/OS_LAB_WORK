#include <stdio.h>

// -------- Process Structure --------
struct process
{
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int rt;    // Remaining Time
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
} p[20];

int main()
{
    // -------- Variable Declarations --------
    int n, tq;                     // n = number of processes, tq = time quantum
    int queue[100], front = 0, rear = 0; // Ready queue
    int vis[20] = {0};             // Tracks whether process has entered queue

    int time = 0, completed = 0;   // Current CPU time and number of completed processes

    // -------- Input Section --------
    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter time quantum: ");
    scanf("%d",&tq);

    // -------- Reading Arrival Time and Burst Time --------
    for(int i=0;i<n;i++)
    {
        p[i].pid = i+1;  // Assign process ID

        printf("Enter AT of P%d: ",i+1);
        scanf("%d",&p[i].at);

        printf("Enter BT of P%d: ",i+1);
        scanf("%d",&p[i].bt);

        // Initially remaining time = burst time
        p[i].rt = p[i].bt;
    }

    // -------- Round Robin Scheduling --------
    while(completed < n)
    {
        // Add newly arrived processes to ready queue
        for(int i=0;i<n;i++)
        {
            if(p[i].at <= time && vis[i]==0)
            {
                queue[rear++] = i;   // Enqueue process index
                vis[i] = 1;          // Mark as visited
            }
        }

        // If queue empty → CPU idle
        if(front == rear)
        {
            time++;     // Move time forward
            continue;
        }

        // Dequeue next process
        int idx = queue[front++];

        // -------- If process finishes within time quantum --------
        if(p[idx].rt <= tq)
        {
            time += p[idx].rt;  // Execute remaining time
            p[idx].rt = 0;      // Process finished

            // Calculate completion, turnaround and waiting time
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;        // Increase completed process count
        }
        else
        {
        
            p[idx].rt -= tq;    // Reduce remaining time
            time += tq;         // Increase current time
        }

        // Check if new processes arrived during execution
        for(int i=0;i<n;i++)
        {
            if(p[i].at <= time && vis[i]==0)
            {
                queue[rear++] = i;
                vis[i] = 1;
            }
        }

        // If process not finished, push it back to queue
        if(p[idx].rt > 0)
            queue[rear++] = idx;
    }

    // -------- Average Calculations --------
    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    // Display process table
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    // Calculate averages
    printf("\nAverage WT = %.2f",avg_wt/n);
    printf("\nAverage TAT = %.2f\n",avg_tat/n);

    return 0;
}