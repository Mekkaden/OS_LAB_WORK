#include<stdio.h>
#include<ctype.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

// Step 1: Define structure that will be stored in shared memory
struct data{
    char s1[100];
    char s2[100];
    char s3[100];
    char result[400];
};

// Step 2: Function to flip case of characters in the final string
void flipcase(char str[]){
    for(int i=0;i<strlen(str);i++){
        if(isupper(str[i]))
            str[i]=tolower(str[i]);
        else if(islower(str[i]))
            str[i]=toupper(str[i]);
    }
}

int main(){

    int shmid;

    // Step 3: Generate unique key using ftok() for shared memory
    key_t key = ftok("shared_key.txt",65);

    // Step 4: Create shared memory segment using shmget()
    shmid = shmget(key,sizeof(struct data),IPC_CREAT|0666);

    // Step 5: Check whether shared memory creation failed
    if(shmid < 0){
        perror("shmget failed");
        return 1;
    }

    // Step 6: Attach shared memory segment to the process
    struct data *shm = (struct data*) shmat(shmid,NULL,0);

    // Step 7: Read three strings from the user and store in shared memory
    printf("Enter first string: ");
    scanf("%s",shm->s1);

    printf("Enter second string: ");
    scanf("%s",shm->s2);

    printf("Enter third string: ");
    scanf("%s",shm->s3);

    // Step 8: Wait for Process 2 to concatenate the strings
    printf("Waiting for Process 2...\n");
    sleep(20);

    // Step 9: Flip the case of the concatenated result
    flipcase(shm->result);

    // Step 10: Display the flipped result
    printf("Flipped result: %s\n",shm->result);

    // Step 11: Detach shared memory from the process
    shmdt(shm);

    // Step 12: Remove shared memory segment from system
    shmctl(shmid,IPC_RMID,NULL);

    return 0;
}