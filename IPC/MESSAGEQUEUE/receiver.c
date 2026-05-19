#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

// Step 1: Define message structure (must contain long type)
struct message {
    long type;
    char text[100];
};

// Step 2: Function to reverse the received string
void reverse(char *s)
{
    int i, len = strlen(s);
    char temp;

    for(i = 0; i < len/2; i++)
    {
        temp = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = temp;
    }
}

int main()
{
    // Step 3: Generate unique key using ftok() for message queue
    key_t key = ftok("progfile",65);

    // Step 4: Create or access message queue using msgget()
    int msgid = msgget(key,0666|IPC_CREAT);

    // Step 5: Declare message structure variable
    struct message m;

    // Step 6: Receive string sent by sender (message type 1)
    msgrcv(msgid,&m,sizeof(m.text),1,0);

    // Step 7: Reverse the received string
    reverse(m.text);

    // Step 8: Change message type to 2 to send back to sender
    m.type = 2;

    // Step 9: Send reversed string back to sender using msgsnd()
    msgsnd(msgid,&m,sizeof(m.text),0);

    // Step 10: Delete message queue from system using msgctl()
    msgctl(msgid,IPC_RMID,NULL);

    return 0;
}