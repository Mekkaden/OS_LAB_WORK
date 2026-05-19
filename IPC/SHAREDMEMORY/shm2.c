#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>

struct data{
    char s1[100];
    char s2[100];
    char s3[100];
    char result[400];
};

int main(){

    key_t key = ftok("shared_key.txt",65);

    int shmid = shmget(key, sizeof(struct data), 0666 | IPC_CREAT);

    if(shmid < 0){
        perror("shmget failed");
        return 1;
    }

    struct data *shm = (struct data*) shmat(shmid,NULL,0);

    sprintf(shm->result,"%s %s %s",shm->s1,shm->s2,shm->s3);

    printf("Process 2: Concatenation done: %s\n",shm->result);

    shmdt(shm);

    return 0;
}