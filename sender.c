#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct message {
    long type;
    char text[100];
};

int main(){

    key_t key = ftok("progfile",65);
    int msgid = msgget(key,0666|IPC_CREAT);

    struct message m;
    char original[100];

    printf("Enter string: ");
    scanf("%s",original);

    strcpy(m.text,original);
    m.type = 1;

    msgsnd(msgid,&m,sizeof(m.text),0);

    msgrcv(msgid,&m,sizeof(m.text),2,0);

    printf("Reversed: %s\n",m.text);

    if(strcmp(original,m.text)==0)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");

    return 0;
}