#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

// Step 1: Define message structure (must contain long type)
struct message {
    long type;
    char text[100];
};

int main(){

    // Step 2: Generate a unique key using ftok()
    key_t key = ftok("progfile",65);

    // Step 3: Create or access the message queue using msgget()
    int msgid = msgget(key,0666|IPC_CREAT);

    // Step 4: Declare message structure and variable to store original string
    struct message m;
    char original[100];

    // Step 5: Read string from user
    printf("Enter string: ");
    scanf("%s",original);

    // Step 6: Copy user input into message structure
    strcpy(m.text,original);

    // Step 7: Set message type to 1 (sending to receiver)
    m.type = 1;

    // Step 8: Send string to receiver using msgsnd()
    msgsnd(msgid,&m,sizeof(m.text),0);

    // Step 9: Receive reversed string from receiver (message type 2)
    msgrcv(msgid,&m,sizeof(m.text),2,0);

    // Step 10: Display reversed string received
    printf("Reversed: %s\n",m.text);

    // Step 11: Compare original and reversed string to check palindrome
    if(strcmp(original,m.text)==0)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");

    return 0;
}