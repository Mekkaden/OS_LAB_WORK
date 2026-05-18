#include <stdio.h>

// -------- STEP 1: Define process structure --------
struct process {
    int pid, at, bt, ct, tat, wt;
    int remaining_bt; 
    int in_queue; // Replaces your 'vis' array to track if it entered the queue
};

int main(void) {
    int n, tq;
    printf("Enter number of processes: ");
    if(scanf("%d", &n) != 1) return 1;

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    struct process p[n];
    
    // We make the queue big enough so it never overflows during preemption
    int queue[1000], front = 0, rear = 0; 

    for(int i = 0; i < n; i++) {
        printf("Enter AT and BT of P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].remaining_bt = p[i].bt;
        p[i].in_queue = 0; // Mark as not visited yet
    }

    int completed = 0, currenttime = 0;
    float sumWT = 0, sumTAT = 0;

    // --- LAZY GANTT CHART SETUP ---
    printf("\n--- Gantt Chart ---\n");
    printf("0");

    // -------- ROUND ROBIN SCHEDULING LOGIC --------
    while(completed < n) {
        
        // 1. Add any newly arrived processes to the back of the queue
        for(int i = 0; i < n; i++) {
            if(p[i].at <= currenttime && p[i].in_queue == 0) {
                queue[rear++] = i;
                p[i].in_queue = 1; 
            }
        }

        // 2. If queue is empty, the CPU is idle
        if(front == rear) {
            currenttime++;
            // --- LAZY GANTT: IDLE TICK ---
            printf(" --IDLE-- %d", currenttime);
            continue;
        }

        // 3. Pop the next process from the front of the line
        int idx = queue[front++];

        // 4. Execution Step
        if(p[idx].remaining_bt <= tq) {
            // Process can finish within this time quantum
            currenttime += p[idx].remaining_bt;
            p[idx].remaining_bt = 0;

            // Standard Math Block
            p[idx].ct = currenttime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            sumWT += p[idx].wt;
            sumTAT += p[idx].tat;
            completed++;
        } 
        else {
            // Process gets preempted after Time Quantum
            p[idx].remaining_bt -= tq;
            currenttime += tq;
        }
        

        // --- LAZY GANTT: PROCESS TICK ---
        // Prints the chunk it just executed (whether it finished or got preempted)
        printf(" --P%d-- %d", p[idx].pid, currenttime);

        // 5. Check if any NEW processes arrived WHILE this process was running
        for(int i = 0; i < n; i++) {
            if(p[i].at <= currenttime && p[i].in_queue == 0) {
                queue[rear++] = i;
                p[i].in_queue = 1;
            }
        }

        // 6. If the current process is still not finished, throw it back to the end of the line
        if(p[idx].remaining_bt > 0) {
            queue[rear++] = idx;
        }
    }

    // -------- TABLE PRINTING --------
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", sumTAT / n);
    printf("\nAverage WT  = %.2f\n", sumWT / n);

    return 0;
}