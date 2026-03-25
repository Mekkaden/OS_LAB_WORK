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

    int currenttime = 0, completed = 0;   // Current CPU time and number of completed processes

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
            if(p[i].at <= currenttime && vis[i]==0)
            {
                queue[rear++] = i;   // Enqueue process index
                vis[i] = 1;          // Mark as visited
            }
        }

        // If queue empty → CPU idle
        if(front == rear)
        {
            currenttime++;     // Move time forward
            continue;
        }

        // Dequeue next process
        int idx = queue[front++];

        // -------- If process finishes within time quantum --------
        if(p[idx].rt <= tq)
        {
            currenttime += p[idx].rt;  // Execute remaining time
            p[idx].rt = 0;      // Process finished

            // Calculate completion, turnaround and waiting time
            p[idx].ct = currenttime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;        // Increase completed process count
        }
        else
        {
        
            p[idx].rt -= tq;    // Reduce remaining time
            currenttime += tq;         // Increase current time
        }

        // Check if new processes arrived during execution
        for(int i=0;i<n;i++)
        {
            if(p[i].at <= currenttime && vis[i]==0)
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



// Algorithm: Round Robin Scheduling

// Step 1: Start

// Step 2: Read the number of processes (n)

// Step 3: Read the time quantum (TQ)

// Step 4: For each process, read:
//         a) Process ID (PID)
//         b) Arrival Time (AT)
//         c) Burst Time (BT)

// Step 5: Initialize for each process:
//         Remaining Time = Burst Time
//         Mark process as not visited

// Step 6: Initialize:
//         Current Time = 0
//         Completed Processes = 0
//         Initialize an empty ready queue

// Step 7: Repeat until all processes are completed:

//         a) Insert into the ready queue all processes
//            whose Arrival Time ≤ Current Time
//            and are not yet visited

//         b) If the ready queue is empty:
//                 Increment Current Time by 1
//                 Go to Step 7

//         c) Remove the first process from the ready queue

//         d) If its Remaining Time ≤ Time Quantum:
//                 Execute the process completely
//                 Increase Current Time by Remaining Time
//                 Set Remaining Time = 0

//                 Completion Time (CT) = Current Time
//                 Turnaround Time (TAT) = CT - AT
//                 Waiting Time (WT) = TAT - BT

//                 Mark process as completed
//                 Increment completed count

//         e) Else:
//                 Execute the process for Time Quantum
//                 Reduce Remaining Time by Time Quantum
//                 Increase Current Time by Time Quantum

//         f) Insert into the ready queue all newly arrived processes
//            whose Arrival Time ≤ Current Time and not yet visited

//         g) If the process is not yet completed,
//            insert it again at the end of the ready queue

// Step 8: Compute:
//         Average Waiting Time = (Sum of all WT) / n
//         Average Turnaround Time = (Sum of all TAT) / n

// Step 9: Display PID, AT, BT, CT, TAT and WT

// Step 10: Stop