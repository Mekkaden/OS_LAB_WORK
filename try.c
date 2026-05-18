#include <stdio.h>
#include<stdlib.h>


struct process{
    int pid;
    int bt;
    int wt;
    int tat;
    int at;
    int rt;
    int inq;
    int ct;
};

int main(void){

   
    int n;
    int tq;
    int t = 0 ;
    int completed = 0 ;
    printf("Enter the number of processes");
    scanf("%d",&n);
    printf("\nEnter the time quantum");
    scanf("%d",&tq);
    struct process p[n];

    printf("Enter the at,bt of processes\n");
    for(int i = 0 ; i < n ;i++){
        printf("Process %d\n" , i);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].pid  = i+1;
        p[i].inq = 0;
        p[i].rt = p[i].bt;
    }

    int queue[100];
    int f = 0;
    int stat = 0 ;
    int swt = 0;
    int r = 0;

    printf("\n---- Gantt cahrt ----- \n");
    printf("0");

    while(completed < n){

        //check for newly arrievd processes
        for(int i = 0;i<n;i++){
            if(p[i].at <= t && p[i].inq == 0){
                queue[r++] = i ;
                p[i].inq = 1;
            }
        }
    

    //check for cpu idle time 
    if(f == r){
        t++;
        printf(" --idle ---%d" , t);
        continue;
    }

    //dequeue
    int idx = queue[f++];

    if(p[idx].rt <= tq){
        p[idx].rt =0;
        t+=p[idx].rt;

        p[idx].ct = t;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        stat += p[idx].wt;
        swt += p[idx].tat;
        completed++;

    }else{
        t+=tq;
        p[idx].rt -=tq;
    }

    printf("---P%d  %d" , p[idx].pid , t);

    //check for newly arrived processes during runtime
    for(int i = 0 ; i < n;i++){
        if(p[i].at <=t && p[i].inq==0){
            queue[r++] = i;
            p[i].inq = 1;
        }
    }

    if(p[idx].rt != 0 ){
        queue[r++] = idx;
    }

}


//printitng table

printf("\nTABLE\n");

printf("\nPID\tAT\tBT\tWT\tCT\tTAT\n");

for(int i = 0 ; i < n ; i++){
    printf("%d\t%d\t%d\t%d\t%d\t%d\n" ,p[i].pid,p[i].at,p[i].bt,p[i].wt,p[i].ct,p[i].tat);
    
}

    return 0;
}