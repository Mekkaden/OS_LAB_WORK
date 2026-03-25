#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>
#include<unistd.h>
#include <sys/wait.h>

struct data{
    char or[100];
    char rev[100];
};

int main(void){

    pid_t pid = fork();

    if(pid < 0 ){
        printf("fork failed");
        return 1;
    }
    else if(pid == 0){
        sleep(8);   // minimal fix
        printf("Child process created\n");

        struct data m;
        key_t key = ftok("progfile",65);
        int shmidd = shmget(key,sizeof(m),0666|IPC_CREAT);
        struct data* shmm = (struct data*)shmat(shmidd,NULL,0);

        char repp[100];
        strcpy(repp,shmm->or);

        int n = strlen(repp);
        char temp;

        for (int i = 0; i < n / 2; i++) {
            temp = repp[i];
            repp[i] = repp[n - i - 1];
            repp[n - i - 1] = temp;
        }

        strcpy(shmm->rev,repp);
        shmdt(shmm);
    }
    else{
        printf("Enter a string: ");
        char rep[100];
        scanf("%s",rep);

        key_t key = ftok("progfile",65);
        struct data m;
        int shmid = shmget(key,sizeof(m),0666|IPC_CREAT);
        struct data* shm = (struct data*)shmat(shmid,NULL,0);

        strcpy(shm->or,rep);

        wait(NULL);
        char hehe[100];
        strcpy(hehe,shm->rev);
        printf("Rev String is %s\n" ,hehe);

        shmdt(shm);
        shmctl(shmid,IPC_RMID,NULL);
    }
}