#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ref[100];

// print frames
void print(int frame[], int f){
    for(int i=0;i<f;i++)
        if(frame[i]==-1) printf("- ");
        else printf("%d ",frame[i]);
}

// FIFO
void fifo(int n,int f){
    int frame[10],i,j=0,fault=0;

    for(i=0;i<f;i++) frame[i]=-1;

    printf("\nFIFO:\nPage\tFrames\tStatus\n");

    for(i=0;i<n;i++){
        int hit=0;

        for(int k=0;k<f;k++)
            if(frame[k]==ref[i]) hit=1;

        printf("%d\t",ref[i]);

        if(!hit){
            frame[j]=ref[i];
            j=(j+1)%f;
            fault++;
            print(frame,f);
            printf("\tFault");
        } else {
            print(frame,f);
            printf("\tHit");
        }
        printf("\n");
    }
    printf("Total Faults = %d\n",fault);
}

// LRU
void lru(int n,int f){
    int frame[10],time[10],i,fault=0,c=0;

    for(i=0;i<f;i++){
      frame[i]=-1;
      time[i]=0;
    }

    printf("\nLRU:\nPage\tFrames\tStatus\n");

    for(i=0;i<n;i++){
        int pos=-1;

        for(int j=0;j<f;j++)
            if(frame[j]==ref[i]) pos=j;

        printf("%d\t",ref[i]);

        if(pos!=-1){
            time[pos]=++c;
            print(frame,f);
            printf("\tHit");
        } else {
            int min=0;
            for(int j=1;j<f;j++)
                if(time[j]<time[min]) min=j;

            frame[min]=ref[i];
            time[min]=++c;
            fault++;

            print(frame,f);
            printf("\tFault");
        }
        printf("\n");
    }
    printf("Total Faults = %d\n",fault);
}

// Optimal
void optimal(int n,int f){
    int frame[10],i,fault=0;

    for(i=0;i<f;i++) frame[i]=-1;

    printf("\nOptimal:\nPage\tFrames\tStatus\n");

    for(i=0;i<n;i++){
        int hit=0;

        // check hit
        for(int j=0;j<f;j++)
            if(frame[j]==ref[i]) hit=1;

        printf("%d\t",ref[i]);

        if(hit){
            print(frame,f);
            printf("\tHit\n");
            continue;
        }

        // 🔥 CHECK EMPTY FRAME FIRST
        int pos=-1;
        for(int j=0;j<f;j++){
            if(frame[j]==-1){
                pos=j;
                break;
            }
        }

        // if no empty frame → apply optimal
        if(pos==-1){
            int farthest=-1;

            for(int j=0;j<f;j++){
                int k;
                for(k=i+1;k<n;k++)
                    if(frame[j]==ref[k]) break;

                if(k==n){
                    pos=j;
                    break;
                }

                if(k>farthest){
                    farthest=k;
                    pos=j;
                }
            }
        }

        frame[pos]=ref[i];
        fault++;

        print(frame,f);
        printf("\tFault\n");
    }

    printf("Total Faults = %d\n",fault);
}
// main
int main(int argc,char *argv[]){
    if(argc<3){
        printf("Usage: %s <length> <frames>\n",argv[0]);
        return 1;
    }

    int n=atoi(argv[1]);
    int f=atoi(argv[2]);

    srand(time(0));

    printf("Reference String: ");
    for(int i=0;i<n;i++){
        ref[i]=rand()%10;
        printf("%d ",ref[i]);
    }
    printf("\n");

    fifo(n,f);
    lru(n,f);
    optimal(n,f);

    return 0;
}