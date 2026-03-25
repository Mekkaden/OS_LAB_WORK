#include <stdio.h>
#include <limits.h>

struct process {
    int pid, at, bt, pr, ct, tat, wt, done;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    //crucial

    for(int i = 0; i < n; i++) {
        printf("Enter AT BT PR of P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i + 1;
        p[i].done = 0;
    }

    int completed = 0, currenttime = 0; //time is like current time
    float sumWT = 0, sumTAT = 0;

    //crucial
    while(completed < n) {
        int idx = -1, max_pr = -1; 

        for(int i = 0; i < n; i++) { //performing search to find the best process to execute now
            if(p[i].at <= currenttime && p[i].done == 0) {
                if(p[i].pr > max_pr) { 
                    max_pr = p[i].pr;
                    idx = i;
                    //idx is index of the selected process
                }
            }
        }

        if(idx == -1) {
            currenttime++;
            continue; //enough for this iteration go back to the next iteration
        }

        currenttime += p[idx].bt;
        p[idx].ct = currenttime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        sumWT += p[idx].wt;
        sumTAT += p[idx].tat;
        completed++;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].pr,
            p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", sumTAT / n);
    printf("\nAverage WT  = %.2f\n", sumWT / n);

    return 0;
}