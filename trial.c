#include <stdio.h>

struct process{
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int ct;
};

int main(void){
    int n;
    struct process p[n];
    printf("Enter the number of processes");
    scanf("%d" ,&n);

        for(int i = 0; i < n; i++){
        printf("\nProcess %d\n", i+1);
        printf("Enter Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);  
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    for(int i = 0 ; i< n;i++){
        for(int j = 0 ; j< n-i-1;j++){
            if(p[j].at > p[j+1].at){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int currenttime = 0;
    int twt = 0;

    for(int i = 0 ; i< n;i++){
        if(currenttime < p[i].at){
            currenttime = p[i].at;

        }

        for(int i = 0;i<n;i++){
            p[i].ct = currenttime + p[i].bt;
            p[i].tat = 
        }
    }

}

