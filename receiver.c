#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct message {
    long type;
    char text[100];
};

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
    key_t key = ftok("progfile",65);
    int msgid = msgget(key,0666|IPC_CREAT);

    struct message m;

    msgrcv(msgid,&m,sizeof(m.text),1,0);

    reverse(m.text);

    m.type = 2;

    msgsnd(msgid,&m,sizeof(m.text),0);

    msgctl(msgid,IPC_RMID,NULL);

    return 0;
}